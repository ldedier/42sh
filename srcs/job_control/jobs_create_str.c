/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_create_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 07:59:34 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/24 17:28:59 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

static t_job_cmd	*create_job_cmd(t_list *s, t_list *e)
{
	t_job_cmd	*job_cmd;
	char		*str;
	char		*tmp;

	// ft_printf("Creating job command from ");
	// sh_print_token(s->content, g_glob.cfg);
	// ft_printf(" to ");
	// sh_print_token(e->content, g_glob.cfg);
	// ft_printf("\n");
	if ((job_cmd = malloc(sizeof(t_job_cmd))) == NULL)
		return (sh_perrorn(SH_ERR1_MALLOC, "create job command"));
	job_cmd->next = NULL;
	str = NULL;
	while (s != e)
	{
		// if (((t_token *)(s->content))->id == LEX_TOK_LBRACE
		// 	&& s->next && ((t_token *)(s->next->content))->id != LEX_TOK_AND
		// 	&& ((t_token *)(s->next->content))->id != LEX_TOK_PIPE)
		// {
		// 	s = s->next;
		// 	continue ;
		// }
		if ((tmp = create_cmd_word((t_token *)s->content)) == NULL)
			return (NULL);
		if (str == NULL)
			str = tmp;
		else
		{
			str = ft_strjoin_free(str, " ", 1);
			str = ft_strjoin_free(str, tmp, 3);
		}
		// ft_dprintf(g_term_fd, "%sstr: \"%s\"%s\n", YELLOW, str, EOC);
		s = s->next;
	}
	job_cmd->str = str;
	return (job_cmd);
}

static t_list		*handle_pipe_tok(t_list *e)
{
	t_symbol_id		id;
	int				count;

	count = 0;
	// ft_dprintf(g_term_fd, "PIPE TOK\n");
	id = ((t_token *)(e->content))->id;
	while (id != END_OF_INPUT)
	{
		if (id == LEX_TOK_OPN_PAR || id == LEX_TOK_LBRACE)
		{
			count++;
			// ft_dprintf(g_term_fd, "OPEN: %d\n", count);
		}
		else if (id == LEX_TOK_CLS_PAR || id == LEX_TOK_RBRACE)
		{
			count--;
			// ft_dprintf(g_term_fd, "CLOSE: %d\n", count);
		}
		else
			// ft_dprintf(g_term_fd, "SOMETHING ELSE\n");
		if (token_break(id) && count == 0)
		{
			// ft_dprintf(g_term_fd, "TOKEN BREAK\n");
			return (e);
		}
		e = e->next;
		id = ((t_token *)(e->content))->id;
	}
	return (e);
}

static int			s_token_loop(t_list *s)
{
	t_job_cmd	*j_cmd;
	t_list		*e;
	t_symbol_id	id;

	e = NULL;
	while (s != NULL && ((t_token *)(s->content))->id != END_OF_INPUT)
	{
		e = s;
		id = ((t_token *)(e->content))->id;
		while (!token_break(id))
		{
			if (id == LEX_TOK_PIPE)
				e = handle_pipe_tok(e);
			else if (id == LEX_TOK_OPN_PAR || id == LEX_TOK_LBRACE)
				e = jobs_create_compound_str(&s, e, id);
			else
				e = e->next;
			id = ((t_token *)(e->content))->id;
		}
		j_cmd = create_job_cmd(s, e);
		if (j_cmd == NULL)
			return (FAILURE);
		add_job_cmd(j_cmd);
		s = e->next;
	}
	return (SUCCESS);
}

int				jobs_create_str(t_list *token_list)
{
	t_list		*s;

	// sh_print_token_list(token_list, g_glob.cfg);
	if (g_job_ctrl->interactive == 0)
		return (SUCCESS);
	s = token_list;
	s_token_loop(s);
	jobs_print_cmds();
	return (SUCCESS);
}
