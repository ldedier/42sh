/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_string_default.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:31:00 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/10/29 09:30:07 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int	jobs_string_default(t_ast_node *node, char **str)
{
	t_list	*lst;

	lst = node->children;
	while (lst)
	{
		if (lst->content->get_job_string(lst->content, str) != SUCCESS)
			return (ERROR);
		lst = lst->next;
	}
	return (SUCCESS);
}
