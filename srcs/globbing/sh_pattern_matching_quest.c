/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pattern_matching_quest.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 05:06:07 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/06 05:06:43 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_pattern_matching_quest(char *name, t_regexp *regexp, int *i)
{
	if (name[*i])
		(*i) += regexp->len;
	else
		return (ERROR);
	return (SUCCESS);
}
