/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_fc_s_synopsis.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:46:05 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/17 21:16:22 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	fill_finder(t_fc_operand **finder)
{

}

int		sh_builtin_fc_s_synopsis(t_context *context, t_fc_options *opts)
{
	t_dlist			*entry_ptr;
	t_fc_operand	*finder;
	char			*to_replace;
	char			*d;

	to_replace = NULL;
	if (!opts->from.parsed)
	{
		ft_printf("auto opt from ! \n");
		opts->from.un.integer = -1;
		opts->from.type = E_FC_INTEGER;
		opts->from.parsed = 1;
		finder = &opts->from;
	}
	else if (opts->from.type == E_FC_STRING
		&& ft_strchr(opts->from.un.string, '=') && !opts->to.parsed)
	{
		opts->to.un.integer = -1;
		opts->to.type = E_FC_INTEGER;
		opts->to.parsed = 1;
		to_replace = opts->from.un.string;
		finder = &opts->to;
	}
	else
		finder = &opts->from;
	if (!(entry_ptr
		= get_entry_from_fc_operand(&context->shell->history, finder)))
	   	return (sh_perror_err(SH_BLT_NO_CMD_FOUND, NULL));
	if (substitution_str && substitute())
	return (SUCCESS);
}
