/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_string_lbrace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 09:41:53 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/10/29 16:24:40 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int	jobs_string_lbrace(t_ast_node *node, char **str)
{
	(void)node;
	if ((*str = ft_strjoin_free(*str, "{ ", 1)) == NULL)
		return (ERROR);
	return (SUCCESS);
}
