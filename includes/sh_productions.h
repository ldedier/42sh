/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_productions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 23:12:11 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/02 23:13:54 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PRODUCTIONS_H
# define SH_PRODUCTIONS_H

# include "sh_grammar.h"
# include "sh_parser.h"

/*
********************************************************************************
*/

/*
** sh_prod_do_group.c
*/
int		sh_init_prod_do_group(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_simple_command.c
*/
int		sh_init_prod_simple_command(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_io_file.c
*/
int		sh_init_prod_io_file(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_redirect_list.c
*/
int		sh_init_prod_redirect_list(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_compound_command.c
*/
int		sh_init_prod_compound_command(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_function_body.c
*/
int		sh_init_prod_function_body(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_case_clause.c
*/
int		sh_init_prod_case_clause(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_subshell.c
*/
int		sh_init_prod_subshell(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_name.c
*/
int		sh_init_prod_name(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_case_list.c
*/
int		sh_init_prod_case_list(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_brace_group.c
*/
int		sh_init_prod_brace_group(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_newline_list.c
*/
int		sh_init_prod_newline_list(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_if_clause.c
*/
int		sh_init_prod_if_clause(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_else_part.c
*/
int		sh_init_prod_else_part(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_pipe_sequence.c
*/
int		sh_init_prod_pipe_sequence(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_complete_command.c
*/
int		sh_init_prod_complete_command(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_cmd_word.c
*/
int		sh_init_prod_cmd_word(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_command.c
*/
int		sh_init_prod_command(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_wordlist.c
*/
int		sh_init_prod_wordlist(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_case_item_ns.c
*/
int		sh_init_prod_case_item_ns(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_fname.c
*/
int		sh_init_prod_fname(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_program.c
*/
int		sh_init_prod_program(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_separator.c
*/
int		sh_init_prod_separator(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_case_item.c
*/
int		sh_init_prod_case_item(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_here_end.c
*/
int		sh_init_prod_here_end(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_pipeline.c
*/
int		sh_init_prod_pipeline(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_filename.c
*/
int		sh_init_prod_filename(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_cmd_suffix.c
*/
int		sh_init_prod_cmd_suffix(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_compound_list.c
*/
int		sh_init_prod_compound_list(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_in.c
*/
int		sh_init_prod_in(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_cmd_name.c
*/
int		sh_init_prod_cmd_name(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_complete_commands.c
*/
int		sh_init_prod_complete_commands(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_while_clause.c
*/
int		sh_init_prod_while_clause(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_cmd_prefix.c
*/
int		sh_init_prod_cmd_prefix(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_until_clause.c
*/
int		sh_init_prod_until_clause(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_and_or.c
*/
int		sh_init_prod_and_or(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_for_clause.c
*/
int		sh_init_prod_for_clause(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_case_list_ns.c
*/
int		sh_init_prod_case_list_ns(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_io_redirect.c
*/
int		sh_init_prod_io_redirect(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_separator_op.c
*/
int		sh_init_prod_separator_op(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_pattern.c
*/
int		sh_init_prod_pattern(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_linebreak.c
*/
int		sh_init_prod_linebreak(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_list.c
*/
int		sh_init_prod_list(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_term.c
*/
int		sh_init_prod_term(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_io_here.c
*/
int		sh_init_prod_io_here(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_function_definition.c
*/
int		sh_init_prod_function_definition(t_cfg *cfg, t_symbol *symbol);

/*
** sh_prod_sequential_sep.c
*/
int		sh_init_prod_sequential_sep(t_cfg *cfg, t_symbol *symbol);

#endif
