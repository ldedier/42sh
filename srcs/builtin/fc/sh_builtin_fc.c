/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_fc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 19:11:45 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/17 15:15:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	parse_fc_params(t_context *context, t_fc_options *opts)
{
	int i;

	i = 1;
	while (i < (int)context->params->current_size
		&& ((char *)context->params->tbl[i])[0] == '-'
		&& !describe_number(((char *)context->params->tbl[i]))
		&& ft_strlen(((char *)context->params->tbl[i])) > 1)
	{
		if (!ft_strcmp("--", (char *)context->params->tbl[i]))
		{
			i++;
			break ;
		}
		if (parse_fc_options(context, &i, opts))
			return (ERROR);
		i++;
	}
	while (i < (int)context->params->current_size && !opts->to.parsed)
	{
		if (parse_fc_operands(context, i, opts))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int			sh_builtin_fc(t_context *context)
{
	t_fc_options opts;

	ft_bzero(&opts, sizeof(opts));
	if (parse_fc_params(context, &opts) != SUCCESS)
		return (ERROR);
	if (opts.opt_s)
		return (sh_builtin_fc_s_synopsis(context, &opts));
	else if (opts.opt_l)
		return (sh_builtin_fc_l_synopsis(context, &opts));
	else
		return (sh_builtin_fc_default_synopsis(context, &opts));
}
