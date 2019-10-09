/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_create_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 07:59:34 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/09 01:42:40 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

static char			*create_cmd_word(t_token *t)
{
	char	*str;

	// ft_printf("creating word from: ");
	// sh_print_token(t, g_glob.cfg);
	// ft_printf("\n");
	if (t->id == LEX_TOK_WORD)
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

static t_job_cmd		*create_job_cmd(t_list *s, t_list *e)
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

static int	add_job_cmd(t_job_cmd *cmd)
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

int			jobs_create_cmds(t_list *token_list)
{
	t_list		*s;
	t_list		*e;
	t_job_cmd	*cmd;

	if (g_job_ctrl->interactive == 0)
		return (SUCCESS);
	s = token_list;
	// sh_print_token_list(token_list, g_glob.cfg);
	while (s != NULL && ((t_token *)(s->content))->id != END_OF_INPUT)
	{
		e = s;
		while (((t_token *)(e->content))->id != END_OF_INPUT
			&& (((t_token *)(e->content))->id != LEX_TOK_SEMICOL)
			&& (((t_token *)(e->content))->id != LEX_TOK_AND))
				e = e->next;
		cmd = create_job_cmd(s, e);
		if (cmd == NULL)
			return (FAILURE);
		add_job_cmd(cmd);
		s = e->next;
	}
	return (SUCCESS);
	// jobs_print_cmds();
}
