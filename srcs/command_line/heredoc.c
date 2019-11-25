/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 19:14:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/25 10:16:22 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			process_heredoc_new_line(char **res, char *tmp, t_shell *shell,
				t_command_line *command_line)
{
	char *to_compare;

	if (!(to_compare = command_line->to_append_str ?
			ft_strjoin(command_line->to_append_str, tmp) : ft_strdup(tmp)))
	{
		free(tmp);
		ft_strdel(&command_line->to_append_str);
		return (heredoc_ret(shell, command_line, FAILURE));
	}
	free(tmp);
	if (!ft_strcmp(to_compare, command_line->heredoc_eof))
	{
		free(to_compare);
		ft_strdel(&command_line->to_append_str);
		return (heredoc_ret(shell, command_line, SUCCESS));
	}
	else
	{
		ft_strdel(&command_line->to_append_str);
		if (!(*res = ft_strjoin_free(*res, to_compare, 3)))
			return (heredoc_ret(shell, command_line, FAILURE));
		if (!(*res = ft_strjoin_free(*res, "\n", 1)))
			return (heredoc_ret(shell, command_line, FAILURE));
	}
	return (KEEP_READ);
}

int			process_heredoc_through_command(char **res, t_shell *shell,
	t_heredoc heredoc_data, t_command_line *command_line)
{
	char	*tmp;
	int		ret;
	int		to_append;

	if (!(tmp = heredoc_data.func(command_line->dy_str->str)))
		return (heredoc_ret(shell, command_line, FAILURE));
	if ((to_append = (refine_heredoc(tmp,
			*(heredoc_data.apply_expansion)))) == 0)
	{
		if ((ret = process_heredoc_new_line(res, tmp, shell, command_line))
			!= KEEP_READ)
			return (ret);
	}
	else
	{
		if (append_to_str(&command_line->to_append_str, tmp))
		{
			free(tmp);
			ft_strdel(&command_line->to_append_str);
			return (heredoc_ret(shell, command_line, FAILURE));
		}
		free(tmp);
	}
	return (3);
}

void		init_heredoc_command_line(t_shell *shell,
				t_command_line *command_line, char *stop)
{
	command_line->heredoc_eof = stop;
	flush_command_line(command_line);
	render_command_line(command_line, -g_glob.cursor, 1);
	command_line->context = E_CONTEXT_HEREDOC;
	update_prompt(shell, command_line);
}

char		*heredoc_handle_ctrl_d(t_shell *shell,
				char *stop, char **res, int *ret)
{
	t_command_line *command_line;

	command_line = &g_glob.command_line;
	if (command_line->to_append_str)
	{
		if (ft_strcmp(command_line->to_append_str, stop))
		{
			if (!(*res = ft_strjoin_free(*res, command_line->to_append_str, 1)))
				return (heredoc_ret_str(shell, command_line, NULL));
			if (!(*res = ft_strjoin_free(*res, "\n", 1)))
				return (heredoc_ret_str(shell, command_line, NULL));
		}
		else
		{
			*ret = SUCCESS;
			return (heredoc_ret_str(shell, command_line, *res));
		}
	}
	return (heredoc_ret_str(shell, command_line, *res));
}

char		*heredoc(t_shell *shell, t_heredoc heredoc, int *ret)
{
	char			*res;
	t_command_line	*command_line;

	command_line = &g_glob.command_line;
	init_heredoc_command_line(shell, command_line, heredoc.stop);
	if (!(res = ft_strnew(0)))
		return (heredoc_ret_str(shell, command_line, NULL));
	while ((*ret = sh_get_command(shell, command_line)) == SUCCESS)
	{
		if (process_heredoc_through_command(&res, shell, heredoc,
			command_line) != 3)
			return (res);
	}
	if (*ret == CTRL_C)
	{
		command_line->interrupted = 1;
		ft_strdel(&command_line->to_append_str);
	}
	if (*ret == CTRL_D)
		return (heredoc_handle_ctrl_d(shell, heredoc.stop, &res, ret));
	else
	{
		free(res);
		return (heredoc_ret_str(shell, command_line, NULL));
	}
}
