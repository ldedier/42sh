/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ar_grammar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 11:02:57 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 11:38:31 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_grammar_holder g_ar_grammar[NB_SYMBOLS_AR] = {
	{"&&", 0, 1, NULL, &sh_traverse_default, NULL},
	{"||", 0, 1, NULL, &sh_traverse_default, NULL},
	{"+", 0, 1, NULL, &sh_traverse_default, NULL},
	{"-", 0, 1, NULL, &sh_traverse_default, NULL},
	{"*", 0, 1, NULL, &sh_traverse_default, NULL},
	{"/", 0, 1, NULL, &sh_traverse_default, NULL},
	{"%", 0, 1, NULL, &sh_traverse_default, NULL},
	{"<", 0, 1, NULL, &sh_traverse_default, NULL},
	{">", 0, 1, NULL, &sh_traverse_default, NULL},
	{"<=", 0, 1, NULL, &sh_traverse_default, NULL},
	{">=", 0, 1, NULL, &sh_traverse_default, NULL},
	{"==", 0, 1, NULL, &sh_traverse_default, NULL},
	{"!=", 0, 1, NULL, &sh_traverse_default, NULL},
	{"integer", 0, 1, NULL, &sh_traverse_default, NULL},
	{"variable", 0, 1, NULL, &sh_traverse_default, NULL},
	{"++", 0, 1, NULL, &sh_traverse_default, NULL},
	{"--", 0, 1, NULL, &sh_traverse_default, NULL},
	{"_EOI_", 0, 1, NULL, &sh_traverse_default, NULL},
	{"ε", 0, 1, NULL, &sh_traverse_default, NULL},
	{"ARITHMETIC", 0, 1, &sh_ar_init_prod_arithmetic,
		&sh_traverse_arithmetic_ar, NULL},
	{"AND_OR", 0, 1, &sh_ar_init_prod_and_or, &sh_traverse_and_or_ar, NULL},
	{"COMPARISON", 0, 1, &sh_ar_init_prod_comparison,
		&sh_traverse_comparison_ar, NULL},
	{"EXPR", 0, 1, &sh_ar_init_prod_expr, &sh_traverse_expr_ar, NULL},
	{"TERM", 0, 1, &sh_ar_init_prod_term, &sh_traverse_term_ar, NULL},
	{"FACTOR", 0, 1, &sh_ar_init_prod_factor, &sh_traverse_factor_ar, NULL}
};
