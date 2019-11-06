/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_string_great_and.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 10:09:57 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/10/29 16:27:48 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int	jobs_string_great_and(t_ast_node *node, char **str)
{
	(void)node;
	if ((*str = ft_strjoin_free(*str, ">& ", 1)) == NULL)
		return (ERROR);
	return (SUCCESS);
}
