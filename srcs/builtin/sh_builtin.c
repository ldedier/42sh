/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 19:04:16 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/21 18:03:45 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_builtin			sh_builtin_find(t_context *context)
{
	if (!ft_strcmp(context->params->tbl[0], "echo"))
		return (&sh_builtin_echo);
	else if (!ft_strcmp(context->params->tbl[0], "pwd"))
		return (&sh_builtin_pwd);
	else if (!ft_strcmp(context->params->tbl[0], "exit"))
		return (&sh_builtin_exit);
	else if (!ft_strcmp(context->params->tbl[0], "where"))
		return (&sh_builtin_where);
	else if (!ft_strcmp(context->params->tbl[0], "cd"))
		return (&sh_builtin_cd);
	else if (!ft_strcmp(context->params->tbl[0], "verbose"))
		return (&sh_builtin_verbose);
	else if (!ft_strcmp(context->params->tbl[0], "set"))
		return (&sh_builtin_set);
	return (NULL);
}
