/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_regexp_parse_new_quest.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 03:41:43 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/08 00:13:43 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_regexp_parse_new_quest:
**	Malloc a new t_regexp struct and push it at the end of regep_list.
**
**	Returned Values
**		SUCCESS : Pushed new t_regexp struct
**		FAILURE : malloc error
*/

int			sh_regexp_parse_new_quest(int *i, t_list **regexp_list)
{
	t_regexp	*regexp;

	(*i)++;
	if (!(regexp = t_regexp_new_push(regexp_list)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_regexp_parse_new_quest"));
	regexp->type = REG_QUEST;
	regexp->len = 1;
	regexp->value = NULL;
	return (SUCCESS);
}
