/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_file_tools.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 04:55:29 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/09 10:59:47 by jdugoudr         ###   ########.fr       */
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
		return (sh_perror_err("Can't create file", filename));
	if (sh_add_redirection_file(OUTPUT, context->redirected_fd, fd,
		&context->redirections))
		return (FAILURE);
	return (SUCCESS);
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
		fd = sh_perror(SH_ERR2_NO_SUCH_FILE_OR_DIR, filename);
	if (stat(filename, &st) == -1)
		return (ERROR);
	else if (access(filename, R_OK))
		fd = sh_perror_err(SH_ERR1_PERM_DENIED, filename);
	if (fd == ERROR)
		return (ERROR);
	if ((fd = open(filename, options)) < 0)
		return (sh_perror("Can't open file", filename));
	if (sh_add_redirection_file(INPUT, context->redirected_fd, fd,
		&context->redirections))
		return (FAILURE);
	return (SUCCESS);
}
