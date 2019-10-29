/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_string_cls_rbrace.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 09:47:59 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/10/29 09:48:03 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int	jobs_string_rbrace(t_ast_node *node, char **str)
{
	(void)node;
	if ((*str = ft_strjoin_free(*str, "}", 1)) == NULL)
		return (ERROR);
	return (SUCCESS);
}
