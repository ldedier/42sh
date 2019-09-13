/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:06:13 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/19 19:12:14 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_exec_builtin_fill_fd:
**	read all redirections associated with a builtin command and fill context->fd
**	field. this fild descriptors will be used to read/write on in/output.
*/

// static void	sh_exec_builtin_fill_fd(t_context *context)
// {
// 	t_list			*head;
// 	t_redirection	*redir;

// 	context->fd[0] = 0;
// 	context->fd[1] = 1;
// 	context->fd[2] = 2;
// 	if (!context->redirections)
// 		return ;
// 	head = *(context->redirections);
// 	while (head)
// 	{
// 		redir = head->content;
// 		if (redir->type == OUTPUT && redir->redirected_fd >= 0
// 				&& redir->redirected_fd <= 2)
// 			context->fd[redir->redirected_fd] = redir->fd;
// 		head = head->next;
// 	}
// 	if (sh_verbose_pipe())
// 	{
// 		ft_dprintf(2, "process_Execute_dup_pipes\n");
// 		ft_dprintf(2, "\tfdin  : %d\n", context->fd[FD_IN]);
// 		ft_dprintf(2, "\tfdout : %d\n", context->fd[FD_OUT]);
// 		ft_dprintf(2, "\tfderr : %d\n", context->fd[FD_ERR]);
// 	}
// }

/*
** sh_exec_builtin:
**	Execute a builtin function, update $? env variable. Manage pipes
**	redirections for builtins.
**
**	return Value:
**		FAILURE : termcaps error (sh_reset_shell(0) == -1)
**		any value returned by a builtin function
*/

int			sh_exec_builtin(t_context *context)
{
	int		res;

	// sh_exec_builtin_fill_fd(context);
	if (isatty(0) && sh_reset_shell(0) == -1)
	{
		sh_process_execute_close_pipes(context);
		return (FAILURE);
	}
	res = context->builtin(context);
	if (res == SUCCESS)
		sh_env_update_ret_value(context->shell, SH_RET_SUCCESS);
	else
		sh_env_update_ret_value(context->shell, SH_RET_ERROR);
	if (isatty(0) && sh_set_shell_back(0) == ATTR_ERROR)
		return (sh_perror("Could not modify this terminal attributes", NULL));
	sh_process_execute_close_pipes(context);
	return (res);
}
