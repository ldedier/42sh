/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_type_search.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 21:46:13 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/12 07:05:26 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_builtin_type_search_alias:
**	Look in alias table if name match a declared alias.
**	Reserved words list correspond to bash's list, not to our implementation.
**	If found message shown depend on options specified.
**
**	Returned Values
**		SUCCESS : matched an alias
**		ERROR : do not matched any alias
*/

int			sh_builtin_type_search_alias(
	char *name, t_args args[], t_context *context)
{
	int			index;
	char		*value;

	if ((index = sh_vars_get_index(context->alias, name)) != -1)
	{
		if (args[TYPE_P_OPT].priority > args[TYPE_T_OPT].priority)
			return (ERROR);
		if (args[TYPE_T_OPT].value)
			ft_dprintf(FD_OUT, "alias\n");
		else
		{
			value = sh_env_get_value((char**)context->alias->tbl, name);
			ft_dprintf(FD_OUT, "%s is aliased to `%s'\n", name, value);
		}
		return (SUCCESS);
	}
	return (ERROR);
}

/*
** sh_builtin_type_search_reserved:
**	Look in a constant table if name match an existing reserved word.
**	Reserved words list correspond to bash's list, not to our implementation.
**	If found message shown depend on options specified.
**
**	Returned Values
**		SUCCESS : matched a builtin
**		ERROR : do not matched any builtin
*/

int			sh_builtin_type_search_reserved(char *name, t_args args[])
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
				ft_dprintf(FD_OUT, "keyword\n");
			else
				ft_dprintf(FD_OUT, "%s is a shell keyword\n", name);
			return (SUCCESS);
		}
		i++;
	}
	return (ERROR);
}

/*
** sh_builtin_type_search_builtin:
**	Look in builtin list if name match an existing builtin.
**	If found message shown depend on options specified.
**
**	Returned Values
**		SUCCESS : matched a builtin
**		ERROR : do not matched any builtin
*/

int			sh_builtin_type_search_builtin(char *name, t_args args[])
{
	if (sh_builtin_find_name(name))
	{
		if (args[TYPE_P_OPT].value
			&& args[TYPE_P_OPT].priority > args[TYPE_T_OPT].priority)
			return (SUCCESS);
		else if (args[TYPE_T_OPT].value)
			ft_dprintf(FD_OUT, "builtin\n");
		else
			ft_dprintf(FD_OUT, "%s is a shell builtin\n", name);
		return (SUCCESS);
	}
	return (ERROR);
}

/*
** sh_builtin_type_search_hash:
**	Use hash table api function to look if name match and hashed binary.
**	If found message shown depend on options specified.
**
**	Returned Values
**		SUCCESS : matched a hashed binary
**		ERROR : do not matched any hash
*/

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
			ft_dprintf(FD_OUT, "%s\n", binary->path);
		else if (args[TYPE_T_OPT].value)
			ft_dprintf(FD_OUT, "file\n");
		else
		{
			ft_dprintf(FD_OUT,
			"%s is hashed (%s)\n", name, binary->path);
		}
		return (SUCCESS);
	}
	return (ERROR);
}
