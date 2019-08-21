/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_perror.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:16:12 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/06 19:37:58 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PERROR_H
# define SH_PERROR_H

# include "sh_21.h"

# define SH_NAME		"21sh"
# define SH_ERR_COLOR	COLOR_PINK

# define SH_ERR1_MALLOC			"Malloc error occured"
# define SH_ERR1_ENV_NOT_SET	"Environnement variable is not set"
# define SH_ERR1_TERM_CPY		"Could not copy terminal attributes"
# define SH_ERR1_INTERN_ERR		"System internal error"
# define SH_ERR1_FORK			"Could not fork, too many processes are running"
# define SH_ERR1_CMD_NOT_FOUND	"Command not found"
# define SH_ERR1_HISTORIC		"Could not open the historic file"
# define SH_ERR1_PERM_DENIED	"Permission denied"
# define SH_ERR1_TOO_MANY_ARGS	"Too many arguments"
# define SH_ERR1_NOT_A_DIR		"Not a directory"
# define SH_ERR1_BAD_FD			"Bad file descriptor"
# define SH_ERR1_IS_DIR			"Is a directory"
# define SH_ERR1_UNEXPECTED_EOF	"Unexpected EOF"
# define SH_ERR1_PIPE			"Pipe error"
# define SH_ERR1_IOCTL			"Ioctl error"
# define SH_ERR1_READ			"Read error"
# define SH_ERR1_EXECVE_FAIL	"Cannot execute binary file: Exec format error"

# define SH_ERR2_NO_SUCH_FILE_OR_DIR	"No such file or directory"
# define SH_ERR2_INVALID_OPT			"Invalid option"
# define SH_ERR2_TOO_MANY_SYMLINK		"Too many levels of symbolic links"

/*
********************************************************************************
*/

/*
** sh_perror_fd.c
*/
int		sh_perror2_fd(
	int fd, const char *error, const char *prefix, const char *suffix);
int		sh_perror_fd(int fd, const char *error, const char *suffix);

/*
** sh_perror.c
*/
int		sh_perror(const char *error, const char *suffix);
int		sh_perror_err(const char *error, const char *suffix);
void	*sh_perrorn(const char *error, const char *suffix);
int		sh_perror_err_fd(int fd, const char *error, const char *suffix);
void	*sh_perrorn_fd(int fd, const char *error, const char *suffix);

/*
** sh_perror2.c
*/
int		sh_perror2(
	const char *error, const char *prefix, const char *suffix);
int		sh_perror2_err(
	const char *error, const char *prefix, const char *suffix);
void	*sh_perror2n(
	const char *error, const char *prefix, const char *suffix);
int		sh_perror2_err_fd(
	int fd, const char *error, const char *prefix, const char *suffix);
void	*sh_perror2n_fd(
	int fd, const char *error, const char *prefix, const char *suffix);

#endif
