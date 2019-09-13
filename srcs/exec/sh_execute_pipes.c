/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 17:26:22 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/30 20:11:41 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_process_process_execute_dup(t_redirection *redir)
{
	if (redir->fd >= 0)
	{
		if (write(redir->fd, "", 0) < 0)
			ft_printf("t'as bien vu l'erreur 2\n");
		ft_printf("process process execute dup :%d %d\n", redir->redirected_fd, redir->fd);
		if (sh_verbose_pipe())
			ft_dprintf(2, "\t%d became %d\n",
					redir->fd, redir->redirected_fd);
		if (dup2(redir->fd, redir->redirected_fd) == -1)
			return (sh_perror(SH_ERR1_INTERN_ERR,
						"process_exec_dup_pipes 2"));
	}
	else if (redir->fd == -1)
	{
		if (sh_verbose_pipe())
			ft_dprintf(2, "\tclosing %d\n", redir->redirected_fd);
		close(redir->redirected_fd);
	}
	return (SUCCESS);
}

int			sh_process_execute_dup(t_context *context)
{
	t_list			*head;
	t_redirection	*redir;

	if (!context->redirections)
		return (SUCCESS);
	if (sh_verbose_pipe())
		ft_dprintf(2, "Redirections for %s:\n", context->params->tbl[0]);
	// head = *(context->redirections);
	head = (context->redirections);
	while (head)
	{
		//on vient pour both pipe et redirection
		redir = (t_redirection*)head->content;
		if (write(redir->fd, "", 0) < 0)
			ft_printf("t'as bien vu l'erreur 1\n");
		if (sh_process_process_execute_dup(redir))
			return (FAILURE);
		head = head->next;
	}
	return (SUCCESS);
}

static void	sh_process_process_execute_close_pipes(t_redirection *redir)
{
	if (redir->fd > 2)
	{
		if (sh_verbose_pipe())
			ft_dprintf(2, "\tclosing %d\n", redir->fd);
		close(redir->fd);
	}
	redir->closed = 1;
}

int			sh_process_execute_close_pipes(t_context *context)
{
	t_list			*head;
	t_redirection	*redir;

	if (!context->redirections)
		return (SUCCESS);
	if (sh_verbose_pipe() && context->params->tbl[0] != NULL)
		ft_dprintf(2, "closing for %s:\n", context->params->tbl[0]);
	// head = *(context->redirections);
	head = (context->redirections);
	while (head)
	{
		//on vient pour both pipe et redirection
		redir = (t_redirection*)head->content;
		sh_process_process_execute_close_pipes(redir);
		head = head->next;
	}
	return (SUCCESS);
}
