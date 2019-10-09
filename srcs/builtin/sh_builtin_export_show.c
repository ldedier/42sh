/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_export_show.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 04:11:01 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/07 00:36:30 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	show_get_min_init(char **min, char **env)
{
	int		i;

	*min = env[0];
	i = 1;
	while (env[i])
	{
		if (ft_strcmp(*min, env[i]) > 0)
			*min = env[i];
		i++;
	}
	return (SUCCESS);
}

static int	show_get_min(char **min, char **env)
{
	int		i;
	char	*new_min;

	i = 0;
	new_min = NULL;
	while (env[i])
	{
		if (!new_min)
		{
			if (ft_strcmp(*min, env[i]) < 0)
				new_min = env[i];
		}
		else if (ft_strcmp(new_min, env[i]) > 0 && ft_strcmp(*min, env[i]) < 0)
			new_min = env[i];
		i++;
	}
	*min = new_min;
	return (SUCCESS);
}

static void	show_assignment(char *str)
{
	int		i;
	char	*equal;

	if (!(equal = ft_strchr(str, '=')))
		ft_printf("%s %s\n", EXPORT_MSG, str);
	else
	{
		*equal = '\0';
		ft_printf("%s %s=", EXPORT_MSG, str);
		i = 1;
		ft_putchar('\"');
		while (equal[i])
		{
			if (equal[i] == '\'' || equal[i] == '\\' || equal[i] == '\"')
				ft_putchar('\\');
			ft_putchar(equal[i]);
			i++;
		}
		ft_putchar('\"');
		ft_putchar('\n');
		*equal = '=';
	}
}

int			sh_builtin_export_show(t_context *context)
{
	char	**tbl;
	char	*min;

	if (write(FD_OUT, NULL, 0))
		return (sh_perror2_err("write error", "export", SH_ERR1_BAD_FD));
	tbl = (char**)(context->saved_env->tbl);
	if (!tbl || !*tbl)
		return (SUCCESS);
	min = NULL;
	show_get_min_init(&min, tbl);
	while (min)
	{
		show_assignment(min);
		show_get_min(&min, tbl);
	}
	return (SUCCESS);
}
