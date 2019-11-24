/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 15:13:21 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/24 15:13:31 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"

/*
** job_num[MAX_JOBS] is a statically allocated array of ints.
** If the job_num[i] = 0, it means that this job number <i> is not taken.
** If we decide to assign it to our newly created job,
**	we set the job_num[i] to 1.
** Whenever we free a completed job, we reset the job_num[i] to 0
**	so that it can be retaken by another job later.
*/

static int		find_available_job_number(void)
{
	int		i;

	i = 1;
	while (i < MAX_JOBS)
	{
		if (g_job_ctrl->job_num[i] == 0)
			return (i);
		i++;
	}
	return (-1);
}

static void		init_job_values(t_job *j, int n, int bg)
{
	j->first_process = NULL;
	j->next = NULL;
	j->signal_num = 0;
	j->notified = 0;
	j->pgid = 0;
	j->foreground = (bg == 0 ? 1 : 0);
	j->sign = ' ';
	if (bg)
		job_added_update_sign(j);
	j->number = n;
	g_job_ctrl->job_num[n] = 1;
	g_job_ctrl->curr_job = j;
}

static int		get_job_string(t_ast_node *node, char *str, t_job *j)
{
	char		*tmp;

	if (str != NULL)
		j->command = ft_strdup(str);
	else
	{
		tmp = NULL;
		if ((g_grammar[node->symbol->id].get_job_string(node, &tmp)))
			return (ERROR);
		j->command = tmp;
		if (j->command == NULL)
			return (sh_perror(SH_ERR1_MALLOC, "job add"));
	}
	if (j->command == NULL)
		return (sh_perror(SH_ERR1_MALLOC, "job add"));
	j->cmd_copy = ft_strdup(j->command);
	if (j->cmd_copy == NULL)
	{
		free(j->command);
		return (sh_perror(SH_ERR1_MALLOC, "job add"));
	}
	return (SUCCESS);
}

/*
** First we find the right number to assign to the job.
** Then we initialize the job values.
** Then we get the right command for the job (the string).
** If the job is the first job added,
**	we point the head of our global structure to it.
** If not, we add it the tail of the job list.
*/

int				job_add(t_ast_node *node, char *str, int bg)
{
	t_job	*j;
	t_job	*it;
	int		n;

	if ((n = find_available_job_number()) < 0)
		return (sh_perror_err("Maxumum number of jobs exceeded", NULL));
	if ((j = malloc(sizeof(t_job))) == NULL)
		return (sh_perror(SH_ERR1_MALLOC, "job add"));
	init_job_values(j, n, bg);
	if (get_job_string(node, str, j) != SUCCESS)
	{
		free(j);
		return (FAILURE);
	}
	if (g_job_ctrl->first_job == NULL)
	{
		g_job_ctrl->first_job = j;
		return (SUCCESS);
	}
	it = g_job_ctrl->first_job;
	while (it->next != NULL)
		it = it->next;
	it->next = j;
	return (SUCCESS);
}
