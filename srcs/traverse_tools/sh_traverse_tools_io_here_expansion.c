/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_here_expansion.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 12:43:22 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/09/05 12:53:22 by jdugoudr         ###   ########.fr       */
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

static int	sh_traverse_io_here_expansion(
		char **str, int *cursor, t_context *context)
{
	int ret;

	if ((*str)[*cursor] == '$' && is_valid_var((*str)[*cursor + 1]))
	{
		if ((ret = sh_expansions_process(
						str, (*str) + *cursor, context, cursor)))
		{
			if (sh_env_update_ret_value_and_question(context->shell, ret))
				return (FAILURE);
			return (ERROR);
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

int			sh_traverse_io_here_phase_expansion(
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
