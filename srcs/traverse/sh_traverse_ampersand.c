/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_ampersand.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 12:27:20 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/22 13:04:15 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_traverse_ampersand :
** This function it's called when we find a semi_col in
** the t_list LIST (grammar)
** It take the context and the and_or node to execute.
*/

long	sh_traverse_ampersand(t_ast_node *node_to_execute, t_context *context)
{
	int	ret;

	g_job_ctrl->ampersand = 1;
	ret = sh_traverse_and_or(node_to_execute, context);
	return (ret);
}
