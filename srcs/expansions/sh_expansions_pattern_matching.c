/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_pattern_matching.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:31:28 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/12 18:44:15 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			fill_regexp(t_list **value, char *str)
{

	return (0);
}

/*
** pattern matching (globing) : *, ?, [], !, intervals with '-'
*/

int			sh_expansions_pattern_matching(t_context *context, t_ast_node *node)
{
	t_ast_node	*child;
	char		*str;
	t_list		*matches;

	str = node->token->value;
	matches = NULL;
//	ft_printf("value: %s\n", str);
	(void)context;
	(void)node;
	(void)child;
	return (0);
}
