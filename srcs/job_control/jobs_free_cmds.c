/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_free_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 17:49:52 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/03 17:54:28 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

void			jobs_free_cmds(void)
{
	t_job_cmd	*ptr;

	if (g_job_ctrl->jc_enabled == 0)
		return ;
	ptr = g_job_ctrl->job_cmd;
	while (g_job_ctrl->job_cmd != NULL)
	{
		ptr = g_job_ctrl->job_cmd->next;
		free(g_job_ctrl->job_cmd->str);
		free(g_job_ctrl->job_cmd);
		g_job_ctrl->job_cmd = ptr;
	}
}
