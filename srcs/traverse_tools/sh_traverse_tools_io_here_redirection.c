/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools_io_here_redirection.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:33:12 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/22 11:54:23 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_redirection_for_heredoc(
		char *str, t_redirection *redirection, t_context *context)
{
	int				fds[2];

	if (pipe(fds))
		return (sh_perror(SH_ERR1_PIPE, "sh_traverse_io_here_end"));
	else
	{
		redirection->type = INPUT;
		redirection->redirected_fd = context->redirected_fd;
		redirection->fd = fds[0];
		ft_putstr_fd(str, fds[1]);
		close(fds[1]);
	}
	return (SUCCESS);
}

long		sh_traverse_tools_io_here_redirection(
		t_ast_node *node, t_context *context)
{
	int				ret;
	t_redirection	red;

	if ((ret = sh_redirection_for_heredoc(
					node->token->value, &red, context)) == SUCCESS)
		ret = sh_add_redirection_file(red.type, context, red.fd);
	return (ret);
}
