/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_jobs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:04:13 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/15 04:35:20 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"
#include "sh_builtin.h"
#include "string.h"

// static void		print_job_status(t_job *j)
// {
// 	if (job_is_completed(j))
// 		ft_printf("[%d]\tCompleted\t\t%s\n", j->number, j->command);
// 	else if (job_is_stopped(j))
// 		ft_printf("[%d]\tStopped\t\t%s\n", j->number, j->command);
// 	else
// 		ft_printf("[%d]\tRunning\t\t%s\n", j->number, j->command);
// }


static int		job_has_same_status(t_job *j)
{
	int			status;
	t_process	*p;
	if (j == NULL || j->first_process == NULL)
		return (1);
	p = j->first_process;
	status = p->status;
	p = p->next;
	while (p != NULL)
	{
		if (p->status != status)
			return (0);
		p = p->next;
	}
	return (1);
}

static void		print_process_status(t_process *p)
{
	int		status;

	status = p->status;
	if (status == -1)
		ft_printf("Running    ");
	if (WIFEXITED(status))
		ft_printf("Done       ");
	else if (WIFSIGNALED(status))
		ft_printf("%-11s", strsignal(WTERMSIG(status)));
	else if (WIFSTOPPED(status))
		ft_printf("%-11s", strsignal(WSTOPSIG(status)));
}

static void		print_job_status(t_job *j)
{
	int	status;

	ft_printf("[%d]  ", j->number);
	status = j->first_process->status;
	if (status == -1)
		ft_printf("Running    ");
	if (WIFEXITED(status))
		ft_printf("Done       ");
	else if (WIFSIGNALED(status))
		ft_printf("%-11s", strsignal(WTERMSIG(status)));
	else if (WIFSTOPPED(status))
		ft_printf("%-11s", strsignal(WSTOPSIG(status)));
	ft_printf("%s\n", j->command);
}

static void		print_job_differant_status(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	ft_printf("[%d]  ", j->number);
	while (p->next != NULL)
	{
		print_process_status(p);
		ft_printf("\"%s\"|\n     ", p->cmd);
		p = p->next;
	}
	print_process_status(p);
	ft_printf("\"%s\"\n", p->cmd);
}

int				sh_builtin_jobs(t_context *context)
{
	t_job	*j;

	(void)context;
	// ft_printf("%s\n", strsignal(SIGHUP));
	if (g_job_ctrl->first_job == NULL)
		return (SUCCESS);
	j = g_job_ctrl->first_job;
	while (j != NULL && !job_is_completed(j) && j->foreground == 0)
	{
		if (job_has_same_status(j))
			print_job_status(j);
		else
			print_job_differant_status(j);
		j = j->next;
	}
	return (0);
}
