/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_fc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 19:11:45 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/13 19:11:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include <limits.h>

int			invalid_argument(char *str, char c)
{
	ft_dprintf(2, "%s%s: %s: -%c: invalid option%s\n", SH_ERR_COLOR,
		SH_NAME, str, c, COLOR_END);
	return (ERROR);
}

static int	parse_fc_editor(t_context *context, int index, t_fc_options *opts)
{
	if (index < (int)context->params->current_size)
	{
		opts->editor = context->params->tbl[index];
		return (SUCCESS);
	}
	else
		return (sh_perror_err("fc: -e: need_argument", NULL));
}

static int	parse_fc_boolean_options(char c, t_fc_options *opts)
{
	if (c  == 's')
		opts->opt_s = 1;
	else if (c == 'l')
		opts->opt_l = 1;
	else if (c == 'r')
		opts->opt_n = 1;
	else if (c == 'r')
		opts->opt_r = 1;
	else
		return (0);
	return (1);
}

static int	parse_fc_options(t_context *context, int *index, t_fc_options *opts)
{
	int i;

	i = 1;
	while (((char *)context->params->tbl[*index])[i])
	{
		if (parse_fc_boolean_options(((char *)context->params->tbl[*index])[i], opts))
			;
		else if (((char *)context->params->tbl[*index])[i] == 'e')
		{
			if (((char *)context->params->tbl[*index])[i + 1])
			{
				opts->editor = &context->params->tbl[*index][i + 1];
				return (SUCCESS);
			}
			else
				return (parse_fc_editor(context, ++(*index), opts));
		}
		else
			return (invalid_argument("fc",
				((char **)(context->params->tbl))[*index][i]));
		i++;
	}
	return (SUCCESS);
}

static int sh_atoi_infinite(char *str, int *error)
{
	int		res;
	int		i;

	res = 0;
	*error = 0;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (ft_isdigit(str[i]))
		*error = 1;
	while (str[i] && ft_isdigit(str[i]))
	{
		res = res * 10 +  str[i] - '0';
		if (res > HISTSIZE)
			return (str[0] == '-' ? -res : res);
		i++;
	}
	return (str[0] == '-' ? -res : res);
}

static void	process_parse_fc_operand(t_fc_operand *operand, char *str)
{
	int error;

	operand->un.integer = sh_atoi_infinite(str, &error);
	if (error)
		operand->type = E_FC_STRING;
	else
	{
		operand->type = E_FC_INTEGER;
		operand->un.string = str;
	}
	operand->parsed = 1;
}

static int	parse_fc_operands(t_context *context, int index, t_fc_options *options)
{
	t_fc_operand *operand;

	if (options->from.parsed)
		operand = &options->to;
	else
		operand = &options->from;
	process_parse_fc_operand(operand, context->params->tbl[index]);
	return (SUCCESS);
}

static int parse_fc_params(t_context *context, t_fc_options *opts)
{
	int i;

	i = 1;
	while (i < (int)context->params->current_size
		&& ((char *)context->params->tbl[i])[0] == '-')
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

int		sh_builtin_fc(t_context *context)
{
	t_fc_options opts;

	ft_bzero(&opts, sizeof(opts));
	/*
	t_args args[] = {
		{E_ARGS_INT, 0, NULL, NULL, NULL, 0},
		{E_ARGS_INT, 0, NULL, NULL, NULL, 0},
		{E_ARGS_BOOL, 0, NULL, NULL, NULL, 0},
		{E_ARGS_BOOL, 0, NULL, NULL, NULL, 0},
		{E_ARGS_BOOL, 0, NULL, NULL, NULL, 0},
		{E_ARGS_BOOL, 0, NULL, NULL, NULL, 0},
		{E_ARGS_STRING, 0, NULL, NULL, NULL, 0}
	};
	*/
	if (parse_fc_params(context, &opts) != SUCCESS)
		return (ERROR);
	if (opts.opt_s)
		return (sh_builtin_fc_s_synopsis(context, &opts));
	else if (opts.opt_l)
		return (sh_builtin_fc_l_synopsis(context, &opts));
	else
		return (sh_builtin_fc_default_synopsis(context, &opts));
}
