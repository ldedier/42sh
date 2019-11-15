/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_cmd_subst.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:29:58 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/15 12:06:15 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	child_part(t_context *context, char *command, int fds[])
{
	int	ret;
	
	(void)ret;
	if (setpgid(getpid(), g_job_ctrl->shell_pgid) < 0)
		return (sh_perror("Could not add the process to a process group",
			"sh_expansions_subst"));
	ret = SUCCESS;
	g_job_ctrl->cmd_subst = 1;
	if (dup2(fds[PIPE_IN], STDOUT_FILENO) < 0)
		return (sh_perror(SH_ERR1_INTERN_ERR, "get_subshell_output"));
	close(fds[PIPE_OUT]);
	if (IS_FG(context->cmd_type))
		sh_pre_execution();
	ft_dprintf(g_term_fd, YELLOW"Prefix in Subst\n"EOC);
	g_job_ctrl->interactive = 0;
	reset_signals();
	ret = execute_command(context->shell, command, 0);
	g_job_ctrl->interactive = 1;
	close(fds[PIPE_IN]);
	sh_free_all(context->shell);
	return (context->shell->ret_value);
}

static int	parent_part(t_context *context, char **str, int fds[], int cpid)
{
	int	ret;

	if (setpgid(cpid, g_job_ctrl->shell_pgid) < 0)
		return (sh_perror("Could not add the process to a process group",
			"sh_expansions_subst"));
	ret = SUCCESS;
	close(fds[PIPE_IN]);
	signal(SIGINT, handle_int);
	waitpid(cpid, &ret, 0);
	ft_dprintf(g_term_fd, "Done waiting\n");
	sh_env_update_ret_value_wait_result(context, ret);
	sh_env_update_question_mark(context->shell);
	if (g_glob.command_line.interrupted ||
	(WIFSIGNALED(ret) && (WTERMSIG(ret) == SIGINT)))
	{
		ft_dprintf(g_term_fd, "Expantion Signaled\n");
		if (IS_FG(context->cmd_type))
			sh_post_execution();
		ft_dprintf(g_term_fd, YELLOW"Postix in Subst\n"EOC);
		close(fds[PIPE_OUT]);
		if ((*str = ft_strdup("")) == NULL)
			return (FAILURE);
		return (context->shell->ret_value);
	}
	ft_dprintf(g_term_fd, "Getting string from fd\n");
	if ((*str = get_string_from_fd(fds[PIPE_OUT])) == NULL)
		return (FAILURE);
	ft_dprintf(g_term_fd, "Got string from fd\n");
	if (IS_FG(context->cmd_type))
		sh_post_execution();
	ft_dprintf(g_term_fd, YELLOW"Postfix in Subst\n"EOC);
	close(fds[PIPE_OUT]);
	if (g_glob.command_line.interrupted)
	{
		ft_dprintf(g_term_fd, "Interrupted\n");
		free(*str);
		if ((*str = ft_strdup("")) == NULL)
			return (FAILURE);
		return (130);
	}
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
