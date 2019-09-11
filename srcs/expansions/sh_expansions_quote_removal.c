/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_quote_removal.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 00:53:16 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/11 07:07:33 by jmartel          ###   ########.fr       */
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
			(*i) += 1;
		(*i) += 1;
	}
	if (input[*i] == '"')
		ft_strdelchar(input, *i);
}

int			sh_expansions_quote_removal(t_context *context, char *input)
{
	int		i;

	i = 0;
	// ft_dprintf(2, "quote removal : %s||\n", input);
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
	// ft_dprintf(2, "quote removal (end) : %s||\n", input);
	return (SUCCESS);
	(void)context;
}
