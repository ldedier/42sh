/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_string_default.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:31:00 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/10/28 18:35:14 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

char	*jobs_string_default(t_ast_node *node)
{
	t_ast_node	*child;

	if (node->children)
	{
		child = node->children->content;
		return (child->get_job_string(child));
	}
	return ("LEAF !\n");
}