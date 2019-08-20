/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_assigment_word.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 12:11:44 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/10 11:31:35 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_assigment_word(t_ast_node *node, t_context *context)
{
	int		ret;

	if (context->phase == E_TRAVERSE_PHASE_EXPANSIONS)
	{
		ret = SUCCESS;
		if (node && node->token)
			ret = sh_expansions(context, node);
		if (!ret && node && node->token && node->token->value
				&& ft_strnstr(node->token->value, "PATH=", 5))
			sh_builtin_hash_empty_table(context->shell);
		if (!ret && node && node->token && node->token->value)
			ret = sh_vars_assignment(context->env, context->vars, node->token->value);
		if (!ret && node && node->token && node->token->value
			&& sh_verbose_exec())
			ft_dprintf(2, "assigned : %s\n", node->token->value);
		sh_env_update_ret_value_and_question(context->shell, ret);
		return (ret);
	}
	else
		return (sh_traverse_tools_browse(node, context));
}
