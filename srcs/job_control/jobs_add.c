/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 00:09:20 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/26 05:12:47 by mdaoud           ###   ########.fr       */
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

int			jobs_add(void)
{
	t_job	*j;
	t_job	*it;
	int		n;

	n = find_available_job_number();
	if (n < 0)
	{
		ft_dprintf(STDERR_FILENO, "Max number of jobs exceded\n");
		return (-1);
	}
	if ((j = malloc(sizeof(t_job))) == NULL)
		return (FAILURE);
	j->number = n;
	j->foreground = g_job_ctrl->ampersand_eol ^ 1;
	// j->foreground = 1;
	ft_dprintf(g_job_ctrl->term_fd, "Job %d added in %s\n",
		j->number, j->foreground == 1 ? "foreground" : "background");
	j->signal_num = 0;
	g_job_ctrl->job_num[n] = 1;
	j->first_process = NULL;
	j->next = NULL;
	j->notified = 0;
	j->pgid = 0;
	j->command = NULL;	//	Fill it with the command
	g_job_ctrl->curr_job = j;
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