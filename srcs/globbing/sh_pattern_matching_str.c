/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pattern_matching_str.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 05:06:07 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/06 05:06:32 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_pattern_matching_str(char *name, t_regexp *regexp, int *i)
{
	if (ft_strnequ(regexp->value, name + *i, regexp->len))
		(*i) += regexp->len;
	else
		return (ERROR);
	return (SUCCESS);
}
