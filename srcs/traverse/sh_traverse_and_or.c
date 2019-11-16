/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_and_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:54:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/16 09:05:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

/*
** sh_traverse_and_or :
** This is the browser of the t_list and_or (grammar)
** We execute a and_or node, check it return value and
** execute or not the next and_or node follow the found token
** AND_IF or OR_IF.
**
** We also call the function sh_env_update_question_mark to be sur
** that at this time, the return value is set in the env variable
*/

long		sh_traverse_and_or(t_ast_node *node, t_context *context)
{
	int		ret;

	ret = sh_execute_and_or(node, context);
	sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	return (ret);
}
