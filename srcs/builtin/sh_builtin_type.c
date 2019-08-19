/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:13:53 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/19 09:51:26 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

#define TYPE_USAGE			"[-atp] name [name ...]"
#define TYPE_A_OPT			0
#define TYPE_A_OPT_USAGE	"Print all the places that contain an executable named name"
#define TYPE_P_OPT			1
#define TYPE_P_OPT_USAGE	"Print the path of the disk file that name would execute."
#define TYPE_T_OPT			2
#define TYPE_T_OPT_USAGE	"Print a string describing the file type"

static int	search_reserved_word(t_context *context, char *name, t_args args[])
{
	int		i;
	const char	*key_words[] = { "!", "{", "}", "[[", "]]", "case", "do",
	"done", "elif", "else", "esac", "fi", "for", "function", "if", "in",
	"select", "then", "until", "until", "while", NULL};

	i = 0;
	while (key_words[i])
	{
		if (ft_strequ(key_words[i], name))
		{
			if (args[TYPE_P_OPT].value && args[TYPE_P_OPT].priority > args[TYPE_T_OPT].priority)
				return (SUCCESS);
			else if (args[TYPE_T_OPT].value)
				ft_dprintf(context->fd[FD_OUT], "keyword\n");
			else
				ft_dprintf(context->fd[FD_OUT], "%s is a shell keyword\n", name);
			return (SUCCESS);
		}
		i++;
	}
	return (ERROR);
}

static int	search_builtin(t_context *context, char *name, t_args args[])
{
	if (sh_builtin_find_name(name))
	{
		if (args[TYPE_P_OPT].value && args[TYPE_P_OPT].priority > args[TYPE_T_OPT].priority)
			return (SUCCESS);
		else if (args[TYPE_T_OPT].value)
			ft_dprintf(context->fd[FD_OUT], "builtin\n");
		else
			ft_dprintf(context->fd[FD_OUT], "%s is a shell builtin\n", name);
		return (SUCCESS);
	}
	return (ERROR);
}

static int	search_hash(t_context *context, char *name, t_args args[])
{
	t_binary		*binary;
	t_hash_finder	finder;

	finder = ft_hash_table_find(context->shell->binaries,
		name, ft_hash_str, compare_str_to_binary);
	if (finder.found)
	{
		binary = (t_binary *)finder.content;
		if (args[TYPE_P_OPT].value && args[TYPE_P_OPT].priority > args[TYPE_T_OPT].priority)
			ft_dprintf(context->fd[FD_OUT], "%s\n", binary->path);
		else if (args[TYPE_T_OPT].value)
			ft_dprintf(context->fd[FD_OUT], "file\n");
		else
			ft_dprintf(context->fd[FD_OUT], "%s is hashed (%s)\n", name, binary->path);
		return (SUCCESS);
	}
	return (ERROR);
}

static int	sh_builtin_type_all(t_context *context, t_args args[], int index, char **argv)
{
	int		ret;
	int		found;
	int		buffer;

	ret = SUCCESS;
	while (argv[index])
	{
		index++;
		found = 0;
		found += !search_reserved_word(context, argv[index - 1], args);
		found += !search_builtin(context, argv[index - 1], args);
		// found += search_hash(context, argv[index - 1], args); // not consulted when -a
		buffer = sh_builtin_type_search_in_path(context, argv[index - 1], args);
		if (buffer == FAILURE)
			return (FAILURE);
		found += !buffer;
		if (found)
			continue ;
		if (!args[TYPE_T_OPT].value && !args[TYPE_P_OPT].value)
			ft_dprintf(context->fd[FD_ERR], "%s: type: %s: not found\n", SH_NAME, argv[index - 1]);
		ret = ERROR;
	}
	return (ret);
}

int			sh_builtin_type(t_context *context)
{
	int				index;
	char			**argv;
	int				ret;
	int				buffer;
	t_args	args[] = {
		{E_ARGS_BOOL, 'a', NULL, NULL, TYPE_A_OPT_USAGE, 0},
		{E_ARGS_BOOL, 'p', NULL, NULL, TYPE_P_OPT_USAGE, 0},
		{E_ARGS_BOOL, 't', NULL, NULL, TYPE_T_OPT_USAGE, 0},
		{E_ARGS_END, 0, NULL, NULL, NULL, 0},
	};

	argv = (char**)context->params->tbl;
	if (sh_builtin_parser(ft_strtab_len(argv), argv, args, &index))
		return (sh_builtin_usage(args, argv[0], TYPE_USAGE, context->shell));
	sh_builtin_parser_show(args);
	if (args[TYPE_A_OPT].value)
		return (sh_builtin_type_all(context, args, index, argv));
	ret = SUCCESS;
	while (argv[index])
	{
		index++;
		if (!search_reserved_word(context, argv[index - 1], args))
			continue ;
		if (!search_builtin(context, argv[index - 1], args))
			continue ;
		if (!search_hash(context, argv[index - 1], args))
			continue ;
		if (((buffer = sh_builtin_type_search_in_path(context, argv[index - 1], args)) == FAILURE))
			return (buffer);
		if (!buffer)
			continue ;
		if (!args[TYPE_T_OPT].value && !args[TYPE_P_OPT].value)
			ft_dprintf(context->fd[FD_ERR], "%s: type: %s: not found\n", "bash", argv[index - 1]);// change bash to SH_NAME
		ret = ERROR;
	}
	return (ret);
}
