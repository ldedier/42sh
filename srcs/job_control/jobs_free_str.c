/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_free_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 09:54:53 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/25 09:58:36 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		jobs_free_str(void)
{
	t_job_cmd	*tmp;

	tmp = g_job_ctrl->job_cmd;
	g_job_ctrl->job_cmd = g_job_ctrl->job_cmd->next;
	if (tmp)
	{
		free(tmp->str);
		free(tmp);
	}
	return (SUCCESS);
}