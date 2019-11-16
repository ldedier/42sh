/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_redirect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 21:27:03 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/16 09:05:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_traverse_io_redirect:
**	Father of any redirections operations
**	Find for the optionnal fd value, and stock it into father_id
**		this fd can only be between 0 and 9 (POSIX)
**	Then call childrens
*/

long		sh_traverse_io_redirect(t_ast_node *node, t_context *context)
{
	t_ast_node	*child;
	int			ret;

	ret = SUCCESS;
	if (context->phase == E_TRAVERSE_PHASE_REDIRECTIONS)
	{
		child = (t_ast_node*)node->children->content;
		context->redirected_fd = -1;
		ret = SUCCESS;
		if (child->symbol->id == sh_index(LEX_TOK_IO_NUMBER))
			context->redirected_fd = ft_atoi(child->token->value);
		sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	}
	return (ret);
}
