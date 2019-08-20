/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_context.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 21:45:25 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/20 15:27:33 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_free_context_dup_lst:
**	Free a t_context object. Function is used with ft_lstdel.
*/

void		sh_free_context_dup_lst(void *c, size_t dummy)
{
	t_context	*context;

	context = (t_context *)c;
	if (context->path)
		ft_strdel(&context->path);
	ft_dy_tab_del(context->params);
	free(context);
	(void)dummy;
}

t_context	*t_context_dup(t_context *context)
{
	t_context *res;

	if (!(res = (t_context *)malloc(sizeof(t_context))))
		return (NULL);
	ft_memcpy(res, context, sizeof(t_context));
	if (context->path && (!(res->path = ft_strdup(context->path))))
	{
		free(res);
		return (NULL);
	}
	if (!(res->params = ft_dy_tab_cpy_str(context->params)))
	{
		ft_strdel(&res->path);
		free(res);
		return (NULL);
	}
	return (res);
}

/*
** t_context_init:
**	take a t_context* in parameter and set every values to it's default value
**
**	return : SUCCESS or FAILURE
*/

int			t_context_init(t_context *context, t_shell *shell)
{
	if (!(context->params = ft_dy_tab_new(5)))
		return (sh_perror(SH_ERR1_MALLOC, "t_context_init"));
	context->path = NULL;
	context->shell = shell;
	context->env = shell->env;
	context->saved_env = NULL;
	context->vars = shell->vars;
	context->term = &shell->term;
	context->fd[0] = 0;
	context->fd[1] = 1;
	context->fd[2] = 2;
	context->builtin = NULL;
	context->current_command_node = NULL;
	context->current_pipe_sequence_node = NULL;
	context->phase = -1;
	context->pid = 0;
	context->redirected_fd = -1;
	context->redirections = NULL;
	return (SUCCESS);
}

/*
** t_context_free_content:
**	Free any allocated memory in a t_context structure
*/

void		t_context_free_content(t_context *context)
{
	ft_dy_tab_del(context->params);
	if (context->saved_env)
		ft_dy_tab_del(context->saved_env);
	if (context->path)
		free(context->path);
}
