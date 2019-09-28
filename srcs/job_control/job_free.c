/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 01:52:35 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/28 16:40:05 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"

void		job_free(t_job *j)
{
	t_process	*p;
	t_process	*p_next;

	if (j == NULL)
		return ;
	p = j->first_process;
	while(p != NULL)
	{
		// ft_printf("Freeing process : ");
		// str_tab_print(p->argv);
		// ft_printf("\n");
		p_next = p->next;
		str_tab_free(p->argv);
		free(p);
		p = p_next;
	}
	// str_tab_free(j->command);	//Add later
	free(j);
}