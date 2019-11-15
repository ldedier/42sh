/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_field_splitting.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:47:32 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/15 16:02:32 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	update_quotes(t_quote **quotes, int i, int start, t_ast_node *node)
{
	int		q;

	q = 0;
	while (quotes[q] && quotes[q]->index < start)
		q++;
	while (quotes[q] && quotes[q]->index < i)
	{
		quotes[q]->c = node->token->value + quotes[q]->index - start;
		quotes[q]->index = -1;
		q++;
	}
	return ;
}

static int	sh_splitting_parse_ifs(char *ws, char *nws, char *ifs)
{
	int		i;
	int		iws;
	int		inws;

	if (ft_strlen(ifs) > 99)
		return (sh_perror_err("IFS", "variable is too long"));
	i = 0;
	iws = 0;
	inws = 0;
	while (ifs[i])
	{
		if (ft_iswhite(ifs[i]))
		{
			ws[iws] = ifs[i];
			iws++;
		}
		else
		{
			nws[inws] = ifs[i];
			inws++;
		}
		i++;
	}
	ws[iws] = '\0';
	nws[inws] = '\0';
	return (SUCCESS);
}

static int	sh_splitting_non_white_ifs(t_ast_node *node, char *ifs, char *input, t_dy_tab *quotes)
{
	char		ws[100];
	char		nws[100];
	int			i;
	int			start;
	char		*str;
	int			first;

	if (sh_splitting_parse_ifs(ws, nws, ifs))
		return (ERROR);
	i = 0;
	if (sh_verbose_expansion())
		ft_dprintf(2, "ifs : non white : %s && white : %s\n", nws, ws);
	while (input[i] && ft_strchr(ws, input[i]))
		i++;
	start = i;
	first = 1;
	while (input[i])
	{
		if (sh_verbose_expansion())
			ft_dprintf(2, "non white ifs : running %d (%c)\n", i, input[i]);
		if (ft_strchr(nws, input[i]) || ft_strchr(ws, input[i]))
		{
			if (first)
			{
				input[i] = 0;
				first = 0;
				i++;
				start = i;
				if (sh_verbose_expansion())
					ft_dprintf(2, "non white ifs : Added first node : %s\n", input);
				continue ;
			}
			else
			{
				if (!(str = ft_strndup(input + start, i - start)))
					return (sh_perror(SH_ERR1_MALLOC, "sh_splitting_non_white_ifs (1)"));
				else if (!(node = sh_add_word_to_ast(node, str, g_glob.cfg)))
					return (sh_perror(SH_ERR1_MALLOC, "sh_splitting_non_white_ifs (2)"));
				update_quotes((t_quote**)quotes->tbl, i, start, node);
				if (sh_verbose_expansion())
					ft_dprintf(2, "non white ifs : Added node : start : %d, i : %d\n", start, i);
				i++;
				if (sh_verbose_expansion())
					ft_dprintf(2, "non white ifs : Added node : %s\n", str);
			}
			start = i;
			if (ft_strchr(ws, input[i]))
			{
				while (input[i] && ft_strchr(ws, input[i]))
					i++;
				// i--;
				start = i;
			}
		}
		else
			i++;
	}
	if (start != i)
	{
		if (!(str = ft_strndup(input + start, i - start)))
			return (sh_perror(SH_ERR1_MALLOC, "sh_splitting_non_white_ifs (1)"));
		else if (!(node = sh_add_word_to_ast(node, str, g_glob.cfg)))
			return (sh_perror(SH_ERR1_MALLOC, "sh_splitting_non_white_ifs (2)"));
		update_quotes((t_quote**)quotes->tbl, i, start, node);
		if (sh_verbose_expansion())
			ft_dprintf(2, "non white ifs : Added last node : %s\n", str);
	}
	return (SUCCESS);
}

static void	decrease_quotes(t_quote **tbl)
{
	int		i;

	i = 0;
	while (tbl[i])
	{
		tbl[i]->index--;
		tbl[i]->c--;
		i++;
	}
}

static int	sh_expansions_splitting_default(t_ast_node *node, t_dy_tab *quotes)
{
	int			i;
	int			start;
	char		*input;
	const char	*ifs = "\n\t \0";

	input = node->token->value;
	i = 0;
	start = -2;
	if (sh_verbose_expansion())
		ft_dprintf(2, RED"default IFS\n"EOC);
	while (input[i] && ft_strchr(ifs, input[i]))
	{
		ft_strdelchar(input, i);
		decrease_quotes((t_quote**)quotes->tbl); // be carefull if used with IFS using quotes
	}
	while (input[i])
	{
		if (t_quote_is_original_quote(i, (t_quote**)quotes->tbl))
		{
			if (sh_verbose_expansion())
				ft_dprintf(2, "going threw quotes\n");
			if (t_quote_get_offset(i, (t_quote**)quotes->tbl) != -1)
				i = t_quote_get_offset(i, (t_quote**)quotes->tbl);
		}
		else if (ft_strchr(ifs, input[i]))
		{
			if (start == -2)
			{
				input[i] = 0;
				i++;
				start = -1;
				if (sh_verbose_expansion())
					ft_dprintf(2, "adding first node : (%s)\n", input);
			}
			else
			{
				if (sh_verbose_expansion())
					ft_dprintf(2, "adding node : %s\n", node->token->value);
				if (!(node = sh_add_word_to_ast(node, ft_strndup(input + start, i - start), g_glob.cfg)))
					return (FAILURE);
				update_quotes((t_quote**)quotes->tbl, i, start, node);
			}
			while (input[i] && ft_strchr(ifs, input[i]))
				i++;
			start = i;
			if (sh_verbose_expansion())
				ft_dprintf(2, "new start : %d (%c)\n", i, input[i]);
			i--;
		}
		i++;
	}
	if (start != i && start >= 0)
	{
		if (!(node = sh_add_word_to_ast(node, ft_strndup(input + start, i - start), g_glob.cfg))) //protect
			return (FAILURE);
		if (sh_verbose_expansion())
			ft_dprintf(2, "adding last node : %s\n", node->token->value);
		update_quotes((t_quote**)quotes->tbl, i, start, node);
		if (sh_verbose_expansion())
			ft_dprintf(2, "last node added : start : %d, i : %d\n", start, i);
	}
	return (SUCCESS);
	(void)quotes;
}

/*
** sh_expansions_splitting:
**	Result of expansions might be spltted into different tokens under
**	certain conditions (unquoted, IFS set, ...).
**	This function only determine wich mode to apply, using IFS variable value.
**	First condition is here to avoid field splitting in heredocs (node is NULL).
**
**	Returned Values:
**		SUCCESS
**		ERROR : IFS is too long to be parsed
**		FAILURE : malloc error
*/

int			sh_expansions_splitting(t_context *context, t_ast_node *node, t_dy_tab *quotes)
{
	char	*ifs;
	int		ret;

	if (!node || node->token->id == LEX_TOK_ASSIGNMENT_WORD)
		return (SUCCESS); // node is null when called from heredocs
	ifs = sh_vars_get_value(context->env, context->vars, "IFS");
	if (!ifs || ft_strequ(ifs, " \t\n"))
	{
		if (!ft_strpbrk(node->token->value, " \t\n"))
			return (SUCCESS);
		ret = sh_expansions_splitting_default(node, quotes);
	}
	else if (!*ifs)
		return (SUCCESS);
	else
	{
		if (!ft_strpbrk(node->token->value, ifs)) // Need to keep ??
			return (SUCCESS);
		ret = sh_splitting_non_white_ifs(node, ifs, node->token->value, quotes);
	}
	if (sh_verbose_expansion())
		sh_print_ast_root(node, g_glob.cfg);
	return (ret);
}
