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
	else if (c == 'n')
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

static int describe_number(char *str)
{
	int i;

	i = 0;
	if (str[i] == '\0'
			|| (str[i] != '-' && str[i] != '+' && !ft_isdigit(str[i])))
	{
		return (0);
	}
	i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int parse_fc_params(t_context *context, t_fc_options *opts)
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
