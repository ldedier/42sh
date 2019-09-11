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
** sh_traverse_pipe_sequence_execute.c
*/
int		sh_traverse_pipe_sequence_execute(
	t_ast_node *node, t_context *context);

/*
** sh_traverse_io_here.c
*/
char	*heredoc_dash(const char *str);
int		sh_traverse_io_here(t_ast_node *node, t_context *context);

/*
** sh_traverse_cmd_word.c
*/
int		sh_traverse_cmd_word(t_ast_node *node, t_context *context);

/*
** sh_traverse_lessgreat.c
*/
int		sh_traverse_lessgreat(t_ast_node *node, t_context *context);

/*
** sh_traverse_io_here_phase_expansion.c
*/
int		sh_traverse_io_here_phase_expansion(
	t_redirection *redirection, t_ast_node *node, t_context *context);

/*
** sh_traverse_list.c
*/
int		sh_traverse_list(t_ast_node *node, t_context *context);

/*
** sh_traverse_io_here_canonical.c
*/
void	populate_command_line(t_command_line *command_line, char *str);
int		heredoc_canonical_mode_eof(char *eof, char **res);
char	*heredoc_gnl_error(int *ret, char **res);
char	*heredoc_canonical_mode(
	t_shell *shell, char *eof, t_heredoc heredoc_data, int *ret);

/*
** sh_traverse_simple_command.c
*/
int		sh_traverse_sc_slash_cmd(t_context *context, int *ret);
int		sh_traverse_simple_command_exec(
	t_ast_node *node, t_context *context);
int		sh_traverse_simple_command_no_exec(
	t_ast_node *node, t_context *context);
int		sh_traverse_sc_no_slash_cmd(t_context *context);
int		sh_traverse_simple_command(t_ast_node *node, t_context *context);

/*
** sh_traverse_io_file.c
*/
int		get_io_file_return(
	t_ast_node *redir_child, char *filename, t_context *context);
int		sh_traverse_io_file(t_ast_node *node, t_context *context);

/*
** sh_traverse_default.c
*/
int		sh_traverse_default(t_ast_node *node, t_context *context);

/*
** sh_traverse_cmd_prefix.c
*/
int		sh_traverse_cmd_prefix(t_ast_node *node, t_context *context);

/*
** sh_traverse_cmd_suffix.c
*/
int		test_field_splitting_function(t_ast_node *child, t_list **ptr);
int		sh_traverse_cmd_suffix(t_ast_node *node, t_context *context);

/*
** sh_traverse_dgreat.c
*/
int		sh_traverse_dgreat(t_ast_node *node, t_context *context);

/*
** sh_traverse_io_redirect.c
*/
int		sh_traverse_io_redirect(t_ast_node *node, t_context *context);

/*
** sh_traverse_cmd_name.c
*/
int		sh_traverse_cmd_name(t_ast_node *node, t_context *context);

/*
** sh_traverse_io_here_expansion.c
*/
int		sh_traverse_io_here_expansion(
	char **str, int *cursor, t_context *context);

/*
** sh_traverse_io_file_tools.c
*/
void	set_failed_command(t_context *context);
int		sh_process_file_output(
	char *filename, t_context *context, int options);
int		sh_process_file_input(
	char *filename, t_context *context, int options);

/*
** sh_traverse.c
*/
int		sh_process_traverse(t_shell *shell);

/*
** sh_traverse_and_or.c
*/
int		sh_traverse_and_or_launch_phase(
	t_ast_node *node, t_context *context);
int		sh_traverse_and_or(t_ast_node *node, t_context *context);

/*
** sh_traverse_simple_command_check_perm.c
*/
int		sh_traverse_sc_check_perm_quiet(char *path);
int		sh_traverse_sc_check_perm(
	t_context *context, char *path, char *command_name);

/*
** sh_traverse_pipe_sequence.c
*/
int		sh_traverse_pipe_sequence(t_ast_node *node, t_context *context);

/*
** sh_traverse_simple_command_tools.c
*/
int		sh_found_sc_search_in_hash(
	t_context *context, t_binary *binary, t_hash_finder finder);
int		sh_traverse_sc_search_in_hash(t_context *context);
int		sh_traverse_sc_search_in_dir(
	char *path, DIR *dir, t_context *context);
int		sh_traverse_sc_search_in_path(t_context *context);

/*
** sh_traverse_semicol.c
*/
int		sh_traverse_semicol(t_ast_node *node, t_context *context);

/*
** sh_traverse_lessand.c
*/
int		sh_traverse_lessand(t_ast_node *node, t_context *context);

/*
** sh_traverse_assignment_word.c
*/
int		sh_traverse_assignment_word(t_ast_node *node, t_context *context);

#endif
