/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_create_cmds_tools.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:02:42 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/25 10:44:51 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			next_sep_is_ampersand(t_list *ptr)
{
	t_list		*it;
	t_symbol_id	id;
	int			count;

	it = ptr;
	count = 1;
	id = ((t_token *)(ptr->content))->id;
	while (id != END_OF_INPUT)
	{
		if (id == LEX_TOK_RBRACE)
		{
			count--;
			ft_printf("\'{\' so count : %d\n", count);
		}
		if (id == LEX_TOK_LBRACE)
		{
			count++;
			ft_printf("\'}\' so count : %d\n", count);
		}
		if (id == LEX_TOK_AND && count == 0)
			return (1);
		else if (id == LEX_TOK_SEMICOL && count == 0)
			return (0);
		it = it->next;
		id = ((t_token *)(it->content))->id;
	}
	return (0);
}

t_list	*create_brace_cmd(t_list *e)
{
	int				count;
	t_symbol_id		id;
	// t_token			*t;

	// ft_dprintf(g_term_fd, "compound\n");
	// t = (t_token *)(e->content);
	id = ((t_token *)(e->content))->id;
	count = 1;
	// ft_printf("Start symblol: ");
	// sh_print_token(t, g_glob.cfg);
	// ft_printf("\n");
	e = e->next;
	while (id != END_OF_INPUT && count > 0)
	{
		id = ((t_token *)(e->content))->id;
		// t = (t_token *)(e->content);
		// sh_print_token(t, g_glob.cfg);
		// ft_printf("	count: %d, Keep going\n", count);
		if (id == LEX_TOK_RBRACE)
			count--;
		else if (id == LEX_TOK_LBRACE)
			count++;
		e = e->next;
	}
	// ft_printf("After compound: ");
	// sh_print_token((t_token *)(e->content), g_glob.cfg);
	// ft_printf("\ncount: %d\n", count);
	return (e);
}

t_list	*create_subshell_cmd(t_list *e)
{
	int				count;
	t_symbol_id		id;
	// t_token			*t;

	// ft_dprintf(g_term_fd, "compound\n");
	// t = (t_token *)(e->content);

	// ft_printf("Start symblol: ");
	// sh_print_token(t, g_glob.cfg);
	// ft_printf("\n");
	id = ((t_token *)(e->content))->id;
	count = 1;
	e = e->next;
	while (id != END_OF_INPUT && count > 0)
	{
		id = ((t_token *)(e->content))->id;
		// t = (t_token *)(e->content);
		// sh_print_token(t, g_glob.cfg);
		// ft_printf("	count: %d, Keep going\n", count);
		if (id == LEX_TOK_CLS_PAR)
			count--;
		else if (id == LEX_TOK_OPN_PAR)
			count++;
		e = e->next;
	}
	// ft_printf("After compound: ");
	// sh_print_token((t_token *)(e->content), g_glob.cfg);
	// ft_printf("\ncount: %d\n", count);
	return (e);
}

t_list	*create_compound_cmd(t_list *e, t_symbol_id start_symb)
{
	// int				count;
	t_symbol_id		id;
	// t_token			*t;

	// ft_dprintf(g_term_fd, "compound\n");
	// t = (t_token *)(e->content);
	(void)start_symb;
	id = ((t_token *)(e->content))->id;
	if (id == LEX_TOK_OPN_PAR)
		return (create_subshell_cmd(e));
	// else if (id == LEX_TOK_LBRACE)
	return (create_brace_cmd(e));
}