/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_cmd_suffix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:31:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/22 18:23:50 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_process_traverse_cmd_suffix(
	t_ast_node *child, t_context *context)
{
	int ret;

	if (context->phase == E_TRAVERSE_PHASE_EXPANSIONS)
	{
		if (child && child->token)
			if ((ret = sh_expansions(context, child)) != SUCCESS)
				return (ret);
	}
	if (context->phase == E_TRAVERSE_PHASE_EXECUTE && child->token)
	{
		if (*child->token->value || child->token->give_as_arg)
			if (ft_dy_tab_add_str(context->params, child->token->value))
				return (sh_perror(SH_ERR1_MALLOC,
							"sh_traverse_cmd_suffix"));
	}
	else if (child && child->symbol && (ret = g_grammar[child->symbol->id].
				traverse(child, context)))
		return (ret);
	return (SUCCESS);
}

long		sh_traverse_cmd_suffix(t_ast_node *node, t_context *context)
{
	t_ast_node	*child;
	t_list		*ptr;
	int			ret;
	t_list		*next;

	ptr = node->children;
	ret = SUCCESS;
	if (context->phase != E_TRAVERSE_PHASE_EXPANSIONS
		&& context->phase != E_TRAVERSE_PHASE_EXECUTE)
		return (SUCCESS);
	sh_traverse_tools_show_traverse_start(node, context);
	while (ptr != NULL)
	{
		child = (t_ast_node *)ptr->content;
		next = ptr->next;
		if (((ret = sh_process_traverse_cmd_suffix(child, context)) != SUCCESS))
			break ;
		ptr = next;
	}
	sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	return (ret);
}
