/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_print_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 17:36:23 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/03 17:57:13 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

void			jobs_print_cmds(void)
{
	t_job_cmd	*ptr;
	size_t		i;

	if (g_job_ctrl == NULL || g_job_ctrl->job_cmd == NULL)
		return ;
	ft_dprintf(g_job_ctrl->term_fd, "%s%s\n============================\n"
		, BLUE, "JOB COMMANDS", EOC);
	ptr = g_job_ctrl->job_cmd;
	i = 1;
	while (ptr != NULL)
	{
		ft_dprintf(g_job_ctrl->term_fd, "%s[%d]: %s%s\n", YELLOW, i, ptr->str, EOC);
		i++;
		ptr = ptr->next;
	}
	ft_dprintf(g_job_ctrl->term_fd, "%s============================%s\n"
		, BLUE, EOC);
}