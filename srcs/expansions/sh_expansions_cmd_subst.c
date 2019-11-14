/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_cmd_subst.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:29:58 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/14 10:49:00 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_expansions_cmd_subst_detect_backquotes(char *start)
{
    int     i;
    int     quoted;
    int     back_quote;

	if (start[0] != '`')
        return (-1);
	quoted = 0;
    back_quote = 1;
    i = 1;
    while (start[i] && back_quote > 0)
    {
        if (start[i] == '\\' && start[i + 1])
            i += 1;
        else if (!quoted && (start[i] == '\'' || start[i] == '"'))
            quoted = start[i];
        else if (quoted && start[i] == quoted)
            quoted = 0;
        else if (!quoted && start[i] == '`')
            back_quote--;
        i++;
    }
    if (!start[i] && back_quote > 0)
        return (-1);
    return (i);
}

int			sh_expansions_cmd_subst_detect_dollar(char *start)
{
    int     i;
    int     quoted;
    int     parenthesis;

	quoted = 0;
	if (start[0] != '$' || start[1] != '(')
        return (-1);
    parenthesis = 1;
    i = 2;
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

int			sh_expansions_cmd_subst_fill(t_expansion *exp, char *start)
{
    int     i;
	int		pattern_len;

	i = -1;
	if (start[0] == '`')
	{
		i = sh_expansions_cmd_subst_detect_backquotes(start);
		pattern_len = 1;
	}
	else if (start[0] == '$' && start[1] == '(')
	{
		i = sh_expansions_cmd_subst_detect_dollar(start);
		pattern_len = 2;
	}
	if (i == -1)
		return (ERROR);
    if (!(exp->original = ft_strndup(start, i)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_cmd_subst_fill (1)"));
	if (!(exp->expansion = ft_strndup(start + pattern_len, i - pattern_len - 1)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_cmd_subst_fill (2)"));
	exp->type = EXP_CMD_SUBST;
	exp->process = &sh_expansions_cmd_subst_process;
	return (SUCCESS);

}

static int get_string_process_gnl_returns(t_gnl_info *info, char **res)
{
	if (info->separator == E_SEPARATOR_NL)
	{
		if (*res == NULL)
		{
			if (!(*res = ft_strjoin(info->line, "\n")))
				return (sh_perror(SH_ERR1_MALLOC, "get_string_from_fd"));
		}
		else if (!(*res = ft_strjoin_3_free(*res, "\n", info->line)))
			return (sh_perror(SH_ERR1_MALLOC, "get_string_from_fd"));
	}
	else if (info->separator == E_SEPARATOR_EOF)
	{
		if (*res == NULL)
		{
			if (!(*res = ft_strdup(info->line)))
				return (sh_perror(SH_ERR1_MALLOC, "get_string_from_fd"));
		}
		else if (!(*res = ft_strjoin_free(*res, info->line, 1)))
			return (sh_perror(SH_ERR1_MALLOC, "get_string_from_fd"));
	}
	else
		return (sh_perror(SH_ERR1_UNEXPECTED_EOF, "get_string_from_fd"));
	return (SUCCESS);
}

char	*get_string_from_fd(int fd)
{
	t_gnl_info	info;
	int			ret;
	char		*res;

	res = NULL;
	while ((ret = get_next_line2(fd, &info, BUFF_SIZE)) > 0)
	{
		if (get_string_process_gnl_returns(&info, &res))
		{
			free(info.line);
			return (NULL);
		}
		free(info.line);
	}
	free(info.line);
	if (!res)
	{
		if (!(res = ft_strnew(0)))
			return (sh_perrorn(SH_ERR1_MALLOC, "get_string_from_fd"));
	}
	return (res);
}

char 	*get_subshell_output(t_shell *shell, char *command)
{
	pid_t	child;
	char	*str;
	int		fds[2];
	int		ret;

	if (pipe(fds))
		return (sh_perrorn(SH_ERR1_PIPE, "get_subshell_output"));
	if ((child = fork()) == -1)
		return (sh_perrorn(SH_ERR1_FORK, "get_subshell_output"));
	if (child == 0)
	{
		g_job_ctrl->interactive = 1;
		if (sh_pre_execution() != SUCCESS)
			exit (FAILURE);
		g_job_ctrl->interactive = 0;
		signal(SIGINT, handle_int);
		if (dup2(fds[PIPE_IN], STDOUT_FILENO) < 0)
			return (sh_perrorn(SH_ERR1_INTERN_ERR, "get_subshell_output"));
		close(fds[PIPE_OUT]);
		ret = execute_command(shell, command, 0);
		close(fds[PIPE_IN]);
		g_job_ctrl->interactive = 1;
		if (sh_post_execution() != SUCCESS)
			exit (FAILURE);
		sh_free_all(shell);
		exit(ret);
	}
	else
	{
		//{ child => PID du subshell }
		close(fds[PIPE_IN]);
//		waitpid(child, &ret, 0);
		str = get_string_from_fd(fds[PIPE_OUT]);
		close(fds[PIPE_OUT]);
		return (str);
	}
}

int			sh_expansions_cmd_subst_process(t_context *context,
				t_expansion *exp)
{
	char *str;

	// insert your code here
	// need to fill exp->res field (!! it is ft_dy_str)
	// This res will later replace the exp->original string in the token value
	(void)context;
	(void)exp;
	if (!(str = get_subshell_output(context->shell, exp->expansion)))
		return (FAILURE);
//	ft_dprintf(2, "command substitution detected : \n\t");
//	t_expansion_show(exp);
	if (!(exp->res = ft_dy_str_new_str(str)))
	{
		free(str);
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_cmd_subs_process"));
	}
	free(str);
	return (SUCCESS);
}
