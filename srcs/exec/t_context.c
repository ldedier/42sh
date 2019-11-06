/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_context.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 21:45:25 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/18 12:03:50 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** t_context_init:
**	take a t_context* in parameter and set every values to it's default value
**
**	return : SUCCESS or FAILURE
*/

int			t_context_init(t_context *context, t_shell *shell)
{
	ft_bzero(context, sizeof(t_context));
	if (!(context->params = ft_dy_tab_new(5)))
		return (sh_perror(SH_ERR1_MALLOC, "t_context_init"));
	context->wflags = (g_job_ctrl->interactive ? WUNTRACED : 0);
	context->cmd_type = SIMPLE_NODE;
	context->path = NULL;
	context->shell = shell;
	context->env = shell->env;
	context->saved_env = shell->saved_env;
	context->vars = shell->vars;
	context->alias = shell->alias;
	context->term = &shell->term;
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
	ft_dy_tab_del_ptr(context->params);
	if (context->path)
		free(context->path);
}

/*
** t_context_reset:
**	Free and reset content after command execution
*/

void		t_context_reset(t_context *context)
{
	int		i;

	i = 0;
	while (i < (int)context->params->current_size)
	{
		free(context->params->tbl[i]);
		context->params->tbl[i] = NULL;
		i++;
	}
	context->params->current_size = 0;
	if (context->path)
		ft_strdel(&context->path);
	context->builtin = NULL;
	context->shell->ret_value_set = 0;
}
