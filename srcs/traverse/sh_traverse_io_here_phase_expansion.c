/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_here_phase_expansion.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 11:28:42 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/09/05 12:42:59 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

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
		t_redirection *redirection, t_ast_node *node, t_context *context)
{
	t_ast_node		*first_child;
	int				fds[2];
	int				ret;

	first_child = node->children->next->content;
	first_child = first_child->children->content;
	if (first_child->token->apply_heredoc_expansion)
	{
		if ((ret = loop_expansion(&(first_child->token->value), context)))
			return (ret);
	}
	if (pipe(fds))
		return (sh_perror(SH_ERR1_PIPE, "sh_traverse_io_here_end"));
	else
	{
		redirection->type = INPUT;
		redirection->redirected_fd = context->redirected_fd;
		redirection->fd = fds[0];
		ft_putstr_fd(first_child->token->value, fds[1]);
		close(fds[1]);
	}
	return (SUCCESS);
}
