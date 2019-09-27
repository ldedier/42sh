/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_quote_removal.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 00:53:16 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/26 01:08:17 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void		sh_expansions_quote_removal(t_quote **quotes)
{
	int		i;

	if (sh_verbose_expansion())
	{
		ft_dprintf(2, "Quotes to delete :\n");
		t_quote_show_tab(quotes);
	}
	i = 0;
	while(quotes[i])
		i++;
	i--;
	while (i >= 0)
	{
		ft_strdelchar(quotes[i]->c, 0);
		i--;
	}
}

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

void		sh_expansions_quote_removal_in_str(char *input)
{
	int			i;

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
}