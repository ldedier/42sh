/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_proc_subst_in.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:29:58 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/15 09:13:33 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_expansions_proc_subst_in_detect(char *start)
{
    int     i;
    int     quoted;
    int     parenthesis;

	i = 0;
	ft_dprintf(2, "start : %s\n", start);
	if (start[0] != '>' || start[1] != '(')
        return (-1);
	quoted = 0;
	i = 2;
    parenthesis = 1;
    while (start[i] && parenthesis > 0)
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
        i++;
    }
    if (!start[i] && parenthesis > 0)
        return (-1);
    return (i);
}

int			sh_expansions_proc_subst_in_fill(t_expansion *exp, char *start)
{
    int     i;

	i = sh_expansions_proc_subst_in_detect(start);
	if (i == -1)
		return (ERROR);
    if (!(exp->original = ft_strndup(start, i)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_proc_subst_in_fill (1)"));
	if (!(exp->expansion = ft_strndup(start + 2, i - 3)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_proc_subst_in_fill (2)"));
	exp->type = EXP_PROC_SUBST_IN;
	exp->process = &sh_expansions_proc_subst_in_process;
	return (SUCCESS);

}

char		*sh_get_fd_string(int fd)
{
	char *str;
	char *fd_str;

	if (!(fd_str = ft_itoa(fd)))
		return (sh_perrorn(SH_ERR1_MALLOC, "sh_get_fd_string"));
	if (!(str = ft_strjoin_free("/dev/fd/", fd_str, 2)))
		return (sh_perrorn(SH_ERR1_MALLOC, "sh_get_fd_string"));
	return (str);
}

char		*sh_get_process_subst_in(t_shell *shell, char *command,
				t_list **redirections)
{
	char	*str;
	int		fds[2];
	pid_t	child;
	int		ret;

	if (pipe(fds))
		return (sh_perrorn(SH_ERR1_PIPE, "sh_get_process_subst_in"));
	if ((child = fork()) == -1)
		return (sh_perrorn(SH_ERR1_FORK, "sh_get_process_subst_in"));
	if (child == 0)
	{
	//	if (dup2(fds[PIPE_OUT], g_term_fd) < 0)
	//	ft_printf("child pid: %zu\n", getpid());
		if (dup2(fds[PIPE_OUT], STDIN_FILENO) < 0)
			return (sh_perrorn(SH_ERR1_INTERN_ERR, "sh_get_process_subst_in"));
		close(fds[PIPE_IN]);
		ret = execute_command(shell, command, 0);
		close(fds[PIPE_OUT]);
	//	ft_printf("done pid: %zu\n", getpid());
		sh_free_all(shell);
		exit(ret);
	}
	else
	{
		//{ child => PID du subshell }
	//	ft_printf("shell pid: %zu\n", getpid());
		close(fds[PIPE_OUT]);
		if (!(str = sh_get_fd_string(fds[PIPE_IN])))
			return (NULL);
		(void)redirections;
		if (sh_add_redirection_pipe(fds[PIPE_IN], redirections))
		{
			free(str);
			return (NULL);
		}
		return (str);
	}
}

int			sh_expansions_proc_subst_in_process(t_context *context,
				t_expansion *exp)
{

	char *str;

	if (!(str = sh_get_process_subst_in(context->shell, exp->expansion,
		&context->redirections)))
	{
		return (FAILURE);
	}
	if (!(exp->res = ft_dy_str_new_str(str)))
	{
		free(str);
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_cmd_subs_process"));
	}
	free(str);
	return (SUCCESS);
}
