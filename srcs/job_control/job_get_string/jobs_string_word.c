/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_string_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 10:10:41 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/10/29 10:12:51 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int	jobs_string_word(t_ast_node *node, char **str)
{
	if ((*str = ft_strjoin_free(*str, node->token->value, 1)) == NULL)
		return (ERROR);
	return (SUCCESS);
}
