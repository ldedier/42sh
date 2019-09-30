/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pgid_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:30:51 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/30 23:14:23 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"

int				set_pgid_parent(int cpid, t_context *context)
{
	int		ret;

	if ((ret = process_add(context, cpid)) != SUCCESS)
		return (ret);
	if ((ret = set_child_pgid(cpid)) != SUCCESS)
		return (ret);
	ft_dprintf(1, "Added process: %s", (char **)context->params->tbl[0]);
	ft_dprintf(1, "\tpid: %d, pgid: %d to job [%d]\n", cpid, getpgid(cpid), g_job_ctrl->curr_job->number);
	return (SUCCESS);
}
