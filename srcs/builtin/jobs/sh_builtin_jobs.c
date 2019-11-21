/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_jobs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:04:13 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/19 18:32:32 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"
#include "sh_builtin.h"
#include "string.h"

static void		builtin_jobs_no_spec(int opt)
{
	t_job	*j;

	j = g_job_ctrl->first_job;
	while (j != NULL && !job_is_completed(j) && j->foreground == 0)
	{
		job_print(j, opt, 1);
		j = j->next;
	}
}

static t_job	*jobs_get_job_to_print(int num)
{
	char	msg[100];
	t_job	*j;
	char	*str;

	ft_strcpy(msg, "%");
	j = NULL;
	if (num > 0)
		j = job_get_by_num(num);
	else if (num == 0)
		j = job_get_by_sign('+');
	else if (num == -1)
		j = job_get_by_sign('-');
	if (j == NULL && num > 0)
	{
		str = ft_itoa(num);
		ft_strcat(msg, str);
		free(str);
		sh_perror2(msg, "jobs", "no such job");
	}
	if (j == NULL && num == 0)
		sh_perror("jobs", "no current job");
	else if (j == NULL && num == -1)
		sh_perror("jobs", "no previous job");
	return (j);
}

static int		builtin_jobs_spec(int j_num[], int opt)
{
	int		i;
	t_job	*j;

	i = 0;
	while (j_num[i] != -2)
	{
		j = jobs_get_job_to_print(j_num[i]);
		if (j == NULL)
			return (ERROR);
		if (!job_is_completed(j) && j->foreground == 0)
			job_print(j, opt, 1);
		i++;
	}
	return (SUCCESS);
}

int				sh_builtin_jobs(t_context *context)
{
	int		opt;
	int		job_num_lst[MAX_JOBS];

	if (g_job_ctrl->interactive == 0)
		return (SUCCESS);
	opt = -1;
	while (++opt < MAX_JOBS)
		job_num_lst[opt] = -2;
	opt = 0;
	if ((parse_jobs_args((char **)context->params->tbl, job_num_lst, &opt)))
		return (ERROR);
	if (job_num_lst[0] == -2)
		builtin_jobs_no_spec(opt);
	else
		return (builtin_jobs_spec(job_num_lst, opt));
	return (0);
}
