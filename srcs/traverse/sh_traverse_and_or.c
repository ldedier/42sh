/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_and_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:54:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/07 09:37:19 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
 * sh_traverse_and_or_call_sons_exec :
 * Following return value of the preview execution,
 * this function execute or not the next level in the ast,
 * pipe sequence (sh_traverse_pipe_sequence).
*/
static int		sh_traverse_and_or_call_sons_exec(t_ast_node *node,
		int *prev_symbol, t_context *context)
{
	t_ast_node	*child;
	int			ret;

	if (*prev_symbol == -1)
		;
	else if (*prev_symbol == sh_index(LEX_TOK_AND_IF)
		&& context->shell->ret_value)
		return (SUCCESS);
	else if (*prev_symbol == sh_index(LEX_TOK_OR_IF)
		&& !context->shell->ret_value)
		return (SUCCESS);
	child = (t_ast_node*)(node->children->content);
	ret = sh_traverse_pipeline(child, context);
	context->shell->ret_value = ret;
	if (ret == FAILURE || ret == STOP_CMD_LINE)
		return (ret);
	if (!context->shell->running)
		return (ret);
	return (SUCCESS);
}

/*
 * sh_traverse_and_or_process_phase :
 * This function set the env variable with the return value of the
 * and_or node execution.
*/
static int		sh_traverse_and_or_process_phase(
	t_context *context, int prev_symbol, t_list *ptr)
{
	int			ret;
	t_ast_node	*child;

	child = (t_ast_node*)ptr->content;
	ret = sh_traverse_and_or_call_sons_exec(child, &prev_symbol, context);
	if (ret && sh_env_update_question_mark(context->shell) == FAILURE)
		return (FAILURE);
	if (ret == KEEP_READ || ret == STOP_CMD_LINE || ret == FAILURE)
		return (ret);
	if (ret == ERROR)
	{
		set_failed_command(context);
		return (KEEP_READ);
	}
	return (KEEP_READ);
}

static int		sh_traverse_and_or_launch_phase(
	t_ast_node *node, t_context *context)
{
	t_list		*ptr;
	int			ret;
	int			prev_symbol;

	ptr = node->children;
	prev_symbol = -1;
	while (ptr != NULL && context->shell->running)
	{
		if ((ret = sh_traverse_and_or_process_phase(
			context, prev_symbol, ptr)) != KEEP_READ)
			return (ret);
		if ((ptr = (ptr)->next))
		{
			prev_symbol = ((t_ast_node*)ptr->content)->symbol->id;
			ptr = (ptr)->next;
		}
		t_context_reset(context);
	}
	return (SUCCESS);
}

/*
 * sh_traverse_and_or :
 * This is the browser of the t_list and_or (grammar)
 * We execute a and_or node, check it return value and
 * execute or not the next and_or node follow the found token
 * AND_IF or OR_IF.
 * 
 * We also call the function sh_env_update_question_mark to be sur
 * that at this time, the return value is set in the env variable 
*/
int				sh_traverse_and_or(t_ast_node *node, t_context *context)
{
	int		ret;

	sh_traverse_tools_show_traverse_start(node, context);
	ret = sh_traverse_and_or_launch_phase(node, context);
	sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	return (ret);
}
