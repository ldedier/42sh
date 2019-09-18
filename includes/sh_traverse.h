/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:35:27 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/05 11:41:04 by jdugoudr         ###   ########.fr       */
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
int		sh_process_traverse(t_shell *shell);

/*
** sh_traverse_list.c
*/
int		sh_traverse_list(t_ast_node *node, t_context *context);

/*
** sh_traverse_command.c
*/
int		sh_traverse_command(t_ast_node *ast, t_context *context);

/*
** sh_traverse_semicol.c
*/
int		sh_traverse_semicol(t_ast_node *node, t_context *context);

/*
** sh_traverse_and_or.c
*/
int		sh_traverse_and_or(t_ast_node *node, t_context *context);

/*
** sh_traverse_pipe_sequence.c
*/
int		sh_traverse_pipeline(t_ast_node *node, t_context *context);


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
// int		test_field_splitting_function(t_ast_node *child, t_list **ptr);
int		sh_traverse_cmd_suffix(t_ast_node *node, t_context *context);

/*
** sh_traverse_cmd_word.c
*/
int		sh_traverse_cmd_word(t_ast_node *node, t_context *context);

/*
** sh_traverse_dgreat.c
*/
int		sh_traverse_simple_command(t_ast_node *node, t_context *context);
// int		sh_traverse_dgreat(t_ast_node *node, t_context *context);

/*
** sh_traverse_io_file.c
*/
int		sh_traverse_io_file(t_ast_node *node, t_context *context);

/*
** sh_traverse_io_here.c
*/
char	*heredoc_dash(const char *str);
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
** sh_traverse_default.c
*/
int		sh_traverse_default(t_ast_node *node, t_context *context);

#endif
