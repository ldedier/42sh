/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_arithmetic.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:19:04 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 12:06:03 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"


long		sh_throw_ar_error(t_context *context, char *error_message,
	int error)
{
	if (error_message != NULL)
		sh_perror(error_message, NULL);
	context->arithmetic_error = error;
	return (1);
}

long		sh_traverse_arithmetic(t_ast_node *node, t_context *context)
{
	if (!context->arithmetic_error)
		return (g_ar_grammar[node->symbol->id].traverse(node, context));
	else
		return (1);
}

long		sh_traverse_ar_root(t_context *context, t_ast_node *root)
{
	context->arithmetic_error = 0;
	return (sh_traverse_arithmetic(root, context));
}

int		sh_execute_arithmetic(t_context *context, char *command)
{
	int         ret;
	t_exec      res;

	res.ast_root = NULL;
	res.cst_root = NULL;
	res.tokens = NULL;
	ret = 0;
	if ((ret = sh_ar_lexer(command, &res.tokens, context->shell)) != SUCCESS)
	{
		context->arithmetic_error = 1;
		if (sh_env_update_ret_value_and_question(context->shell, ret) == FAILURE)
			ret = sh_perror(SH_ERR1_MALLOC, "sh_execute_arithmetic (1)");
		ft_lstdel(&res.tokens, sh_free_token_lst);
	}
	else if ((ret = sh_parser(context->shell, &context->shell->parser_ar, &res)))
	{
		sh_perror_err("syntax error", NULL);
		context->arithmetic_error = 1;
		if (sh_env_update_ret_value_and_question(context->shell, ret) == FAILURE)
			ret = sh_perror(SH_ERR1_MALLOC, "sh_execute_arithmetic (2)");
		ft_lstdel(&res.tokens, sh_free_token_lst);
	}
	else
	{
		sh_print_ast(res.ast_root, &context->shell->parser_ar.cfg, 0);
		ret = sh_traverse_ar_root(context, res.ast_root);
		free_execution_tools(&res.tokens, &res.ast_root, &res.cst_root);
	}
	return (ret);
}
