/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_fc_l_synopsis.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:42:22 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/17 20:07:37 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		get_true_rank(t_history *history, int number)
{
	int res;

	if (history->from < history->to)
		res = number;
	else
	{
		if (number < history->from)
			res = history->nb_entries - history->from + number;
		else
			res = number - history->from;
	}
	return (res);
}

int		get_listing_way(t_history *history, t_dlist *from, t_dlist *to)
{
	int from_number;
	int to_number;

	from_number = ((t_entry *)from->content)->number;
	to_number = ((t_entry *)to->content)->number;
	return (get_true_rank(history, to_number)
		- get_true_rank(history, from_number));
}

void	sh_builtin_fc_list(t_history *history, t_dlist *from,
	t_dlist *to, int opt_n)
{
	int		list_way;
	t_dlist	*ptr;

	list_way = get_listing_way(history, from, to);
	ptr = from;
	if (from == to)
		t_entry_print(ptr->content, !opt_n);
	while (ptr != to)
	{
		t_entry_print(ptr->content, !opt_n);
		if (list_way < 0)
			ptr = ptr->next;
		else
			ptr = ptr->prev;
	}
	if (to != from)
		t_entry_print(ptr->content, !opt_n);
}

void	print_fc_operand(t_fc_operand *op)
{
	if (op->type == E_FC_STRING)
	{
		ft_printf("string: %s\n", op->un.string);
	}
	else
		ft_printf("int: %d\n", op->un.integer);
}

void	swap_entries(t_history *history, t_dlist **from, t_dlist **to)
{
	t_dlist *tmp;

	if (get_listing_way(history, *from, *to) > 0)
	{
		tmp = *from;
		*from = *to;
		*to = tmp;
	}
}

int		sh_builtin_fc_l_synopsis(t_context *context, t_fc_options *opts)
{
	t_dlist *from;
	t_dlist *to;

	if (!opts->from.parsed)
	{
		ft_printf("auto opt from ! \n");
		opts->from.un.integer = -16;
		opts->from.type = E_FC_INTEGER;
	}
	if (!opts->to.parsed)
	{
		ft_printf("auto opt to ! \n");
		opts->to.un.integer = -1;
		opts->to.type = E_FC_INTEGER;
	}
//	ft_printf("HISTORY:\n");
//	print_history(&context->shell->history);
//	ft_printf("000000000000000000000000\n");
//	print_fc_operand(&opts->from);
//	print_fc_operand(&opts->to);
	
	if (!(from = get_entry_from_fc_operand(&context->shell->history, &opts->from)))
		return (sh_perror_err(SH_BLT_HISTORY_RANGE, NULL));
	if (!(to = get_entry_from_fc_operand(&context->shell->history, &opts->to)))
		return (sh_perror_err(SH_BLT_HISTORY_RANGE, NULL));
	
//	ft_printf("FROM: %p\n", from->content);
//	ft_printf("TO: %p\n", to->content);	
	if (opts->opt_r)
		swap_entries(&context->shell->history, &from, &to);
	sh_builtin_fc_list(&context->shell->history, from, to, opts->opt_n);
	return (SUCCESS);
}
