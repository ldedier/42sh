/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_cmd_subst_tools.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 05:44:20 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/23 11:04:27 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_expansions_cmd_subst_detect_backquotes(char *start)
{
	int	i;
	int	quoted;
	int	back_quote;

	if (start[0] != '`')
		return (-1);
	quoted = 0;
	back_quote = 1;
	i = 0;
	while (start[++i] && back_quote > 0)
	{
		if (start[i] == '\\' && start[i + 1])
			i += 1;
		else if (!quoted && (start[i] == '\'' || start[i] == '"'))
			quoted = start[i];
		else if (quoted && start[i] == quoted)
			quoted = 0;
		else if (!quoted && start[i] == '`')
			back_quote--;
	}
	if (!start[i] && back_quote > 0)
		return (-1);
	return (i);
}

int			sh_expansions_cmd_subst_detect_dollar(char *start)
{
	int	i;
	int	quoted;
	int	parenthesis;

	quoted = 0;
	if (start[0] != '$' || start[1] != '(')
		return (-1);
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

int			sh_expansions_cmd_subst_fill(t_expansion *exp, char *start)
{
	int		i;
	int		patternlen;

	i = -1;
	if (start[0] == '`')
	{
		i = sh_expansions_cmd_subst_detect_backquotes(start);
		patternlen = 1;
	}
	else if (start[0] == '$' && start[1] == '(')
	{
		i = sh_expansions_cmd_subst_detect_dollar(start);
		patternlen = 2;
	}
	if (i == -1)
		return (ERROR);
	if (!(exp->original = ft_strndup(start, i)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_cmd_subst_fill (1)"));
	if (!(exp->expansion = ft_strndup(start + patternlen, i - patternlen - 1)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_cmd_subst_fill (2)"));
	exp->type = EXP_CMD_SUBST;
	exp->process = &sh_expansions_cmd_subst_process;
	return (SUCCESS);
}

static int	get_string_process_gnl_returns(t_gnl_info *info, char **res)
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

char		*get_string_from_fd(int fd)
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
