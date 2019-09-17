
#include "sh_21.h"

static int	is_saved(t_list *lst_redir, int fd)
{
	t_redirection 	*redir;

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
 * We creat a backup for the given fd
 * If the fd to save was close we return -1
 * Otherwise, the backup fd
 * -2 if an error occur
 *
 * If the dup creat a fd wich is already
 * in the list. That's mean the user already
 * closed this fd. So we re-do a dup until we
 * find a "non-used" fd.
*/
static int	save_fd(t_redirection_type type, t_list *lst, int fd)
{
	int 			backup;
	int 			tmp;

	if ((backup = sh_check_open_fd(type, fd)) >= 0)
	{
		if ((backup = dup(fd)) < 0)
			return (-2);
		if (is_saved(lst, backup))
		{
			tmp = save_fd(type, lst, fd);
			close(backup);
			return (tmp);
		}
	}
	return (backup);
}

static int	apply_dup(t_redirection *el)
{
	if (el->fd >= 0)
	{
		if (sh_verbose_pipe())
			ft_dprintf(2, "\t%d became %d\n",
					el->fd, el->redirected_fd);
		if (dup2(el->fd, el->redirected_fd) == -1)
			return (sh_perror(SH_ERR1_INTERN_ERR,
						"process_exec_dup_pipes 2"));
	}
	else if (el->fd == -1)
	{
		if (sh_verbose_pipe())
			ft_dprintf(2, "\tclosing %d\n", el->redirected_fd);
		close(el->redirected_fd);
	}
	el->was_apply = 1;
	return (SUCCESS);
}

int 		sh_execute_redirection(t_context *context)
{
	t_redirection	*el;
	t_list			*lst;

	lst = context->redirections;
	if (sh_verbose_pipe())
		ft_dprintf(2, "Redirections for %s:\n", context->params->tbl[0]);
	while (lst)
	{
		el = lst->content;
		if ((el->backup = save_fd(el->type, context->redirections, el->redirected_fd)) == -2 || apply_dup(el))
		{
			sh_perror(SH_ERR1_INTERN_ERR, "Error to apply redirection");
			return (STOP_CMD_LINE);
		}

		lst = lst->next;
	}
	return (SUCCESS);
}