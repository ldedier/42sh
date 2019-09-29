/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_is_completed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:19:55 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/29 19:06:26 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

int		job_is_completed(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p != NULL)
	{
		if (p->completed == 0)
			return (0);
		p = p->next;
	}
	return (1);
}


/* This piece of code needs rework for commands like "sleep 43 || sleep 43 &" */

// int		job_is_completed(t_job *j)
// {
// 	t_process	*p;

// 	p = j->first_process;
// 	// if (j->pipe_node == 2)
// 	// 	return (0);
// 	while (p != NULL)
// 	{
// 		// if (p->completed == 0 || (j->pipe_node == 0))
// 		if (p->completed == 0)
// 		{
// 			// if (j->pipe_node == 2)
// 				// ft_printf("process missing\n");
// 			return (0);
// 		}
// 		p = p->next;
// 	}
// 	return (1);
// }