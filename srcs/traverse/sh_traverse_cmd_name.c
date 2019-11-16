/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_cmd_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:31:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/16 09:05:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

long		sh_traverse_cmd_name(t_ast_node *node, t_context *context)
{
	return (sh_traverse_cmd_suffix(node, context));
}

// merging corr-redirections and new field splitting , kept this code to check tit works
// need to delete it then

/*
{
	t_ast_node	*child;
	int			ret;

	child = (t_ast_node *)node->children->content;
	if (context->phase == E_TRAVERSE_PHASE_EXPANSIONS)
	{
		if (child && child->token)
		{
			ret = sh_expansions(context, child);
			return (ret);
		}
		return (SUCCESS);
	}
	else if (context->phase == E_TRAVERSE_PHASE_EXECUTE)
	{
		if (child == NULL)
			return (SUCCESS);
		if (ft_dy_tab_add_str(context->params, child->token->value))
			return (sh_perror(SH_ERR1_MALLOC, "sh_traverse_cmd_name"));
		return (SUCCESS);
	}
	else
		return (SUCCESS);
}
*/