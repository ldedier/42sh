/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_string_dgreat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 10:05:29 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/10/29 16:27:24 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int	jobs_string_dgreat(t_ast_node *node, char **str)
{
	(void)node;
	if ((*str = ft_strjoin_free(*str, ">> ", 1)) == NULL)
		return (ERROR);
	return (SUCCESS);
}
