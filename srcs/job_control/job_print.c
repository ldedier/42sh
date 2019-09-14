/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 00:24:19 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/14 02:10:03 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "job_control.h"
#include "sh_21.h"

void			job_print(void)
{
	t_job		*j;
	t_process	*p;
	int			i;

	if (g_first_job == NULL)
	{
		ft_printf("%sNO JOBS AVAILABLE%s\n", COLOR_GREEN, COLOR_END);
		return ;
	}
	ft_printf("\t\t\t%sPRINTING JOBS%s\n", COLOR_GREEN, COLOR_END);
	j = g_first_job;
	while (j != NULL)
	{
		ft_printf("%sjob: %d%s\n", COLOR_YELLOW, j->number, COLOR_END);
		p = j->first_process;
		while (p != NULL)
		{
			ft_printf("Process pid: %d, pgid: %d\t\t", p->pid,j->pgid);
			ft_printf("%s", COLOR_CYAN);
			print_tab(p->argv);
			ft_printf("%s=========================================================\n", COLOR_GREEN);
			ft_printf("%s", COLOR_END);
			p = p->next;
		}
		j = j->next;
	}
}