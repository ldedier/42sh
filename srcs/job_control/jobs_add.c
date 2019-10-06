/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 00:09:20 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/30 18:02:33 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"

static int	find_available_job_number(void)
{
	int		i;

	i = 1;
	while (i < MAX_JOBS)
	{
		if (g_job_ctrl->job_num[i] == 0)
			return (i);
		i++;
	}
	return (-1);
}

static void	init_job_values(t_job *j, int n, int fg)
{
	j->first_process = NULL;
	j->next = NULL;
	j->signal_num = 0;
	j->notified = 0;
	j->pgid = 0;
	j->number = n;
	g_job_ctrl->job_num[n] = 1;
	j->pipe_node = 0;
	g_job_ctrl->pipe_node = 0;
	g_job_ctrl->curr_job = j;
	// j->foreground = g_job_ctrl->ampersand_eol ^ 1;
	j->foreground = fg;
}

int			jobs_add(int fg)
{
	t_job	*j;
	t_job	*it;
	int		n;

	n = find_available_job_number();
	if (n < 0)
		return (jc_error_free("Maximum number of jobs exceeded",
			"job_add", 0, STOP_CMD_LINE));
	if ((j = malloc(sizeof(t_job))) == NULL)
		return (jc_error_free(SH_ERR1_MALLOC, "jobs_add", 1, FAILURE));
	init_job_values(j, n, fg);
	// ft_printf("%sJob %d added in %s%s\n",COLOR_GREEN, j->number, j->foreground == 1 ? "foreground" : "background", COLOR_END);
	j->command = NULL;	//	Fill it with the command
	// Add the newly created job at the end of the job list.
	if (g_job_ctrl->first_job == NULL)
	{
		g_job_ctrl->first_job = j;
		return (SUCCESS);
	}
	it = g_job_ctrl->first_job;
	while (it->next != NULL)
		it = it->next;
	it->next = j;
	return (SUCCESS);
}