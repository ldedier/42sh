/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_string_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 10:10:41 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/10/29 16:23:45 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int	jobs_string_word(t_ast_node *node, char **str)
{
	// ft_dprintf(g_term_fd, "WORD\n");
	// node->token->
	 /*ft_dprintf(g_term_fd, "value: %s\n", node->token->value);*/
	if ((*str = ft_strjoin_free(*str, node->token->value, 1)) == NULL)
		return (ERROR);
	if ((*str = ft_strjoin_free(*str, " ", 1)) == NULL)
		return (ERROR);
	return (SUCCESS);
}
