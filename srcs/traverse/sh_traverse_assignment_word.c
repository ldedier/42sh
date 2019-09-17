/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_assignment_word.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 11:20:39 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/09/12 15:03:44 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_assignment_word(t_ast_node *node, t_context *context)
{
	int		ret;

	ret = SUCCESS;
	if (context->phase == E_TRAVERSE_PHASE_EXECUTE)
	{
		sh_traverse_tools_show_traverse_start(node, context);
		if (node && node->token)
			ret = sh_expansions(context, node);
		if (!ret && node && node->token && node->token->value
				&& ft_strnstr(node->token->value, "PATH=", 5))
			sh_builtin_hash_empty_table(context->shell);
		if (!ret && node && node->token && node->token->value)
			ret = sh_vars_assignment(
					context->env, context->vars, node->token->value);
		if (!ret && node && node->token && node->token->value
			&& sh_verbose_exec())
			ft_dprintf(FD_ERR, "assigned : %s\n", node->token->value);
		sh_env_update_ret_value_and_question(context->shell, ret);
		sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	}
	return (ret);
}
