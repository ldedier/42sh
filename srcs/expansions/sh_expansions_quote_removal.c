/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_quote_removal.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 00:53:16 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/13 23:28:46 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	remove_simple_quote(char *input, int *i)
{
	ft_strdelchar(input, *i);
	while (input[*i] && input[*i] != '\'')
		(*i) += 1;
	if (input[*i] == '\'')
		ft_strdelchar(input, *i);
}

static void	remove_double_quote(char *input, int *i)
{
	ft_strdelchar(input, *i);
	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '\\')
			ft_strdelchar(input, *i);
		(*i) += 1;
	}
	if (input[*i] == '"')
		ft_strdelchar(input, *i);
}

int			sh_expansions_quote_removal(t_context *context, t_ast_node *node)
{
	int			i;
	char		*input;

	input = node->token->value;
	i = 0;
	if (sh_verbose_expansion())
		ft_dprintf(2, "quote removal : %s||\n", input);
	while (input[i])
	{
		if (input[i] == '\'')
			remove_simple_quote(input, &i);
		else if (input[i] == '\"')
			remove_double_quote(input, &i);
		else if (input[i] == '\\')
		{
			ft_strdelchar(input, i);
			i++;
		}
		else
			i++;
	}
	if (sh_verbose_expansion())
		ft_dprintf(2, "quote removal (end) : %s||\n", input);
	return (SUCCESS);
	(void)context;
}
