/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:35:27 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/12 04:55:25 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TRAVERSE_H
# define SH_TRAVERSE_H

# include "sh_21.h"

# define MAX_FILENAME_LEN	255

typedef struct dirent		t_dirent;
typedef struct s_heredoc	t_heredoc;
typedef char *(*t_heredoc_func)(const char *);

struct				s_heredoc
{
	char			*stop;
	int				*apply_expansion;
	t_heredoc_func	func;
};
/*
********************************************************************************
*/

/*
** sh_traverse.c
*/
int		sh_process_traverse(t_shell *shell, t_ast_node *ast_root);

/*
** sh_traverse_and_or.c
*/
int		sh_traverse_and_or(t_ast_node *node, t_context *context);

/*
** sh_traverse_assignment_word.c
*/
int		sh_traverse_assignment_word(t_ast_node *node, t_context *context);

/*
** sh_traverse_cmd_name.c
*/
int		sh_traverse_cmd_name(t_ast_node *node, t_context *context);

/*
** sh_traverse_cmd_prefix.c
*/
int		sh_traverse_cmd_prefix(t_ast_node *node, t_context *context);

/*
** sh_traverse_cmd_suffix.c
*/
int		sh_traverse_cmd_suffix(t_ast_node *node, t_context *context);

/*
** sh_traverse_cmd_word.c
*/
int		sh_traverse_cmd_word(t_ast_node *node, t_context *context);

/*
** sh_traverse_command.c
*/
int		sh_traverse_command(t_ast_node *node, t_context *context);

/*
** sh_traverse_default.c
*/
int		sh_traverse_default(t_ast_node *node, t_context *context);

/*
** sh_traverse_io_file.c
*/
int		sh_traverse_io_file(t_ast_node *node, t_context *context);

/*
** sh_traverse_io_here.c
*/
int		sh_traverse_io_here(t_ast_node *node, t_context *context);

/*
** sh_traverse_io_here_canonical.c
*/
char	*heredoc_canonical_mode(
	t_shell *shell, char *eof, t_heredoc heredoc_data, int *ret);

/*
** sh_traverse_io_redirect.c
*/
int		sh_traverse_io_redirect(t_ast_node *node, t_context *context);

/*
** sh_traverse_list.c
*/
int		sh_traverse_list(t_ast_node *node, t_context *context);

/*
** sh_traverse_pipe_sequence.c
*/
int		sh_traverse_pipeline(t_ast_node *node, t_context *context);

/*
** sh_traverse_semicol.c
*/
int		sh_traverse_semicol(
	t_ast_node *node_to_execute, t_context *context);

/*
** sh_traverse_simple_command.c
*/
int		sh_traverse_simple_command(t_ast_node *node, t_context *context);

/*
** sh_traverse_subshell.c
*/
int		sh_traverse_subshell(t_ast_node *node, t_context *context);

#endif
