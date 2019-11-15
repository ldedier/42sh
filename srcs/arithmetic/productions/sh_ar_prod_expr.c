/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_ar_init_prod_expr(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg, 1,
		TERM_AR))
		return (1);
	if (sh_add_prod(symbol, cfg, 3,
		EXPR_AR,
		LEX_TOK_AR_PLUS,
		TERM_AR))
		return (1);
	if (sh_add_prod(symbol, cfg, 3,
		EXPR_AR,
		LEX_TOK_AR_MINUS,
		TERM_AR))
		return (1);
	return (0);
}
