/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_fc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 19:11:45 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/17 15:14:24 by ldedier          ###   ########.fr       */
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
	if (c == 's')
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

int			parse_fc_options(t_context *context, int *index, t_fc_options *opts)
{
	int		i;
	char	*str;

	str = ((char *)context->params->tbl[*index]);
	i = 1;
	while (str[i])
	{
		if (parse_fc_boolean_options(str[i], opts))
			;
		else if (str[i] == 'e')
		{
			if (str[i + 1])
			{
				opts->editor = &str[i + 1];
				return (SUCCESS);
			}
			else
				return (parse_fc_editor(context, ++(*index), opts));
		}
		else
			return (invalid_argument("fc", str[i]));
		i++;
	}
	return (SUCCESS);
}

int			describe_number(char *str)
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
