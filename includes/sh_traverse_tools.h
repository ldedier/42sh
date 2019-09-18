/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:47:31 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/28 17:51:15 by jmartel          ###   ########.fr       */
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
int		sh_traverse_tools_browse(t_ast_node *node, t_context *context);
// int		sh_traverse_tools_browse(
	// t_ast_node *node, t_context *context, int (*func)(t_ast_node *, t_context *));
int		sh_traverse_tools_search(t_ast_node *node, int searched_symbol_id);

/*
** sh_traverse_tools_reset.c
*/
void	sh_traverse_tools_reset_context(t_context *context);
void	sh_traverse_tools_reset_params(t_context *context);

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
** sh_traverse_tools_io_file.c
*/
int		sh_process_file_output(
	char *filename, t_context *context, int options);
int		sh_process_file_input(
	char *filename, t_context *context, int options);

/*
** sh_traverse_tools_get_heredoc.c
*/
char	*get_heredoc(
	t_context *context, t_heredoc *heredoc_data, int *ret);

/*
** sh_traverse_tools_simple_command_check_perm.c
*/
int		sh_traverse_sc_check_perm_quiet(char *path);
int		sh_traverse_sc_check_perm(
	t_context *context, char *path, char *command_name);

/*
** sh_traverse_tools_simple_command.c
*/
int		sh_traverse_sc_search_in_hash(t_context *context);
int		sh_traverse_sc_search_in_path(t_context *context);

/*
** sh_traverse_tools_io_here_expansion.c
*/
int		sh_traverse_io_here_phase_expansion(
			t_ast_node *node, t_context *context);

/*
** sh_traverse_tools_io_here_redirection.c
*/
int 	sh_traverse_tools_io_here_redirection(
	t_ast_node *node, t_context *context);

#endif
