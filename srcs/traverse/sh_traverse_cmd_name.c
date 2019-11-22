/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_cmd_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:31:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/22 11:53:05 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

long		sh_traverse_cmd_name(t_ast_node *node, t_context *context)
{
	return (sh_traverse_cmd_suffix(node, context));
}
