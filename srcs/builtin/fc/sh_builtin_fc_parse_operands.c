/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_fc_parse_parameters.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 04:52:00 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/17 15:31:35 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_atoi_fc(const char *str, int *error)
{
	int		res;
	int		i;

	res = 0;
	*error = 0;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		res = res * 10 + str[i] - '0';
		if (res > HISTSIZE)
			return (str[0] == '-' ? -res : res);
		i++;
	}
	if (str[i] != '\0')
		*error = 1;
	return (str[0] == '-' ? -res : res);
}

static void	process_parse_fc_operand(t_fc_operand *operand,
		char *str)
{
	int error;

	operand->un.integer = sh_atoi_fc(str, &error);
	if (error)
	{
		operand->type = E_FC_STRING;
		operand->un.string = str;
	}
	else
		operand->type = E_FC_INTEGER;
	operand->parsed = 1;
}

int			parse_fc_operands(t_context *context, int index,
			t_fc_options *options)
{
	t_fc_operand *operand;

	if (options->from.parsed)
		operand = &options->to;
	else
		operand = &options->from;
	process_parse_fc_operand(operand, context->params->tbl[index]);
	return (SUCCESS);
}
