/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_check_open_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:06:52 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/21 20:31:10 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	is_saved(t_list *lst_redir, int fd)
{
	t_redirection	*redir;

	while (lst_redir)
	{
		redir = lst_redir->content;
		if (redir->redirected_fd == fd)
			return (1);
		lst_redir = lst_redir->next;
	}
	return (0);
}

/*
** We creat a backup for the given fd
** If the fd to save was close we return -1
** Otherwise, the backup fd
** -2 if an error occur
**
** If the dup creat a fd wich is already
** in the list. That's mean the user already
** closed this fd. So we re-do a dup until we
** find a "non-used" fd.
*/

static int	save_fd(t_list *lst, t_redirection_type type, int fd)
{
	int	backup;
	int	tmp;

	if ((backup = sh_check_open_fd(fd)) >= 0)
	{
		if ((backup = dup(fd)) < 0)
			return (-2);
		if (is_saved(lst, backup))
		{
			tmp = save_fd(lst, type, fd);
			close(backup);
			return (tmp);
		}
	}
	return (backup);
}

/*
** We check if the destination fd is not close one.
** Return -1 if not
** Return fd if it's ok
**
** If fd and one backup are egual means fd it's close.
** Because backup can only took on close fd.
*/

int			sh_check_dst_fd(t_list *lst, int fd)
{
	t_redirection	*el;

	if (fd == TTY_FD)
		return (-1);
	while (lst)
	{
		el = lst->content;
		if (el->backup == fd)
			return (-1);
		if (el->fd == fd && el->was_closed == 1)
			return (-1);
		lst = lst->next;
	}
	return (sh_check_open_fd(fd));
}

/*
** If the source fd is egual to a backup we need to take a
** new backup.
** If source fd is not close we need to create a backup.
**
** return -1 if error
** otherwise 0
*/

int			sh_check_src_fd(t_list *head, t_redirection *curr_redir)
{
	t_redirection		*el;
	t_list				*lst;

	lst = head;
	while (lst)
	{
		el = lst->content;
		if (el->backup == curr_redir->redirected_fd)
		{
			if ((el->backup = save_fd(
				head, curr_redir->type, curr_redir->redirected_fd)) == -1)
				return (-1);
			close(curr_redir->redirected_fd);
			break ;
		}
		lst = lst->next;
	}
	if (sh_check_open_fd(curr_redir->redirected_fd) != -1)
	{
		if ((curr_redir->backup = save_fd(
			head, curr_redir->type, curr_redir->redirected_fd)) < 0)
			return (-1);
	}
	return (0);
}
