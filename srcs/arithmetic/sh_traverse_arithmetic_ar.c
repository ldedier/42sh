/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_arithmetic_ar.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 18:44:34 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/16 09:05:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

long		sh_traverse_arithmetic_ar(t_ast_node *node, t_context *context)
{
	if (node->children)
		return (sh_traverse_arithmetic(node->children->content, context));
	else
		return (0);
}
