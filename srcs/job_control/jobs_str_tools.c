/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_str_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:02:42 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/28 13:46:39 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			next_sep_is_ampersand(t_list *ptr, t_list **rbrace)
{
	t_list		*it;
	t_symbol_id	id;
	int			count;

	it = ptr->next;
	count = 1;
	id = ((t_token *)(it->content))->id;
	while (id != END_OF_INPUT)
	{
		// ft_printf("id = %d\n", sh_index(id));
		if (id == LEX_TOK_RBRACE)
		{
			count--;
			if (count == 0)
				*rbrace = it;
			// ft_printf("\'}\' so count : %d\n", count);
		}
		if (id == LEX_TOK_LBRACE)
		{
			count++;
			// ft_printf("\'{\' so count : %d\n", count);
		}
		else
		{
			if (id == LEX_TOK_AND || id == LEX_TOK_PIPE)
			{
				if (count == 0)
					return (1);
			}
			else if (token_break(id))
			{
				if (count == 0)
					return (0);
			}
		}
		it = it->next;
		id = ((t_token *)(it->content))->id;
	}
	return (0);
}

int			token_break(t_symbol_id id)
{
	return (id == END_OF_INPUT || id == LEX_TOK_SEMICOL || id == LEX_TOK_AND
		|| id == LEX_TOK_AND_IF || id == LEX_TOK_OR_IF);
}


int			add_job_cmd(t_job_cmd *cmd)
{
	t_job_cmd	*it;

	if (g_job_ctrl->job_cmd == NULL)
		g_job_ctrl->job_cmd = cmd;
	else
	{
		it = g_job_ctrl->job_cmd;
		while (it->next != NULL)
			it = it->next;
		it->next = cmd;
	}
	return (SUCCESS);
}


char		*create_cmd_word(t_token *t)
{
	char	*str;

	// ft_printf("creating word from: ");
	// sh_print_token(t, g_glob.cfg);
	// ft_printf("\n");
	if (t->id == LEX_TOK_WORD || t->id == LEX_TOK_IO_NUMBER)
	{
		// ft_dprintf(g_term_fd, "token %s\n", t->value);
		if ((str = ft_strdup(t->value)) == NULL)
			return (sh_perrorn(SH_ERR1_MALLOC, "create job command"));
		return (str);
	}
	// else if ((str = ft_strdup(g_glob.cfg->symbols[t->index].debug)) == NULL)
	// 		return (sh_perror(SH_ERR1_MALLOC, "create job command"));
	else
	{
		// ft_dprintf(g_term_fd, "token %s\n", g_glob.cfg->symbols[t->index].debug);
		str = ft_strdup(g_glob.cfg->symbols[t->index].debug);
		return (str);
	}

}