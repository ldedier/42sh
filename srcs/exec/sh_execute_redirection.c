
#include "sh_21.h"

// static int	apply_dup(t_redirection *el)
// {
// 	if (el->fd >= 0)
// 	{
// 		if (sh_verbose_pipe())
// 			ft_dprintf(2, "\t%d became %d\n",
// 					el->fd, el->redirected_fd);
// 		if (dup2(el->fd, el->redirected_fd) == -1)
// 			return (sh_perror(SH_ERR1_INTERN_ERR,
// 						"executing redirection"));
// 	}
// 	else if (el->fd == -1)
// 	{
// 		if (sh_verbose_pipe())
// 			ft_dprintf(2, "\tclosing %d\n", el->redirected_fd);
// 		close(el->redirected_fd);
// 	}
// 	return (SUCCESS);
// }

int 		sh_execute_redirection(t_list *lst, t_redirection *el)
{
	(void)lst;/////////////////
	if (sh_verbose_pipe())
		ft_dprintf(2, "Redirections %d:\n", el->fd);
	if (el->fd >= 0)
	{
		if (sh_verbose_pipe())
			ft_dprintf(2, "\t%d became %d\n",
					el->fd, el->redirected_fd);
		if (dup2(el->fd, el->redirected_fd) == -1)
			return (sh_perror(SH_ERR1_INTERN_ERR,
						"executing redirection"));
	}
	else if (el->fd == -1)
	{
		if (sh_verbose_pipe())
			ft_dprintf(2, "\tclosing %d\n", el->redirected_fd);
		close(el->redirected_fd);
	}
	return (SUCCESS);
}





// int 		sh_execute_redirection(t_context *context)
// {
// 	t_redirection	*el;
// 	t_list			*lst;

// 	lst = context->redirections;
// 	if (sh_verbose_pipe())
// 		ft_dprintf(2, "Redirections for %s:\n", context->params->tbl[0]);
// 	while (lst)
// 	{
// 		el = lst->content;
// 		if ((el->backup = save_fd(el->type, context->redirections, el->redirected_fd)) == -2 || apply_dup(el))
// 		{
// 			sh_perror(SH_ERR1_INTERN_ERR, "Error to apply redirection");
// 			return (STOP_CMD_LINE);
// 		}

// 		lst = lst->next;
// 	}
// 	return (SUCCESS);
// }