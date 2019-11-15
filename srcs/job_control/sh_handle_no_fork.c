/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_handle_no_fork.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:40:13 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/15 11:33:21 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	handle_int(int signo)
{
	if (signo == SIGINT)
	{
		ft_dprintf(g_term_fd, RED"SIGINT"EOC);
		g_job_ctrl->flag = 1;
		get_down_from_command(&g_glob.command_line);
		g_glob.command_line.interrupted = 1;
	}
}
