/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_arithmetic.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 11:27:40 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/23 19:45:23 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_ARITHMETIC_H
# define SH_ARITHMETIC_H

# include "sh_21.h"

t_grammar_holder g_ar_grammar[NB_SYMBOLS_AR];

/*
********************************************************************************
*/

/*
** lexer/sh_ar_lexer.c
*/
int		sh_ar_lexer(char *expansion, t_list **tokens, t_shell *shell);

/*
** lexer/sh_ar_lexer_rule_1.c
*/
int		sh_ar_lexer_rule_1(t_lexer *lexer);

/*
** lexer/sh_ar_lexer_rule_2.c
*/
int		sh_ar_lexer_rule_2(t_lexer *lexer);

/*
** lexer/sh_ar_lexer_rule_3.c
*/
int		sh_ar_lexer_rule_3(t_lexer *lexer);

/*
** lexer/sh_ar_lexer_rule_4.c
*/
int		sh_ar_lexer_rule_4(t_lexer *lexer);

/*
** lexer/sh_ar_lexer_rule_5.c
*/
int		sh_ar_lexer_rule_5(t_lexer *lexer);

/*
** lexer/sh_ar_lexer_rule_6.c
*/
int		sh_ar_lexer_rule_6(t_lexer *lexer);

/*
** lexer/sh_ar_lexer_rule_7.c
*/
int		sh_ar_lexer_rule_7(t_lexer *lexer);

/*
** lexer/sh_ar_lexer_rule_8.c
*/
int		sh_ar_lexer_rule_8(t_lexer *lexer);

/*
** lexer/sh_ar_lexer_rule_9.c
*/
int		sh_ar_lexer_rule_9(t_lexer *lexer);

/*
** lexer/t_ar_lexer.c
*/
void	t_ar_lexer_init(t_lexer *lexer, t_shell *shell, char *input);
void	t_ar_lexer_reset(t_lexer *lexer, int tok_start);
int		t_ar_lexer_add_token(t_lexer *lexer);
void	t_ar_lexer_show(t_lexer *lexer);

/*
** lexer/t_ar_token.c
*/
void	t_ar_token_show_1(t_token *token);
void	t_ar_token_show(t_token *token);
void	t_ar_token_free(t_token *token);

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
int		sh_ar_init_prod_comparison_others(t_cfg *cfg, t_symbol *symbol);
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
long	sh_throw_ar_error(
	t_context *context, char *error_message, int error);
long	sh_traverse_arithmetic(t_ast_node *node, t_context *context);
long	sh_execute_arithmetic(t_context *cont, char *command);

/*
** sh_traverse_and_or_ar.c
*/
long	sh_traverse_and_or_ar(t_ast_node *node, t_context *context);

/*
** sh_traverse_arithmetic_ar.c
*/
long	sh_traverse_arithmetic_ar(t_ast_node *node, t_context *context);

/*
** sh_traverse_comparison_ar.c
*/
long	sh_traverse_comparison_ar(t_ast_node *node, t_context *context);

/*
** sh_traverse_expr_ar.c
*/
long	sh_traverse_expr_ar(t_ast_node *node, t_context *context);

/*
** sh_traverse_factor_ar.c
*/
void	add_shell_var(char *variable, int to_add, t_context *context);
long	get_integer_from_var(char *variable, t_context *context);
long	sh_traverse_factor_ar(t_ast_node *node, t_context *context);

/*
** sh_traverse_term_ar.c
*/
long	sh_traverse_term_ar(t_ast_node *node, t_context *context);

#endif
