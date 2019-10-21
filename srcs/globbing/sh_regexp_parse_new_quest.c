/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_regexp_parse_new_quest.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 03:41:43 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/21 04:38:31 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_regexp_parse_new_quest(int *i, t_list **regexp_list)
{
	int			start;
	t_regexp	*regexp;

	start = (*i);
	(*i)++;
	if (!(regexp = t_regexp_new_push(regexp_list)))
		return (FAILURE);
	regexp->type = REG_QUEST;
	regexp->start = start;
	regexp->len = 1;
	regexp->value = NULL;
	return (SUCCESS);
}
