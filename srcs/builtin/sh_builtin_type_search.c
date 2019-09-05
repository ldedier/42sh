/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_type_search.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 21:46:13 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/04 21:47:56 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_builtin_type_search_reserved(
	t_context *context, char *name, t_args args[])
{
	int			i;
	const char	*key_words[] = { "!", "{", "}", "[[", "]]", "case", "do",
	"done", "elif", "else", "esac", "fi", "for", "function", "if", "in",
	"select", "then", "until", "until", "while", NULL};

	i = 0;
	while (key_words[i])
	{
		if (ft_strequ(key_words[i], name))
		{
			if (args[TYPE_P_OPT].value
				&& args[TYPE_P_OPT].priority > args[TYPE_T_OPT].priority)
				return (SUCCESS);
			else if (args[TYPE_T_OPT].value)
				ft_dprintf(context->fd[FD_OUT], "keyword\n");
			else
			{
				ft_dprintf(
					context->fd[FD_OUT], "%s is a shell keyword\n", name);
			}
			return (SUCCESS);
		}
		i++;
	}
	return (ERROR);
}

int			sh_builtin_type_search_builtin(
	t_context *context, char *name, t_args args[])
{
	if (sh_builtin_find_name(name))
	{
		if (args[TYPE_P_OPT].value
			&& args[TYPE_P_OPT].priority > args[TYPE_T_OPT].priority)
			return (SUCCESS);
		else if (args[TYPE_T_OPT].value)
			ft_dprintf(context->fd[FD_OUT], "builtin\n");
		else
			ft_dprintf(context->fd[FD_OUT], "%s is a shell builtin\n", name);
		return (SUCCESS);
	}
	return (ERROR);
}

int			sh_builtin_type_search_hash(
	t_context *context, char *name, t_args args[])
{
	t_binary		*binary;
	t_hash_finder	finder;

	finder = ft_hash_table_find(context->shell->binaries,
		name, ft_hash_str, compare_str_to_binary);
	if (finder.found)
	{
		binary = (t_binary *)finder.content;
		if (args[TYPE_P_OPT].value
			&& args[TYPE_P_OPT].priority > args[TYPE_T_OPT].priority)
			ft_dprintf(context->fd[FD_OUT], "%s\n", binary->path);
		else if (args[TYPE_T_OPT].value)
			ft_dprintf(context->fd[FD_OUT], "file\n");
		else
		{
			ft_dprintf(context->fd[FD_OUT],
			"%s is hashed (%s)\n", name, binary->path);
		}
		return (SUCCESS);
	}
	return (ERROR);
}
