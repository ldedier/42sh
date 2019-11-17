/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:00:32 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/17 16:02:15 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			fill_option_value(int **address_ptr, int *value_ptr,
				int *address, int value)
{
	*address_ptr = address;
	*value_ptr = value;
	return (1);
}

int			get_option(t_shell *shell, char *option_name, int **option,
		int *value)
{
	(void)shell;
	if (!ft_strcmp(option_name, "vi"))
	{
		return (fill_option_value(option, value,
		((int*)&g_glob.command_line.edit_style), E_EDIT_STYLE_VIM));
	}
	else if (!ft_strcmp(option_name, "readline"))
	{
		return (fill_option_value(option, value,
		((int*)&g_glob.command_line.edit_style), E_EDIT_STYLE_READLINE));
	}
	return (0);
}

int			add_option(t_context *context, int index)
{
	int		*opt;
	int		value;
	char	*option_name;

	option_name = (char *)context->params->tbl[index];
	if (get_option(context->shell, option_name, &opt, &value))
		*opt = value;
	else
		ft_dprintf(2, "%s%s%s", SH_ERR_COLOR, "set: unknown option\n", EOC);
	return (SUCCESS);
}

int			remove_option(t_context *context, int index)
{
	int		*opt;
	int		value;
	char	*option_name;

	option_name = (char *)context->params->tbl[index];
	if (get_option(context->shell, option_name, &opt, &value))
		*opt = !value;
	else
		ft_dprintf(2, "%s%s", SH_ERR_COLOR, "set: unknown option\n", EOC);
	return (SUCCESS);
}
