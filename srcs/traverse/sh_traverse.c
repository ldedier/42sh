/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 21:45:25 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/30 11:25:24 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static t_ast_node	*go_to_list(t_ast_node *node)
{
	t_ast_node *test;

	test = node;
	while (test->symbol->id != sh_index(LIST))
	{
		if (test->children == NULL)
			return (NULL);
		test = test->children->content;
	}
	return (test);
}

int		sh_process_traverse(t_shell *shell, t_ast_node *ast_root)
{
	t_context	context;
	t_ast_node	*list_node;
	int			ret;

	if (t_context_init(&context, shell) == FAILURE)
		return (FAILURE);
	if ((list_node = go_to_list(ast_root)) == NULL)
	{
		shell->history.should_add = 0;
		t_context_free_content(&context);
		return (SUCCESS);
	}
	context.phase = E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS;
	if ((ret = sh_traverse_tools_browse(list_node, &context)) == SUCCESS)
		/*ret = g_grammar[list_node->symbol->id].traverse(list_node, &context);*/
		ret = sh_traverse_list(list_node, &context);
	t_context_free_content(&context);
	return (ret);
}
