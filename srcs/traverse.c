/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 21:45:25 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/20 17:10:44 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_process_traverse(t_shell *shell)
{
	t_context	context;

	if (t_context_init(&context, shell) == FAILURE)
		return (FAILURE);
	g_grammar[shell->parser.ast_root->symbol->id].
		traverse(shell->parser.ast_root, &context);
	// ft_strtab_put((char **)context.params->tbl);
	t_context_free(&context);
	return (SUCCESS);
}
