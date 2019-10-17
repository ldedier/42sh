/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 04:42:10 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/17 02:40:01 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"
#include "string.h"

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

static void		print_process_status(t_process *p, int pid_flag)
{
	int		status;
	int	print_fd;

	print_fd = (pid_flag == 0 ? STDOUT_FILENO : g_term_fd);
	status = p->status;
	// ft_dprintf(g_term_fd, "<%d>: %#X (%d)\n", p->pid, p->status, p->status);
	if (status == -1 || WIFCONTINUED(status))
		ft_dprintf(print_fd, "Running    ");
	if (WIFEXITED(status))
		ft_dprintf(print_fd, "Done       ");
	else if (WIFSIGNALED(status))
		ft_dprintf(print_fd, "%-11s", strsignal(WTERMSIG(status)));
	else if (WIFSTOPPED(status))
		ft_dprintf(print_fd, "%-11s", strsignal(WSTOPSIG(status)));
}

static void		print_job_status(t_job *j, int pid_flag)
{
	int	status;
	int	print_fd;

	print_fd = (pid_flag == 0 ? STDOUT_FILENO : g_term_fd);
	ft_dprintf(print_fd, "[%d]  ", j->number);
	status = j->first_process->status;
	if (j->first_process->next == NULL && pid_flag)
		ft_dprintf(print_fd, "%d  ",j->first_process->pid);
	if (status == -1 || WIFCONTINUED(status))
		ft_dprintf(print_fd, "Running    ");
	if (WIFEXITED(status))
		ft_dprintf(print_fd, "Done       ");
	else if (WIFSIGNALED(status))
		ft_dprintf(print_fd, "%-11s", strsignal(WTERMSIG(status)));
	else if (WIFSTOPPED(status))
		ft_dprintf(print_fd, "%-11s", strsignal(WSTOPSIG(status)));
	ft_dprintf(print_fd, "%s\n", j->command);
}

static void		print_job_differant_status(t_job *j, int pid_flag)
{
	t_process	*p;
	int			print_fd;

	print_fd = (pid_flag == 0 ? STDOUT_FILENO : g_term_fd);
	p = j->first_process;
	ft_dprintf(print_fd, "[%d]  ", j->number);
	while (p->next != NULL)
	{
		print_process_status(p, pid_flag);
		ft_dprintf(print_fd, "\"%s|\"\n     ", p->cmd);
		p = p->next;
	}
	print_process_status(p, pid_flag);
	ft_dprintf(print_fd, "\"%s\"\n", p->cmd);
}


void			job_print(t_job *j, int pid_flag)
{
	if (job_has_same_status(j))
		print_job_status(j, pid_flag);
	else
		print_job_differant_status(j, pid_flag);
}