#include "sh_21.h"

static int 		sh_redirection_for_heredoc(char *str, t_redirection *redirection, t_context *context)
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
int 	sh_traverse_tools_io_here_redirection(t_ast_node *node, t_context *context)
{
	int 			ret;
	t_redirection 	redir;

	if ((ret = sh_redirection_for_heredoc(node->token->value, &redir, context)) == SUCCESS)
		ret = sh_add_redirection(redir.type,
			context->redirected_fd, redir.fd, &(context->redirections));
	return (ret);
}