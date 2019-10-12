/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_pattern_matching.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:31:28 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/12 13:31:28 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** Le pattern matching (globing) : *, ?, [], !
** et les intervals de caractères avec -
*/

int			sh_expansions_pattern_matching(t_context *context,
				t_ast_node *node)
{
	t_ast_node	*child;
	char		*str;

	str = node->token->value;
//	ft_printf("value: %s\n", str);
	(void)context;
	(void)node;
	(void)child;
	return (0);
}
