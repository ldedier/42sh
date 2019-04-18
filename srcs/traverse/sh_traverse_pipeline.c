/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 20:33:13 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/18 12:46:23 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_pipeline(t_ast_node *node, t_context *context)
{
	sh_traverse_update_father(node, context);
	return (sh_traverse_tools_browse(node, context));
}
