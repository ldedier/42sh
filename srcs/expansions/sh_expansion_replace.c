/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansion_replace.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 14:59:23 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/08/03 14:59:27 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_expansions_replace(
	t_expansion *expansion, char **input, int index)
{
	*input = ft_strrep_free(
		*input, expansion->res->str, index, ft_strlen(expansion->original));
	if (!(*input))
		return (FAILURE);
	if (sh_verbose_expansion())
	{
		t_expansion_show_type(expansion);
		ft_dprintf(2, " expansion : %s", L_BLUE);
		ft_dprintf(2, "%s => %s\n", expansion->original, expansion->res->str);
		ft_dprintf(2, "new input : %s%s\n", *input, EOC);
	}
	return (SUCCESS);
}
