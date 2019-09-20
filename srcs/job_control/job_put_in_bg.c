/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_put_in_bg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:10:55 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/21 00:54:47 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"

int			job_put_in_bg(t_job *j, int cont)
{
	if (cont)
		if (kill (-j->pgid, SIGCONT) < 0)
		{
			ft_dprintf(STDERR_FILENO, "kill");
			return (-1);
		}
	return (0);
}