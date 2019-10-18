/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_subshell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 10:03:30 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/10/18 08:23:14 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** search_term
** compound_list node can be a newline_list follow by a term node and separator
** need to have at least a term node.
**
** So we skip all newline_list to go to the term node.
** Have to check of the proper separator.
** A term can be a list of and_or break by separator node.
** A separator can be ';' '&' 'line_break' or 'newline_list'
*/
static int	get_last_separator(t_ast_node *curr_node)
{
	t_ast_node	*last_separator;

	if (curr_node->children->next)
	{
		last_separator = curr_node->children->next->content;
		last_separator = last_separator->children->content;
		if (last_separator->symbol->id == sh_index(SEPARATOR_OP))
		{
			last_separator = last_separator->children->content;
			/*ft_printf("we've got a separator ! it's ");// delete it*/
			if (last_separator->symbol->id == sh_index(LEX_TOK_AND))
			{
				/*ft_printf("-%c-\n", '&');// delete it*/
				return (1);
			}
			else if (last_separator->symbol->id == sh_index(LEX_TOK_SEMICOL))
			{
				;
			}

				/*ft_printf("-%c-\n", ';');// delete it*/
		}
		else
			return (ERROR);
			/*ft_printf("-well this is a separtor not yet manage like linebreak or something ..-\n");// delete it*/
	}
	return (0);
}

static int	search_term(t_ast_node *node, t_context *context)
{
	t_list		*el;
	int			ret;
	t_ast_node	*curr_node;
	// t_ast_node	*node_to_exec;

	el = node->children;
	// node_to_exec = NULL;
	ret = SUCCESS;
	while (el)
	{
		curr_node = el->content;
		if (curr_node->symbol->id == sh_index(COMPOUND_LIST))
		{
			get_last_separator(curr_node);//check retrun value to know if they are '&' at the end
			el = curr_node->children;
			curr_node = el->content;
		}
		if (curr_node->symbol->id == sh_index(TERM))
			break ;
		el = el->next;
	}
	if (el)
		ret = get_node_to_exec(curr_node, context, SEPARATOR, &sh_get_separator);
	return (ret);
}

/*
** sh_traverse_subshell
** We execute here what a subshell do.
** We fork to have a "subshell"
**
** A subshell node can only have, at least and at most,
** '(' 'compund_list' and ')' children.
** So we can directly go to compound_list node.
*/
int		sh_traverse_subshell(t_ast_node *node, t_context *context)
{
	pid_t	pid;
	int		ret;

	if ((pid = fork()) < 0)
		return (sh_perror_err(SH_ERR1_FORK, "can't fork for subshell"));
	else if (pid)
	{
		waitpid(pid, &ret, 0);
		sh_env_update_ret_value_wait_result(context, ret);
		return (SUCCESS);
	}
	else
	{
		/*ret = search_term(node->children->next->content, context);*/
		ret = search_term(node, context);
		sh_free_all(context->shell);
		if (ret != SUCCESS)
			exit(ret);
		exit(context->shell->ret_value);
	}
	return (0);
}

int		sh_traverse_brace_group(t_ast_node *node, t_context *context)
{
	int	ret;

	sh_traverse_tools_show_traverse_start(node, context);
	/*ret = search_term(node->children->next->content, context);*/
	ret = search_term(node, context);
	sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	return (ret);
}
