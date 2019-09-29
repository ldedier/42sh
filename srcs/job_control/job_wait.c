/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 23:10:38 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/30 01:34:34 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

void		job_wait(t_job *j, int *res)
{
	int		status;
	pid_t	pid;


	pid = waitpid(-1, &status, WUNTRACED);
	while (!job_check_changes(pid, status) && !job_is_stopped(j)
			&& !job_is_completed(j))
		pid = waitpid(-1, &status, WUNTRACED);
	*res = status;
}