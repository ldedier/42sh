/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_cmd_subst.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:29:58 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/13 09:27:04 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"


static int	child_part(t_context *context, char *command, int fds[])
{
	int	ret;
	
	(void)ret;
	ret = SUCCESS;
	if (dup2(fds[PIPE_IN], STDOUT_FILENO) < 0)
		return (sh_perror(SH_ERR1_INTERN_ERR, "get_subshell_output"));
	close(fds[PIPE_OUT]);
	sh_pre_execution();
	g_job_ctrl->interactive = 0;
	reset_signals();
	signal(SIGTSTP, SIG_IGN);
	ret = execute_command(context->shell, command, 0);
	g_job_ctrl->interactive = 1;
	close(fds[PIPE_IN]);
	sh_free_all(context->shell);
	return (context->shell->ret_value);
}

static int	parent_part(t_context *context, char **str, int fds[], int cpid)
{
	int	ret;

	(void)context;
	ret = SUCCESS;
	close(fds[PIPE_IN]);
	waitpid(cpid, &ret, 0);
	sh_env_update_ret_value_wait_result(context, ret);
	sh_env_update_question_mark(context->shell);
	sh_post_execution();
	if ((*str = get_string_from_fd(fds[PIPE_OUT])) == NULL)
		return (FAILURE);
	if (WIFSIGNALED(ret) && (WTERMSIG(ret) == SIGINT))
	{
		close(fds[PIPE_OUT]);
		return (context->shell->ret_value);
	}
	close(fds[PIPE_OUT]);
	return (SUCCESS);
}

int 		get_subshell_output(t_context *context, char *command, char **str)
{
	pid_t	cpid;
	int		fds[2];
	
	if (pipe(fds))
		return (sh_perror(SH_ERR1_PIPE, "get_subshell_output"));
	if ((cpid = fork()) == -1)
		return (sh_perror(SH_ERR1_FORK, "get_subshell_output"));
	if (cpid == 0)
		exit(child_part(context, command, fds));
	else
		return (parent_part(context, str, fds, cpid));
}

int			sh_expansions_cmd_subst_process(t_context *context,
				t_expansion *exp)
{
	char	*str;
	int		ret;

	(void)context;
	(void)exp;
	ret = SUCCESS;
	if ((ret = get_subshell_output(context, exp->expansion, &str)))
	{
		if (str)
			free(str);
		return (ret);
	}
	if (!(exp->res = ft_dy_str_new_str(str)))
	{
		free(str);
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_cmd_subs_process"));
	}
	free(str);
	return (SUCCESS);
}
