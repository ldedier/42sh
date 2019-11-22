/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_cmd_word.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:31:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/16 09:05:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

long		sh_traverse_cmd_word(t_ast_node *node, t_context *context)
{
	return (sh_traverse_cmd_suffix(node, context));
}
