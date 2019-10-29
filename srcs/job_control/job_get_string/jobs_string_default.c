/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_string_default.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:31:00 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/10/29 16:17:56 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int	jobs_string_default(t_ast_node *node, char **str)
{
	t_list		*lst;
	t_ast_node	*child;

	lst = node->children;
	while (lst)
	{
		child = lst->content;
		if (g_grammar[child->symbol->id].get_job_string(child, str) != SUCCESS)
			return (ERROR);
		lst = lst->next;
	}
	return (SUCCESS);
}
