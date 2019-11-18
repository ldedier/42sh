/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_field_splitting.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:47:32 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/18 11:43:57 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

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

static int	sh_splitting_non_white_ifs(
		t_ast_node *node, char *ifs, char *input, t_dy_tab *quotes)
{
	t_split_data	data;
	t_split_word 	word;
	int				i;
	int				ret;

	data.input = input;
	data.not_first = 0;
	data.skip_nws = 1;
	data.quotes = (t_quote **)quotes->tbl;
	if (sh_splitting_parse_ifs(data.ws, data.nws, ifs))
		return (ERROR);
	if (sh_verbose_expansion())
		ft_dprintf(2, "ifs : non white : %s && white : %s\n", data.nws, data.ws);
	if ((i = start_nws_split(&node, &data)) < 0)
		return (FAILURE);
	while (input[i])
	{
		if (sh_verbose_expansion())
			ft_dprintf(2, "non white ifs : running %d (%c)\n", i, input[i]);
		if ((ret = sh_get_next_word_nws(&data, &word, &i)) < 0)
			return (FAILURE);
		else if (ret == 1)
			if ((ret = split_input(&node, &data, word.start, word.end)) != SUCCESS)
				return (ret);
	}
	return (SUCCESS);
}

static int	sh_expansions_splitting_default(t_ast_node *node, t_dy_tab *quotes)
{
	t_split_data	data;
	t_split_word	word;
	int				i;
	int				ret;

	data.input = node->token->value;
	data.not_first = 0;
	data.skip_nws = 0;
	data.quotes = (t_quote **)quotes->tbl;
	data.ws[0] = '\n';
	data.ws[1] = '\t';
	data.ws[2] = ' ';
	data.ws[3] = '\0';
	data.nws[0] = 0;
	if (sh_verbose_expansion())
		ft_dprintf(2, RED"default IFS\n"EOC);
	if ((i = start_nws_split(&node, &data)) < 0)
		return (FAILURE);
	while (data.input[i])
	{
		if ((ret = sh_get_next_word_ws(&data, &word, &i)) < 0)
			return (FAILURE);
		else if (ret == 1)
			if ((ret = split_input(&node, &data, word.start, word.end)) != SUCCESS)
				return (ret);
	}
	return (SUCCESS);
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
	static int i = 0;

	i++;
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
		sh_print_ast_root(node);
	return (ret);
}
