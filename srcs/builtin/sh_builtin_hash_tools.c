/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_hash_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 19:23:54 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/25 07:23:49 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_builtin_hash_add_utility(t_context *context, char *utility)
{
	t_hash_finder	finder;
	t_context		new_context;
	int				ret;

	if (ft_strchr(utility, '/'))
		return (SUCCESS);
	finder = ft_hash_table_find(
		context->shell->binaries, utility, ft_hash_str, compare_str_to_binary);
	if (!finder.found)
	{
		if ((ret = t_context_init(&new_context, context->shell)))
			return (ret);
		ret = ft_dy_tab_add_str(new_context.params, utility);
		if (!ret && !(new_context.builtin = sh_builtin_find(&new_context)))
			ret = sh_traverse_sc_search_in_path(&new_context);
		if (!ret && !new_context.builtin && !new_context.path)
			ret = sh_perror2_err(utility, "hash", "not found");
		t_context_free_content(&new_context);
		return (ret);
	}
	return (SUCCESS);
}

void		sh_builtin_hash_empty_table(t_shell *shell)
{
	t_hash_table	*table;
	unsigned long	i;

	table = shell->binaries;
	i = 0;
	while (i < table->size)
	{
		ft_lstdel(&table->data[i], sh_free_binary_lst);
		i++;
	}
}

static void	sh_builtin_hash_show_binary(t_binary *binary,
		t_binary_stats *stats, int *empty)
{
	if (*empty == 1)
	{
		ft_printf("%-*s %-*s %-*s\n", stats->max_hits_str_len, "hits",
			stats->max_name_len, "name", stats->max_path_len, "path");
		*empty = 0;
	}
	ft_printf("%4d %-*s %-*s\n", binary->hits,
		stats->max_name_len, binary->name, stats->max_path_len, binary->path);
}

int			sh_builtin_hash_show(t_shell *shell)
{
	t_hash_table	*table;
	unsigned long	i;
	t_list			*ptr;
	int				empty;
	t_binary_stats	stats;

	empty = 1;
	table = shell->binaries;
	sh_builtin_hash_update_stats(table, &stats);
	i = 0;
	while (i < table->size)
	{
		ptr = table->data[i];
		while (ptr != NULL)
		{
			sh_builtin_hash_show_binary(
				(t_binary *)ptr->content, &stats, &empty);
			ptr = ptr->next;
		}
		i++;
	}
	if (empty)
		ft_dprintf(FD_OUT, "hash: hash table empty\n");
	return (SUCCESS);
}

void		sh_builtin_hash_update_stats(
	t_hash_table *table, t_binary_stats *stats)
{
	unsigned long	i;
	t_binary		*binary;
	int				ret;
	t_list			*ptr;

	stats->max_path_len = 0;
	stats->max_name_len = 0;
	stats->max_hits_str_len = 0;
	i = 0;
	while (i < table->size)
	{
		ptr = table->data[i];
		while (ptr != NULL)
		{
			binary = (t_binary *)ptr->content;
			if ((ret = ft_strlen(binary->path)) > stats->max_path_len)
				stats->max_path_len = ret;
			if ((ret = ft_strlen(binary->name)) > stats->max_name_len)
				stats->max_name_len = ret;
			if ((ret = ft_longlen(binary->hits)) > stats->max_hits_str_len)
				stats->max_hits_str_len = ret;
			ptr = ptr->next;
		}
		i++;
	}
}
