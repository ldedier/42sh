/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_fc_l_synopsis.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:42:22 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/14 17:42:22 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_builtin_fc_l_synopsis(t_context *context, t_fc_options *opts)
{
	(void)context;
	(void)opts;

	if (!opts->from.parsed)
	{
		opts->from.un.integer = -16;
		opts->from.type = E_FC_INTEGER;
	}
	if (!opts->to.parsed)
	{
		opts->to.un.integer = -1;
		opts->to.type = E_FC_INTEGER;
	}
	return (SUCCESS);
}
