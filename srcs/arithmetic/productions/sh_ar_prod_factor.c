/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ar_prod_factor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/24 20:52:02 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_ar_init_prod_factor_else(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg, 2,
		LEX_TOK_AR_VARIABLE,
		LEX_TOK_AR_DEC))
		return (1);
	else if (sh_add_prod(symbol, cfg, 2,
		LEX_TOK_AR_MINUS,
		FACTOR_AR))
		return (1);
	else if (sh_add_prod(symbol, cfg, 2,
		LEX_TOK_AR_PLUS,
		FACTOR_AR))
		return (1);
	return (0);
}

int			sh_ar_init_prod_factor(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg, 1,
		LEX_TOK_AR_INTEGER))
		return (1);
	else if (sh_add_prod(symbol, cfg, 1,
		LEX_TOK_AR_VARIABLE))
		return (1);
	else if (sh_add_prod(symbol, cfg, 2,
		LEX_TOK_AR_INC,
		LEX_TOK_AR_VARIABLE))
		return (1);
	else if (sh_add_prod(symbol, cfg, 2,
		LEX_TOK_AR_VARIABLE,
		LEX_TOK_AR_INC))
		return (1);
	else if (sh_add_prod(symbol, cfg, 2,
		LEX_TOK_AR_DEC,
		LEX_TOK_AR_VARIABLE))
		return (1);
	else
		return (sh_ar_init_prod_factor_else(cfg, symbol));
}
