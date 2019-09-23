/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_semicol.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 12:27:20 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/19 20:51:53 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
 * sh_traverse_semicol :
 * This function it's called when we find a semi_col in 
 * the t_list LIST (grammar)
 * It take the context and the and_or node to execute.
*/
int		sh_traverse_semicol(t_ast_node *node_to_execute, t_context *context)
{
	int 	ret;
	
	ret = sh_traverse_and_or(node_to_execute, context);
	return (ret);
}
