/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_jobs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:04:13 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/20 05:43:17 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"
#include "sh_builtin.h"
#include "string.h"

#define	JOBS_P	1
#define	JOBS_L	2

int				sh_builtin_jobs(t_context *context)
{
	t_job	*j;
	int		opt;
	int		job_num_lst[MAX_JOBS];

	if (g_job_ctrl->interactive == 0)
		return (SUCCESS);
	opt = -1;
	while (++opt < MAX_JOBS)
		job_num_lst[opt] = -1;
	opt = 0;
	if ((parse_jobs_args((char **)context->params->tbl, job_num_lst, &opt)))
		return (ERROR);
	// ft_dprintf(g_term_fd, "jobs: ");
	// for(int i = 0 ; job_num_lst[i] != -1; i++)
	// {
	// 	ft_dprintf(g_term_fd, "[%d] ", job_num_lst[i]);
	// }
	// ft_dprintf(g_term_fd, "\noptions: %d\n", opt);
	// ft_printf("%s\n", strsignal(SIGHUP));
	if (g_job_ctrl->first_job == NULL)
		return (SUCCESS);
	j = g_job_ctrl->first_job;
	while (j != NULL && !job_is_completed(j) && j->foreground == 0)
	{
		job_print(j, 0);
		j = j->next;
	}
	return (0);
}
