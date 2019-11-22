/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools_io_file.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 04:55:29 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/21 20:21:08 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_process_file_output(char *filename,
		t_context *context, int options)
{
	struct stat st;
	int			fd;

	fd = 42;
	if (ft_strlen(filename) > MAX_FILENAME_LEN)
		fd = sh_perror_err(SH_ERR1_FILENAME_LEN, filename);
	if (stat(filename, &st) != -1)
	{
		if (S_ISDIR(st.st_mode))
			fd = sh_perror_err(SH_ERR1_IS_DIR, filename);
		else if (access(filename, R_OK))
			fd = sh_perror_err(SH_ERR1_PERM_DENIED, filename);
	}
	if (fd == ERROR)
		return (ERROR);
	if ((fd = open(filename, options, 0644)) < 0)
		return (sh_perror_err("open: error while opening", filename));
	return (sh_add_redirection_file(OUTPUT, context, fd));
}

int		sh_process_file_input(char *filename,
		t_context *context, int options)
{
	struct stat st;
	int			fd;

	fd = 42;
	if (ft_strlen(filename) > MAX_FILENAME_LEN)
	{
		return (sh_perror_err(SH_ERR1_FILENAME_LEN, filename));
	}
	if (access(filename, F_OK))
		fd = sh_perror(filename, SH_ERR2_NO_SUCH_FILE_OR_DIR);
	if (stat(filename, &st) == -1)
		return (ERROR);
	else if (access(filename, R_OK))
		fd = sh_perror_err(SH_ERR1_PERM_DENIED, filename);
	if (fd == ERROR)
		return (ERROR);
	if ((fd = open(filename, options)) < 0)
		return (sh_perror_err("open: error while opening", filename));
	return (sh_add_redirection_file(INPUT, context, fd));
}
