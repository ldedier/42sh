/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_commands_from_file.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 15:23:43 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/26 07:42:35 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		sh_process_read_canonical_gnl(t_shell *shell, t_gnl_info *info)
{
	int ret;

	if (info->separator != E_SEPARATOR_ZERO)
	{
		ft_printf("%s\n", info->line);
		if ((ret = execute_command(shell, info->line, 1)))
		{
			free(info->line);
			return (ret);
		}
	}
	else
	{
		free(info->line);
		return (sh_perror("Illegal characters received from input",
					"sh_process_read_canonical_gnl"));
	}
	free(info->line);
	return (ret);
}

int				sh_execute_commands_from_file(t_shell *shell, char *filename)
{
	int			gnl_ret;
	t_gnl_info	info;
	int			ret;
	int			fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (sh_perror(SH_ERR1_EDIT, "sh_execute_commands_from_edit_file"));
	gnl_ret = SUCCESS;
	while (shell->running && (gnl_ret = get_next_line2(fd, &info, 1)) == 1)
	{
		if ((ret = sh_process_read_canonical_gnl(shell, &info)))
		{
			close(fd);
			return (ret);
		}
	}
	if (gnl_ret == -1)
	{
		close(fd);
		return (sh_perror("get_next_line", "sh_execute_commands_from_file"));
	}
	if (shell->running)
		free(info.line);
	close(fd);
	return (SUCCESS);
}
