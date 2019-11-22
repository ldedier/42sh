/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:47:31 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/20 12:52:25 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TRAVERSE_TOOLS_H
# define SH_TRAVERSE_TOOLS_H

/*
********************************************************************************
*/

/*
** sh_traverse_tools_browse.c
*/
long	sh_traverse_tools_browse(t_ast_node *node, t_context *context);
long	sh_traverse_tools_search(t_ast_node *node, int searched_symbol_id);

/*
** sh_traverse_tools_browse_redirection.c
*/
int		loop_traverse_redirection(t_ast_node *node, t_context *context);
int		loop_traverse_compound_redirection(
	t_ast_node *node, t_context *context);
long	sh_traverse_tools_browse_redirection(
	t_ast_node *node, t_context *context);

/*
** sh_traverse_tools_compound.c
*/
long	sh_traverse_tools_search_term(
	t_ast_node *node, t_context *context);
long	sh_traverse_tools_compound_redir(
	t_ast_node *node,
	t_context *context,
	t_ast_node **compound_redir,
	t_list **lst_redi);

/*
** sh_traverse_tools_debug.c
*/
char	*t_phase_name(t_phase phase);
char	*ret_to_str(int ret);
void	sh_traverse_tools_show_traverse_start(
	t_ast_node *node, t_context *context);
void	sh_traverse_tools_show_traverse_ret_value(
	t_ast_node *node, t_context *context, int ret);

/*
** sh_traverse_tools_get_exec_node.c
*/
int		get_node_to_exec(
	t_ast_node *node,
	t_context *context,
	t_symbol_id symbol,
	int (*f)(t_ast_node *,
	t_ast_node *,
	t_context *));

/*
** sh_traverse_tools_get_heredoc.c
*/
char	*get_heredoc(
	t_context *context, t_heredoc *heredoc_data, int *ret);

/*
** sh_traverse_tools_get_separator.c
*/
int		sh_get_separator_op(
	t_ast_node *to_execute, t_ast_node *separator, t_context *context);
int		sh_get_separator(
	t_ast_node *to_execute, t_ast_node *separator, t_context *context);

/*
** sh_traverse_tools_io_file.c
*/
int		sh_process_file_output(
	char *filename, t_context *context, int options);
int		sh_process_file_input(
	char *filename, t_context *context, int options);

/*
** sh_traverse_tools_io_here_expansion.c
*/
long	sh_traverse_io_here_phase_expansion(
	t_ast_node *node, t_context *context);

/*
** sh_traverse_tools_io_here_redirection.c
*/
long	sh_traverse_tools_io_here_redirection(
	t_ast_node *node, t_context *context);

/*
** sh_traverse_tools_simple_command.c
*/
long	sh_traverse_sc_search_in_hash(t_context *context);
long	sh_traverse_sc_search_in_path(t_context *context);

/*
** sh_traverse_tools_simple_command_check_perm.c
*/
int		check_for_symlink_loop(struct stat *st, char *path, int i);
long	sh_traverse_sc_check_perm_quiet(char *path);
long	sh_traverse_sc_check_perm(
	t_context *context, char *path, char *command_name);

#endif
