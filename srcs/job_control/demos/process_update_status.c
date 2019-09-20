/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_update_status.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:32:56 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/21 00:33:43 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"

void		process_update_status(void)
{
	int status;
	pid_t pid;

	do
		pid = waitpid (-1, &status, WUNTRACED|WNOHANG);
	while (!mark_process_status (pid, status));
}