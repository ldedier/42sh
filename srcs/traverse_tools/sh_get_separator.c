/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_separator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:42:32 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/10/07 14:46:01 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
 * get_separator_op :
 * This function take the current and_or nod to execute and the separator_op.
 * Separator_op is necessary because it can change the way we execute the
 * and_or node.
 * semi column separator : just execute the and_or
 * and (&) separator : probably we need to fork at this time and execute
 * and_or node in back_ground.
*/
int 	sh_get_separator_op(
	t_ast_node *to_execute, t_ast_node *separator, t_context *context)
{
	//need to send to_execute to the good separator
	if (separator->symbol->id == sh_index(LEX_TOK_SEMICOL))
		return (sh_traverse_semicol(to_execute, context));
	if (separator->symbol->id == sh_index(LEX_TOK_AND))
	{
		ft_dprintf(STDERR_FILENO, "sh_get_separator_op: sorry & is not yet implement\n");
		return (ERROR);
	}
	return (FAILURE);
}

int		sh_get_separator(
		t_ast_node *to_execute, t_ast_node *separator, t_context *context)
{
	//need to send to_execute to the good separator
	if (separator->symbol->id == sh_index(NEWLINE_LIST))
	{
		ft_dprintf(STDERR_FILENO, "sh_get_separator: sorry NEWLINE_LIST is not yet implement\n");
		return (ERROR);
	}
	else
		return (sh_get_separator_op(
					to_execute, separator->children->content, context));
	return (FAILURE);
}
