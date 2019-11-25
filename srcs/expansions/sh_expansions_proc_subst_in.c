/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_proc_subst_in.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:29:58 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/25 22:44:21 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_expansions_proc_subst_in_detect(char *start)
{
	int	i;
	int	quoted;
	int	parenthesis;

	if (start[0] != '>' || start[1] != '(')
		return (-1);
	quoted = 0;
	parenthesis = 1;
	i = 1;
	while (start[++i] && parenthesis > 0)
	{
		if (start[i] == '\\' && start[i + 1])
			i += 1;
		else if (!quoted && (start[i] == '\'' || start[i] == '"'))
			quoted = start[i];
		else if (quoted && start[i] == quoted)
			quoted = 0;
		else if (!quoted && start[i] == '(')
			parenthesis++;
		else if (!quoted && start[i] == ')')
			parenthesis--;
	}
	if (!start[i] && parenthesis > 0)
		return (-1);
	return (i);
}

int			sh_expansions_proc_subst_in_fill(t_expansion *exp, char *start)
{
	int	i;

	i = sh_expansions_proc_subst_in_detect(start);
	if (i == -1)
		return (ERROR);
	if (!(exp->original = ft_strndup(start, i)))
		return (sh_perror(SH_ERR1_MALLOC, "expansions_proc_subst_in_fill (1)"));
	if (!(exp->expansion = ft_strndup(start + 2, i - 3)))
		return (sh_perror(SH_ERR1_MALLOC, "expansions_proc_subst_in_fill (2)"));
	exp->type = EXP_PROC_SUBST_IN;
	exp->process = &sh_expansions_proc_subst_in_process;
	return (SUCCESS);
}

static void	sh_get_process_subst_in_child(
	t_shell *shell, char *command, int fds[2])
{
	int		ret;

	if (dup2(fds[PIPE_OUT], STDIN_FILENO) < 0)
	{
		sh_perrorn(SH_ERR1_INTERN_ERR, "sh_get_process_subst_in");
		exit(FAILURE);
	}
	close(fds[PIPE_IN]);
	g_job_ctrl->interactive = 0;
	free_execution_tools(&shell->exec->tokens, &shell->exec->ast_root,
		&shell->exec->cst_root);
	ft_strdel(&shell->hist_dup);
	ret = execute_command(shell, command, 0);
	g_job_ctrl->interactive = 1;
	close(fds[PIPE_OUT]);
	sh_free_all(shell);
	exit(ret);
}

static char	*sh_get_process_subst_in(t_shell *shell, char *command,
				t_list **redirections)
{
	char	*str;
	int		fds[2];
	pid_t	child;

	if (pipe(fds))
		return (sh_perrorn(SH_ERR1_PIPE, "sh_get_process_subst_in"));
	if ((child = fork()) == -1)
		return (sh_perrorn(SH_ERR1_FORK, "sh_get_process_subst_in"));
	if (child == 0)
		sh_get_process_subst_in_child(shell, command, fds);
	else
	{
		close(fds[PIPE_OUT]);
		if (!(str = sh_get_fd_string(fds[PIPE_IN])))
			return (NULL);
		if (sh_add_redirection_pipe(fds[PIPE_IN], redirections))
		{
			free(str);
			return (NULL);
		}
		return (str);
	}
	return (SUCCESS);
}

int			sh_expansions_proc_subst_in_process(t_context *context,
				t_expansion *exp)
{
	char *str;

	if (!(str = sh_get_process_subst_in(context->shell, exp->expansion,
		&context->redirections)))
		return (FAILURE);
	if (!(exp->res = ft_dy_str_new_str(str)))
	{
		free(str);
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_cmd_subs_process"));
	}
	free(str);
	return (SUCCESS);
}
