/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_arithmetic.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 11:27:40 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/15 15:37:32 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_ARITHMETIC_H
# define SH_ARITHMETIC_H

#include "sh_21.h"

t_grammar_holder g_ar_grammar[NB_SYMBOLS_AR];

/*
********************************************************************************
*/

/*
** productions/sh_ar_prod_and_or.c
*/
int		sh_ar_init_prod_and_or(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_ar_prod_arithmetic.c
*/
int		sh_ar_init_prod_arithmetic(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_ar_prod_comparison.c
*/
int		sh_ar_init_prod_comparison(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_ar_prod_expr.c
*/
int		sh_ar_init_prod_expr(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_ar_prod_factor.c
*/
int		sh_ar_init_prod_factor(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_ar_prod_term.c
*/
int		sh_ar_init_prod_term(t_cfg *cfg, t_symbol *symbol);

/*
** sh_execute_arithmetic.c
*/
int		sh_traverse_arithmetic(t_ast_node *node, t_context *context);
int		sh_traverse_ar_root(t_context *context, t_ast_node *root);
int		sh_execute_arithmetic_fake(t_shell *shell, char *command);
int		sh_execute_arithmetic(t_context *context, char *command);

/*
** sh_lexer_arithmetic.c
*/
t_token	*t_token_integer(int value);
void	populate_test1(t_list **tokens, t_shell *shell);
void	populate_test2(t_list **tokens, t_shell *shell);
int		sh_lexer_arithmetic(
	char *command, t_list **tokens, t_shell *shell);

/*
** sh_traverse_and_or_ar.c
*/
int		sh_traverse_and_or_ar(t_ast_node *node, t_context *context);

/*
** sh_traverse_arithmetic.c
*/
int		sh_traverse_arithmetic_ar(t_ast_node *node, t_context *context);

/*
** sh_traverse_comparison_ar.c
*/
int		sh_traverse_comparison_ar(t_ast_node *node, t_context *context);

/*
** sh_traverse_expr_ar.c
*/
int		sh_traverse_expr_ar(t_ast_node *node, t_context *context);

/*
** sh_traverse_factor_ar.c
*/
int		sh_traverse_factor_ar(t_ast_node *node, t_context *context);

/*
** sh_traverse_term_ar.c
*/
int		sh_traverse_term_ar(t_ast_node *node, t_context *context);

#endif
