/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_fg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:04:13 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/26 03:35:22 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"
#include "sh_builtin.h"


int			sh_builtin_fg(t_context *context)
{
	t_job	*active_job;
	int		res;

	active_job = get_active_job();
	if (active_job == NULL || active_job->pgid == 0)
		return (sh_perror_err("fg", "no such job"));
	ft_printf("sending sigcont to %d %d\n", active_job->number, active_job->pgid);
	if (active_job == NULL)
		return (ERROR);
	return (job_put_in_fg(active_job, 1, &res));
}
