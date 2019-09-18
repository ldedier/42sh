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

int		sh_process_traverse(t_shell *shell, t_ast_node *ast_root)
{
	t_context	context;
	int			ret;

	if (t_context_init(&context, shell) == FAILURE)
		return (FAILURE);
	context.phase = E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS;
	if ((ret = g_grammar[ast_root->symbol->id].
		traverse(ast_root, &context)))
	{
		ft_dy_tab_del(context.params);
		return (ret);
	}
	context.phase = E_TRAVERSE_PHASE_EXPANSIONS;
	ret = g_grammar[ast_root->symbol->id].
		traverse(ast_root, &context);
	t_context_free_content(&context);
	return (ret);
}
