/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_alias_show.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 22:53:28 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/13 05:46:19 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	show_get_min_init(char **min, char **alias)
{
	int		i;

	*min = alias[0];
	i = 1;
	while (alias[i])
	{
		if (ft_strcmp(*min, alias[i]) > 0)
			*min = alias[i];
		i++;
	}
	return (SUCCESS);
}

static int	show_get_min(char **min, char **alias)
{
	int		i;
	char	*new_min;

	i = 0;
	new_min = NULL;
	while (alias[i])
	{
		if (!new_min)
		{
			if (ft_strcmp(*min, alias[i]) < 0)
				new_min = alias[i];
		}
		else if (ft_strcmp(new_min, alias[i]) > 0
			&& ft_strcmp(*min, alias[i]) < 0)
			new_min = alias[i];
		i++;
	}
	*min = new_min;
	return (SUCCESS);
}

void		show_alias(char *str)
{
	int		i;
	char	*equal;

	if (!(equal = ft_strchr(str, '=')))
		ft_printf("%s %s\n", ALIAS_MSG, str);
	else
	{
		*equal = '\0';
		ft_printf("%s %s=", ALIAS_MSG, str);
		i = 1;
		ft_putchar('\'');
		while (equal[i])
		{
			if (equal[i] == '\'' || equal[i] == '\\')
				ft_putchar('\\');
			ft_putchar(equal[i]);
			i++;
		}
		ft_putchar('\'');
		ft_putchar('\n');
		*equal = '=';
	}
}

int			sh_builtin_alias_show(t_context *context)
{
	char	**tbl;
	char	*min;

	tbl = (char**)(context->alias->tbl);
	if (!tbl || !*tbl)
		return (SUCCESS);
	if (write(FD_OUT, NULL, 0))
		return (sh_perror2_err("write error", "alias", SH_ERR1_BAD_FD));
	min = NULL;
	show_get_min_init(&min, tbl);
	while (min)
	{
		show_alias(min);
		show_get_min(&min, tbl);
	}
	return (SUCCESS);
}
