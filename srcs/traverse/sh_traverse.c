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


// static void	just_test(t_ast_node *node, int shift)
// {
// 	t_list		*lst = node->children;

// 	while (lst)
// 	{
// 		t_ast_node	*child = lst->content;
// 		if (child->token)
// 			ft_printf("%*c%s\n", shift, ' ', child->token->value);
// 		else
// 			just_test(child, shift + 1);
// 		lst = lst->next;
// 	}
// }

// int		sh_process_traverse(t_shell *shell)
// {
// 	t_context	context;
// 	int			ret;

// 	if (t_context_init(&context, shell) == FAILURE)
// 		return (FAILURE);
// 	// just_test(shell->parser.ast_root, 0);
// 	context.phase = E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS;
// 	if ((ret = g_grammar[shell->parser.ast_root->symbol->id].
// 		traverse(shell->parser.ast_root, &context)))
// 	{
// 		ft_dy_tab_del(context.params);
// 		return (ret);
// 	}
// 	// context.phase = E_TRAVERSE_PHASE_EXPANSIONS;
// 	context.phase = E_TRAVERSE_PHASE_PIPE;
// 	ret = g_grammar[shell->parser.ast_root->symbol->id].
// 		traverse(shell->parser.ast_root, &context);
// 	t_context_free_content(&context);
// 	return (ret);
// }

static t_ast_node	*go_to_list(t_ast_node *node)
{
	t_ast_node *test;

	test = node;
	while (test->symbol->id != 58)//58 est le id de LIST mais je sais pas d'ou ca sort...
	{
		if (test->children == NULL)
			return (NULL);
		test = test->children->content;
	}
	return (test);
}

int		sh_process_traverse(t_shell *shell)
{
	t_context	context;
	t_ast_node	*list_node;
	int			ret;

	if (t_context_init(&context, shell) == FAILURE)
		return (FAILURE);
	if ((list_node = go_to_list(shell->parser.ast_root)) == NULL)
		return (SUCCESS);
	ret = sh_traverse_list(list_node, &context);
	t_context_free_content(&context);
	return (ret);
}
