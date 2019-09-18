#include "sh_21.h"

int 	sh_reset_redirection(t_list **lst)
{
	t_redirection	*el;
	t_list			*del;

	while (*lst)
	{
		el = (*lst)->content;
		if (el->was_apply)
		{
			if (el->backup >= 0)
			{
				if (dup2(el->backup, el->redirected_fd) < 0)
					return (sh_perror(SH_ERR1_INTERN_ERR, "can't reset redirections"));
				close(el->backup);
			}
			else
				close(el->redirected_fd);
		}
		del = *lst;
		(*lst) = (*lst)->next;
		free(el);
		free(del);
	}
	return (SUCCESS);
}