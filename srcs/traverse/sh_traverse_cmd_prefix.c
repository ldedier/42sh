/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_cmd_prefix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 10:44:22 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/20 14:52:31 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_traverse_cmd_prefix(t_ast_node *node, t_context *context)
{
	// t_ast_node	*child;

	// ft_dprintf(2, "cmd prefix child : %s\n", child->symbol->debug);
	return (sh_traverse_tools_browse(node, context));
}