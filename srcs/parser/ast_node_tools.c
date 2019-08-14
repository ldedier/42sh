/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 20:10:04 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/13 12:34:17 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_ast_node	*sh_new_ast_node(t_symbol_id id, char *value)
{
	t_ast_node	*res;
	t_token		*token;

	token = NULL;
	if (value)
	{
		if (!(token = t_token_new(id, value)))
			return (sh_perrorn(SH_ERR1_MALLOC, "new_ast_node (1)"));
	}
	if (!(res = malloc(sizeof(t_ast_node))))
	{
		t_token_free(token);
		return (sh_perrorn(SH_ERR1_MALLOC, "new_ast_node (2)"));
	}
	sh_init_ast_node(res, token, &g_glob.cfg->symbols[sh_index(id)], NULL);
	res->builder = NULL;
	return (res);
}

/*
** appends a child to the ast_node node
**
** if value is not null, the node will be considered a symbol_id token
** of this value
**
** else, it will be a symbol of id symbol_id
**
** in both cases returns the newly appended child or NULL on error
*/

t_ast_node	*sh_add_to_ast_node(t_ast_node *node, t_symbol_id id,
				char *value)
{
	t_ast_node *new_node;

	if (!(new_node = sh_new_ast_node(id, value)))
		return (NULL);
	if (ft_lstaddnew_ptr_last(&node->children, new_node,
		sizeof(t_ast_node *)))
	{
		sh_free_ast_node(&node, 0);
		return (sh_perrorn(SH_ERR1_MALLOC, "add_to_ast_node (2)"));
	}
	return (new_node);
}
