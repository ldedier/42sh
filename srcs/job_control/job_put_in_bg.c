/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_put_in_bg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:10:55 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/26 04:44:23 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"

int			job_put_in_bg(t_job *j, int cont)
{
	j->foreground = 0;
	if (cont)
		if (kill (-j->pgid, SIGCONT) < 0)
		{
			ft_dprintf(STDERR_FILENO, "kill");
			return (ERROR);
		}
	return (SUCCESS);
}