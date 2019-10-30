/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_simple_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:31:19 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/30 22:58:08 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

int 		sh_execute_simple_command(t_ast_node *father_node, t_context *context)
{
	int 	ret;

	ret = SUCCESS;
	if (!context->params->tbl || !context->params->tbl[0])
		return (SUCCESS);
	if (ret == SUCCESS)
	{
		if ((context->builtin = sh_builtin_find(context)))
			ret = sh_execute_builtin(father_node, context);
		else
			ret = sh_execute_binary(father_node, context);
	}
	return (ret);
}
