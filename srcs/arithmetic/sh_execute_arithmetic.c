/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_arithmetic.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:19:04 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/25 14:31:12 by ldedier          ###   ########.fr       */
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

static long	sh_traverse_ar_root(
	t_context *context, t_ast_node *root, t_exec *res)
{
	if (sh_verbose_expansion())
		sh_print_ast(res->ast_root, &context->shell->parser_ar.cfg, 0);
	context->arithmetic_error = 0;
	return (sh_traverse_arithmetic(root, context));
}

static int	handle_parser_error(t_context *cont, t_exec *res, int ret)
{
	sh_perror_err("syntax error", NULL);
	cont->arithmetic_error = 1;
	if (sh_env_update_ret_value_and_question(cont->shell, ret) == 2)
		ret = sh_perror(SH_ERR1_MALLOC, "sh_execute_arithmetic (2)");
	ft_lstdel(&res->tokens, sh_free_token_lst);
	return (ret);
}

long		sh_execute_arithmetic(t_context *cont, char *command)
{
	long		ret;
	t_exec		res;

	res.ast_root = NULL;
	res.cst_root = NULL;
	res.tokens = NULL;
	if ((ret = sh_ar_lexer(command, &res.tokens, cont->shell)) != SUCCESS)
	{
		cont->arithmetic_error = 1;
		if (sh_env_update_ret_value_and_question(cont->shell, ret) == 2)
			ret = sh_perror(SH_ERR1_MALLOC, "sh_execute_arithmetic (1)");
		ft_lstdel(&res.tokens, sh_free_token_lst);
	}
	else if ((ret = sh_parser(cont->shell, &cont->shell->parser_ar, &res)))
		ret = handle_parser_error(cont, &res, ret);
	else
	{
		ret = sh_traverse_ar_root(cont, res.ast_root, &res);
		free_execution_tools(&res.tokens, &res.ast_root, &res.cst_root);
	}
	return (ret);
}
