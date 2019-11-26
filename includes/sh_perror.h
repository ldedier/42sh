/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_perror.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:16:12 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/26 08:50:57 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PERROR_H
# define SH_PERROR_H

# include "sh_21.h"

# define SH_NAME		"42sh"
# define SH_ERR_COLOR	COLOR_PINK

# define SH_ERR1_MALLOC			"Malloc error occured"
# define SH_ERR1_ENV_NOT_SET	"Environnement variable is not set"
# define SH_ERR1_TERM_CPY		"Could not copy terminal attributes"
# define SH_ERR1_INTERN_ERR		"System internal error"
# define SH_ERR1_FORK			"Could not fork, too many processes are running"
# define SH_ERR1_CMD_NOT_FOUND	"Command not found"
# define SH_ERR1_HISTORY		"Could not open the history file"
# define SH_ERR1_EDIT			"Could not open the edit file"
# define SH_ERR1_TTY			"Could not open the tty file descriptor"
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
# define SH_ERR1_FILENAME_LEN	"File name too long"
# define SH_ERR1_MAX_RECUR		"Maximum execution recursion depth reached"

# define SH_ERR1_EVENT_NOT_FOUND		"event not found"

# define SH_ERR2_NO_SUCH_FILE_OR_DIR	"No such file or directory"
# define SH_ERR2_INVALID_OPT			"Invalid option"
# define SH_ERR2_TOO_MANY_SYMLINK		"Too many levels of symbolic links"

# define SH_BLT_UNAREXP			"Unary operator expected"
# define SH_BLT_BINAREXP		"Binary operator expected"
# define SH_BLT_NOTWELLFORM		"Sorry your command are not well formatted"
# define SH_BLT_INTEGER			"Integer expression expected"
# define SH_BLT_HISTORY_RANGE	"fc: history specification out of range"
# define SH_BLT_NO_CMD_FOUND	"fc: no command found"

# define SH_BAD_SUBSTITUTE		"Bad subsitution"
# define SH_AMB_REDIRECT		"Ambigous redirect"

# define SH_ERR1_DIV_ZERO		"Division by 0"

typedef struct s_lexer			t_lexer;

/*
********************************************************************************
*/

/*
** sh_perror.c
*/
int		sh_perror(const char *error, const char *suffix);
int		sh_perror_err(const char *error, const char *suffix);
void	*sh_perrorn(const char *error, const char *suffix);
int		sh_perror_unexpected_eof(t_lexer *lexer);

/*
** sh_perror2.c
*/
int		sh_perror2(
	const char *error, const char *prefix, const char *suffix);
int		sh_perror2_err(
	const char *error, const char *prefix, const char *suffix);
void	*sh_perror2n(
	const char *error, const char *prefix, const char *suffix);

#endif
