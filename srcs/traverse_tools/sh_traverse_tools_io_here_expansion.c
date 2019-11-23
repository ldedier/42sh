/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools_io_here_expansion.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 12:43:22 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/22 13:09:32 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** Expansion apply to heredoc
*/

static int	is_valid_var(char c)
{
	if (ft_isalnum(c))
		return (1);
	else if (c == '$' || c == '?')
		return (1);
	else if (c == '{')
		return (1);
	return (0);
}

static long	sh_traverse_io_here_expansion(
		char **str, int *cursor, t_context *context)
{
	int			ret;
	t_dy_tab	*quotes;

	if ((*str)[*cursor] == '$' && is_valid_var((*str)[*cursor + 1]))
	{
		if (!(quotes = ft_dy_tab_new(1)))
			return (sh_perror(SH_ERR1_MALLOC, "sh_traverse_io_here_expansion"));
		ret = sh_expansions_process(str, context, cursor, quotes);
		ft_dy_tab_del_ptr(quotes);
		context->shell->running = 1;
		if (ret != SUCCESS && ret != STOP_CMD_LINE)
		{
			if (sh_env_update_ret_value_and_question(context->shell, ret))
				return (FAILURE);
			return (ret);
		}
	}
	else
		(*cursor) += 1;
	return (SUCCESS);
}

static int	loop_expansion(char **str, t_context *context)
{
	int	cursor;
	int	ret;

	cursor = 0;
	while ((*str)[cursor])
	{
		if ((*str)[cursor] == '\\'
			&& ((*str)[cursor + 1] == '$' || (*str)[cursor + 1] == '\\'))
		{
			ft_strcpy(*str + cursor, (*str) + cursor + 1);
			cursor++;
		}
		if ((ret = sh_traverse_io_here_expansion(str, &cursor, context)))
		{
			ft_strdel(str);
			return (ret);
		}
	}
	return (SUCCESS);
}

long		sh_traverse_io_here_phase_expansion(
				t_ast_node *node, t_context *context)
{
	t_ast_node		*first_child;
	int				ret;

	first_child = node->children->next->content;
	first_child = first_child->children->content;
	if (first_child->token->apply_heredoc_expansion)
	{
		if ((ret = loop_expansion(&(first_child->token->value), context)))
			return (ret);
	}
	return (SUCCESS);
}
