/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:49:38 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/17 12:44:19 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

/*
 * sh_traverse_list :
 * This is the browser of the t_list LIST (grammar)
 * Here we scan all LIST node, and_or and separator together, and
 * execute the and_or node at the moment we find it.
 * We wait its return to continue to run the t_list LIST.
*/
int			sh_traverse_list(t_ast_node *node, t_context *context)
{
	int			ret;
	t_ast_node	*last_separator;

	// ft_printf("SHELL PGID: %d\n", g_job_ctrl->shell_pgid);
	if (node->children->next)
	{
		last_separator = node->children->next->content;
		last_separator = last_separator->children->content;
		if (last_separator->symbol->id == sh_index(LEX_TOK_AND))
			g_job_ctrl->ampersand_eol = 1;
		else
			g_job_ctrl->ampersand_eol = 0;
	}
	else
		g_job_ctrl->ampersand_eol = 0;
	sh_traverse_tools_show_traverse_start(node, context);
	ret = get_node_to_exec(node->children->content, context, SEPARATOR_OP, &sh_get_separator_op);
	sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	if (ret == FAILURE)
		return (FAILURE);
	else if (ret == STOP_CMD_LINE)
		return (ERROR);
	return (ret);
}
