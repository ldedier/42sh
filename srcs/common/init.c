/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 13:19:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/23 03:08:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static char	*refine_history_entry(char *entry)
{
	int		len;
	char	*new;
	int		i;
	int		char_len;

	i = 0;
	len = ft_strlen(entry);
	if (!(new = ft_strnew(len)))
		return (sh_perrorn(SH_ERR1_MALLOC, "refine_history_entry"));
	while (entry[i])
	{
		if ((char_len = get_char_len2(i, len, (unsigned char *)entry)) == -1)
		{
			new[i] = ' ';
			i++;
		}
		else
		{
			ft_strncpy(&new[i], &entry[i], char_len);
			i += char_len;
		}
	}
	return (new);
}

static int	process_read_history(t_history *history, t_gnl_info info)
{
	char *res;

	if (info.separator == E_SEPARATOR_NL || info.separator == E_SEPARATOR_EOF)
	{
		if (!(res = refine_history_entry(info.line)))
		{
			free(info.line);
			return (FAILURE);
		}
		free(info.line);
		if (sh_append_to_history(history, res, 0))
		{
			free(res);
			return (FAILURE);
		}
		free(res);
		return (SUCCESS);
	}
	else
	{
		free(info.line);
		return (sh_perror(SH_ERR1_UNEXPECTED_EOF, "sh_init_history (2)"));
	}
}

static int	sh_init_history(t_history *history)
{
	int			fd;
	int			ret;
	t_gnl_info	info;

	history->commands = NULL;
	history->nb_entries = 0;
	history->from = -1;
	history->to = -1;
	if ((fd = open(PATH"/"HISTORY_FILE, O_CREAT | O_RDWR
		| O_NOFOLLOW, S_IRWXU)) == -1)
		return (sh_perror(SH_ERR1_HISTORY, "sh_init_history (2)"));
	while ((ret = get_next_line2(fd, &info, BUFF_SIZE)) == 1)
	{
		if (process_read_history(history, info) != SUCCESS)
			return (FAILURE);
	}
	if (ret == -1)
		return (FAILURE);
	free(info.line);
	history->head_start.next = history->commands;
	history->head_start.prev = NULL;
	history->head = &history->head_start;
	close(fd);
	return (SUCCESS);
}

int			sh_init_allocations(t_shell *shell, char **env)
{
	if (!(shell->alias = ft_dy_tab_new(5)))
		return (FAILURE);
	if (sh_main_init_env(shell, env) == FAILURE)
		return (FAILURE);
	if (sh_main_init_vars(shell) == FAILURE)
		return (FAILURE);
	if (sh_init_command_line(shell, &g_glob.command_line) != SUCCESS)
		return (FAILURE);
	shell->running = 1;
	if (sh_init_parsing_posix(&shell->parser) != SUCCESS)
		return (FAILURE);
	if (sh_init_parsing_arithmetic(&shell->parser_ar) != SUCCESS)
		return (FAILURE);
	if ((sh_init_history(&shell->history)) != SUCCESS)
		return (FAILURE);
	if (!(shell->binaries = ft_hash_table_new(BINARIES_TABLE_SIZE)))
		return (FAILURE);
	return (SUCCESS);
}

int			sh_init_shell(t_shell *shell, char **env)
{
	struct termios s;

	s = shell->term;
	ft_bzero(shell, sizeof(t_shell));
	ft_bzero(&g_glob.command_line, sizeof(t_command_line));
	g_glob.command_line.fd = -1;
	if (isatty(0))
		if (ioctl(0, TIOCGWINSZ, &g_glob.winsize) == -1)
			return (sh_perror(SH_ERR1_IOCTL, "sh_init_shell"));
	shell->term = s;
	shell->ret_value = 0;
	shell->ret_value_set = 0;
	if (sh_init_allocations(shell, env) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
