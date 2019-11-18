/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparison.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 11:45:25 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_ar_init_prod_comparison_others(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg, 3,
		COMPARISON_AR,
		LEX_TOK_AR_LESS,
		EXPR_AR))
		return (1);
	if (sh_add_prod(symbol, cfg, 3,
		COMPARISON_AR,
		LEX_TOK_AR_LESSEQ,
		EXPR_AR))
		return (1);
	if (sh_add_prod(symbol, cfg, 3,
		COMPARISON_AR,
		LEX_TOK_AR_NOT_EQUAL,
		EXPR_AR))
		return (1);
	if (sh_add_prod(symbol, cfg, 3,
		COMPARISON_AR,
		LEX_TOK_AR_EQUAL,
		EXPR_AR))
		return (1);
	return (0);
}

int		sh_ar_init_prod_comparison(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg, 1,
		EXPR_AR))
		return (1);
	if (sh_add_prod(symbol, cfg, 3,
		COMPARISON_AR,
		LEX_TOK_AR_GREAT,
		EXPR_AR))
		return (1);
	if (sh_add_prod(symbol, cfg, 3,
		COMPARISON_AR,
		LEX_TOK_AR_GREATEQ,
		EXPR_AR))
		return (1);
	return (sh_ar_init_prod_comparison_others(cfg, symbol));
}
