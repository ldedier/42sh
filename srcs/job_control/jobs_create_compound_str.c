/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_create_compound_str.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 10:02:45 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/28 14:04:36 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_list	*create_brace_str(t_list *e)
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

t_list	*create_subshell_str(t_list *e)
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

t_list	*handle_brace_tok(t_list **s, t_list *e)
{
	t_list	*rbrace;
	t_list	*ptr;

	rbrace = NULL;
	if (!next_sep_is_ampersand(e, &rbrace))
	{
		ptr = e;
		while (ptr && ptr->next != rbrace)
			ptr = ptr->next;
		ptr->next = rbrace->next;
		free(rbrace);
		ptr = *s;
		*s = (*s)->next;
		e = e->next;
		return (e);
	}
	return (create_brace_str(e));
}

t_list	*jobs_create_compound_str(t_list **s, t_list *e, t_symbol_id start_symb)
{
	// int				count;
	t_symbol_id		id;
	// t_token			*t;

	// ft_dprintf(g_term_fd, "compound\n");
	// t = (t_token *)(e->content);
	(void)start_symb;
	id = ((t_token *)(e->content))->id;
	if (id == LEX_TOK_OPN_PAR)
		return (create_subshell_str(e));
	return (handle_brace_tok(s, e));
}