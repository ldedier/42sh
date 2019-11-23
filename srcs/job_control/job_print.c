/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 04:42:10 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/21 11:00:04 by mdaoud           ###   ########.fr       */
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

static void		print_process_status(t_process *p, int opt, int fd)
{
	int		status;

	status = p->status;
	if (opt)
		ft_dprintf(fd, "%d  ", p->pid);
	if (status == -1 || WIFCONTINUED(status))
		ft_dprintf(fd, "%-19s", "Running");
	else if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		ft_dprintf(fd, "%-19s", "Done");
	else if (WIFEXITED(status))
		ft_dprintf(fd, "%s %-14d", "Exit", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		ft_dprintf(fd, "%-19s", sys_siglist[WTERMSIG(status)]);
	else if (WIFSTOPPED(status))
		ft_dprintf(fd, "%-19s", sys_siglist[WSTOPSIG(status)]);
}

static void		print_job_status(t_job *j, int opt, int fd)
{
	int	status;

	ft_dprintf(fd, "[%d]  %c ", j->number, j->sign);
	status = j->first_process->status;
	if (j->first_process->next == NULL && opt)
		ft_dprintf(fd, "%d  ", j->first_process->pid);
	else if (status == -1 || WIFCONTINUED(status))
		ft_dprintf(fd, "%-19s", "Running");
	else if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		ft_dprintf(fd, "%-19s", "Done");
	else if (WIFEXITED(status))
		ft_dprintf(fd, "%s %-14d", "Exit", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		ft_dprintf(fd, "%-19s", sys_siglist[WTERMSIG(status)]);
	else if (WIFSTOPPED(status))
		ft_dprintf(fd, "%-19s", sys_siglist[WSTOPSIG(status)]);
	ft_dprintf(fd, "%s\n", j->command);
}

static void		print_job_differant_status(t_job *j, int opt, int fd)
{
	t_process	*p;

	p = j->first_process;
	ft_dprintf(fd, "[%d]  %c ", j->number, j->sign);
	while (p->next != NULL)
	{
		print_process_status(p, opt, fd);
		ft_dprintf(fd, "%s|\n       ", p->cmd);
		p = p->next;
	}
	print_process_status(p, opt, fd);
	ft_dprintf(fd, "%s\n", p->cmd);
}

void			job_print(t_job *j, int opt, int fd)
{
	if (job_has_same_status(j) && opt == 0)
		print_job_status(j, opt, fd);
	else
		print_job_differant_status(j, opt, fd);
}
