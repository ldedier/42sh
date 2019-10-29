/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_string_and_if.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 09:55:25 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/10/29 09:56:05 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int	jobs_string_and_if(t_ast_node *node, char **str)
{
	(void)node;
	if ((*str = ft_strjoin_free(*str, "&&", 1)) == NULL)
		return (ERROR);
	return (SUCCESS);
}
