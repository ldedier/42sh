/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_arithmetic_productions.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 10:58:15 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/15 14:36:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_ARITHMETIC_PRODUCTIONS_H
# define SH_ARITHMETIC_PRODUCTIONS_H

# define NB_PRODUCTIONS_AR	26
# define NB_SYMBOLS_AR		25
# define NB_TERMS_AR		19

typedef enum e_symbol_id_ar
{
	LEX_TOK_AR_AND,
	LEX_TOK_AR_OR,
	LEX_TOK_AR_PLUS,
	LEX_TOK_AR_MINUS,
	LEX_TOK_AR_MULTIPLY,
	LEX_TOK_AR_DIVIDE,
	LEX_TOK_AR_MODULO,
	LEX_TOK_AR_LESS,
	LEX_TOK_AR_GREAT,
	LEX_TOK_AR_LESSEQ,
	LEX_TOK_AR_GREATEQ,
	LEX_TOK_AR_EQUAL,
	LEX_TOK_AR_NOT_EQUAL,
	LEX_TOK_AR_INTEGER,
	LEX_TOK_AR_VARIABLE,
	LEX_TOK_AR_INC,
	LEX_TOK_AR_DEC,
	END_OF_INPUT_AR,
	EPS_AR,
	ARITHMETIC_AR,
	AND_OR_AR,
	COMPARISON_AR,
	EXPR_AR,
	TERM_AR,
	FACTOR_AR
}			t_symbol_id_ar;

/*
********************************************************************************
*/

/*
** sh_ar_prod_and_or.c
*/
int		sh_ar_init_prod_and_or(t_cfg *cfg, t_symbol *symbol);

/*
** sh_ar_prod_arithmetic.c
*/
int		sh_ar_init_prod_arithmetic(t_cfg *cfg, t_symbol *symbol);

/*
** sh_ar_prod_comparison.c
*/
int		sh_ar_init_prod_comparison(t_cfg *cfg, t_symbol *symbol);

/*
** sh_ar_prod_expr.c
*/
int		sh_ar_init_prod_expr(t_cfg *cfg, t_symbol *symbol);

/*
** sh_ar_prod_factor.c
*/
int		sh_ar_init_prod_factor(t_cfg *cfg, t_symbol *symbol);

/*
** sh_ar_prod_term.c
*/
int		sh_ar_init_prod_term(t_cfg *cfg, t_symbol *symbol);

#endif
