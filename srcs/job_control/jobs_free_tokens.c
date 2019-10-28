/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_free_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 12:27:52 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/26 14:59:39 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void		jobs_free_tokens(void)
{
	t_list	*ptr;
	t_list	*l_next;
	// t_token	*t;
	// t_list	*ptr;

	if (!g_job_ctrl->interactive)
		return ;
	ptr = g_job_ctrl->tokens;
	while (ptr != NULL)
	{
		l_next = ptr->next;
		free(ptr->content);
		free(ptr);
		ptr = l_next;
	}
	// free(g_job_ctrl->tokens);
	g_job_ctrl->tokens = NULL;
}