/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 19:04:16 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/25 11:23:10 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_builtin_container		*get_builtins(void)
{
	static t_builtin_container res[NB_BUILTINS] = {
		{ "echo", sh_builtin_echo },
		{ "pwd", sh_builtin_pwd },
		{ "exit", sh_builtin_exit },
		{ "type", sh_builtin_type },
		{ "cd", sh_builtin_cd },
		{ "verbose", sh_builtin_verbose },
		{ "hash", sh_builtin_hash },
		{ "export", sh_builtin_export },
		{ "set", sh_builtin_set },
		{ "unset", sh_builtin_unset },
		{ "export", sh_builtin_unset },
		{ "test", sh_builtin_test },
		{ "jobs", sh_builtin_jobs},
		{ "fg", sh_builtin_fg},
		{ "bg", sh_builtin_bg},
		{ "fc", sh_builtin_fc },
		{ "alias", sh_builtin_alias },
		{ "unalias", sh_builtin_unalias },
		{ "beeeh", sh_builtin_bonus }
	};

	return (res);
}

t_builtin				sh_builtin_find_name(char *name)
{
	int					i;
	t_builtin_container	*builtins;

	builtins = get_builtins();
	i = 0;
	while (i < NB_BUILTINS)
	{
		if (!ft_strcmp(name, builtins[i].name))
			return (builtins[i].builtin);
		i++;
	}
	return (NULL);
}

t_builtin				sh_builtin_find(t_context *context)
{
	int					i;
	t_builtin_container	*builtins;

	builtins = get_builtins();
	i = 0;
	while (i < NB_BUILTINS)
	{
		if (!ft_strcmp(context->params->tbl[0], builtins[i].name))
			return (builtins[i].builtin);
		i++;
	}
	return (NULL);
}
