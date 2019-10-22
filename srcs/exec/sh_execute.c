/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:31:19 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/21 07:27:36 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

int 	sh_execute_simple_command(t_context *context)
{
	int 	ret;

	ret = SUCCESS;
	if (!context->params->tbl || !context->params->tbl[0])
		return (SUCCESS);
	// if (!ft_strchr(context->params->tbl[0], '/'))
	// 	ret = sh_no_slash_cmd(context);
	// else
	// 	ret = sh_slash_cmd(context);
	if (ret == SUCCESS)
	{
		if ((context->builtin = sh_builtin_find(context)))
			ret = sh_execute_builtin(context);
		else
			ret = sh_exec_binaire(context);
	}
	return (ret);
}