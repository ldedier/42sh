/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_simple_command.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/17 22:20:57 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_simple_command(t_ast_node *node, t_context *context)
{
	// if (sh_traverse_tools_browse(node, context) == FAILURE)
	// 	return (FAILURE);
	// return (sh_traverse_tools_flush(context));
	return (sh_traverse_tools_browse(node, context));
}
