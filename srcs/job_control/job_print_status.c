/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_print_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 15:30:50 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/21 16:19:00 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

void			job_print_status(t_job *j, const char *new_status)
{
	ft_dprintf(g_job_ctrl->term_fd, "[%d]\t%s\n", j->number, new_status);
}