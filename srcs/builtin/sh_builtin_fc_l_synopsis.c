/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_fc_l_synopsis.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:42:22 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/14 17:42:22 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		get_listing_way(t_history *history, t_dlist *from, t_dlist *to)
{
	int from_number;
	int to_number;

	from_number = ((t_entry *)from)->number;
	to_number = ((t_entry *)to)->number;

	(void)history;
	return (1);
}

void	sh_builtin_fc_list(t_history *history, t_dlist *from,
	t_dlist *to, int opt_n)
{
	int		list_way;
	t_dlist	*ptr;

	list_way = get_listing_way(history, from, to);
	ptr = from;
	while (ptr != to)
	{
		t_entry_print(ptr->content, !opt_n);
		if (list_way == 1)
			ptr = ptr->next;
		else
			ptr = ptr->prev;
	}
	if (to != from)
		t_entry_print(ptr->content, !opt_n);
}

void static print_fc_operand(t_fc_operand *op)
{
	if (op->type == E_FC_STRING)
	{
		ft_printf("string: %s\n", op->un.string);
	}
	else
		ft_printf("int: %d\n", op->un.integer);
}

int		sh_builtin_fc_l_synopsis(t_context *context, t_fc_options *opts)
{
	t_dlist *from;
	t_dlist *to;

	if (!opts->from.parsed)
	{
		opts->from.un.integer = 16;
		opts->from.type = E_FC_INTEGER;
	}
	if (!opts->to.parsed)
	{
		opts->to.un.integer = -1;
		opts->to.type = E_FC_INTEGER;
	}
	print_fc_operand(&opts->from);
	print_fc_operand(&opts->to);

//	print_history(&context->shell->history);
	if (!(from = get_entry_from_fc_operand(&context->shell->history, &opts->from)))
		return (sh_perror_err(SH_BLT_HISTORY_RANGE, NULL));
	if (!(to = get_entry_from_fc_operand(&context->shell->history, &opts->to)))
		return (sh_perror_err(SH_BLT_HISTORY_RANGE, NULL));
	if (opts->opt_r)
		sh_builtin_fc_list(&context->shell->history, to, from, opts->opt_n);
	else
		sh_builtin_fc_list(&context->shell->history, from, to, opts->opt_n);
	return (SUCCESS);
}
