/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_pipe_sequence.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/22 01:40:43 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
 * pipe_to_do :
 * This function is called when we have pipes to execute.
 * We do here the first fork. That's mean, in this case, we have to add
 * this new process in the jobs list.
*/
static int		pipe_to_do(t_ast_node *node, t_context *context)
{
	int		ret;
	int 	child;

	if ((child = fork()) < 0)
		return (sh_perror(SH_ERR1_FORK, "execution fork for pipe"));
	else if (child)
	{
		waitpid(child, &ret, 0);
		sh_env_update_ret_value_wait_result(context, ret);
		return (SH_RET_VALUE_EXIT_STATUS(ret));
	}
	else
	{
		child = getpid();
		ft_printf("Forked for the pipe, %d %d\n", child, getpgid(child));
		ret = sh_execute_pipe(node, context);
		exit(ret);
	}
}

/*
 * sh_traverse_pipe_sequence :
 * This is the browser of t_list pipe_sequence
 * We check if we have separator pipe
 * If we don't, we just call the next level on the ast simple_command
 * If we have, we do the first fork here and call the pipe_sequence_execute
 * wich will perform all pipe and call traverse_command for each sons.
*/
int				sh_traverse_pipeline(t_ast_node *node, t_context *context)
{
	int		ret;

	sh_traverse_tools_show_traverse_start(node, context);
	if (ft_lstlen(node->children) > 1)
		ret = pipe_to_do(node, context);
	else
		ret = sh_traverse_command(node->children->content, context);
	sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	return (ret);
}
