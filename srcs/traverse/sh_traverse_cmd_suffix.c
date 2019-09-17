/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_cmd_suffix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:31:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/28 11:29:36 by jdugoudr         ###   ########.fr       */
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
		// if (!(!*child->token->value && child->token->expansion))
			if (ft_dy_tab_add_str(context->params, child->token->value))
				return (sh_perror(SH_ERR1_MALLOC,
							"sh_traverse_cmd_suffix"));
	}
	else if (child && child->symbol && (ret = g_grammar[child->symbol->id].
				traverse(child, context)))
		return (ret);
	return (SUCCESS);
}

/* JMARTEL TO UNCOMMENT AND AKNOWLEDGE (then delete)
int		test_field_splitting_function(t_ast_node *child, t_list **ptr)
{
	int			i;
	t_ast_node	*node;

	*ptr = (*ptr)->next; //pour passer au suivant dans la liste pas encore modifiee
	node = child;
	i = 0;
	while (i < 3)
	{
		if (!(node = sh_add_word_to_ast(node,
			ft_strdup("je remplace 3 fois mdr le 2 eme param hehe"))))
		{
			return (1);
		}
		i++;
	}
	sh_delete_node_from_parent(child);
	return (0);
}
*/

int			sh_traverse_cmd_suffix(t_ast_node *node, t_context *context)
{
	t_ast_node	*child;
	t_list		*ptr;
	int			ret;
/* JMARTEL TO UNCOMMENT AND AKNOWLEDGE
	int			i;

	i = 1;
*/
	ptr = node->children;
	ret = SUCCESS;
	if (context->phase != E_TRAVERSE_PHASE_EXPANSIONS 
		&& context->phase != E_TRAVERSE_PHASE_EXECUTE)
		return (SUCCESS);
	sh_traverse_tools_show_traverse_start(node, context);
	while (ptr != NULL)
	{
		child = (t_ast_node *)ptr->content;
		if (((ret = sh_process_traverse_cmd_suffix(child, context)) != SUCCESS))
			break ;
		/* JMARTEL TO UNCOMMENT AND AKNOWLEDGE
		if (i == 2 && context->phase == E_TRAVERSE_PHASE_REDIRECTIONS)
		{
			test_field_splitting_function(child, &ptr);
			sh_print_ast(context->shell->parser.ast_root, 0);
			if (!ptr) //au cas ou on a remplace le dernier token
				break ;
		}
		i++;
		*/
		ptr = ptr->next;
	}
	sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	return (ret);
}
