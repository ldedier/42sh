/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_ar_init_prod_and_or(t_cfg *cfg, t_symbol *symbol)
{
	if (sh_add_prod(symbol, cfg, 1,
		COMPARISON_AR))
		return (1);
	if (sh_add_prod(symbol, cfg, 3,
		AND_OR_AR,
		LEX_TOK_AR_AND,
		COMPARISON_AR))
		return (1);
	if (sh_add_prod(symbol, cfg, 3,
		AND_OR_AR,
		LEX_TOK_AR_OR,
		COMPARISON_AR))
		return (1);
	return (0);
}
