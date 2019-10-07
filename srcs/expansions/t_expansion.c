/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:16:11 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/05 02:41:32 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** t_expansion_free_content
**		free a t_expansion struct.
*/

void		t_expansion_free_content(t_expansion *expansion)
{
	if (expansion->original)
		free(expansion->original);
	if (expansion->expansion)
		free(expansion->expansion);
	if (expansion->res)
		ft_dy_str_free(&expansion->res);
}

/*
** t_expansion_show
**	show res, original and expansion fields of a t_expansion structure.
**	This print every thing on a single line, with a newline.
*/

void		t_expansion_show(t_expansion *exp)
{
	ft_dprintf(2, "exp : ");
	t_expansion_show_type(exp);
	if (exp->original)
		ft_dprintf(2, "\toriginal : >>%s<<", exp->original);
	if (exp->expansion)
		ft_dprintf(2, "\texpansion : >>%s<<", exp->expansion);
	if (exp->res)
		ft_dprintf(2, "\tres : >>%s<<", exp->res->str);
	ft_putstr_fd("\n", 2);
}

/*
** t_expansion_show_type
**	show litteral value of type field of a t_expansion structure
*/

void		t_expansion_show_type(t_expansion *exp)
{
	if (exp->type == 1)
		ft_dprintf(2, "variable");
	else if (exp->type == 2)
		ft_dprintf(2, "parameter");
	else if (exp->type == 3)
		ft_dprintf(2, "command");
	else if (exp->type == 4)
		ft_dprintf(2, "arithmetic");
	else if (exp->type == 5)
		ft_dprintf(2, "tilde");
}
