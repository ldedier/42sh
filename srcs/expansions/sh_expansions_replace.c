/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_replace.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 14:59:23 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/19 19:39:37 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void		sh_expansions_update_quotes_pointer(char **input, t_quote **quotes)
{
	int	i;

	i = 0;
	while (quotes[i])
	{
		quotes[i]->c = (*input) + quotes[i]->index;
		i++;
	}
}

static void	sh_expansions_replace_update_quotes(
	t_expansion *exp, char *new, t_quote **quotes, int index)
{
	int		offset;
	int		i;

	offset = ft_strlen(exp->res->str) - ft_strlen(exp->original);
	i = 0;
	while (quotes[i])
	{
		if (quotes[i]->index > index)
			quotes[i]->index += offset;
		quotes[i]->c = new + quotes[i]->index;
		i++;
	}
	if (sh_verbose_expansion() && quotes[i])
	{
		ft_dprintf(2, YELLOW"expansions replace : updated quote table\n"EOC);
		t_quote_show_tab(quotes);
	}
}

int			sh_expansions_replace(
	t_expansion *exp, char **input, int index, t_quote **quotes)
{
	char	*new;

	new = ft_strrep(*input, exp->res->str, index, ft_strlen(exp->original));
	if (!(new))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_replace"));
	sh_expansions_replace_update_quotes(exp, new, quotes, index);
	free(*input);
	(*input) = new;
	if (sh_verbose_expansion())
	{
		t_expansion_show_type(exp);
		ft_dprintf(2, " expansion : %s", L_BLUE);
		ft_dprintf(2, "%s => %s\n", exp->original, exp->res->str);
		ft_dprintf(2, "new input : %s%s\n", *input, EOC);
	}
	return (SUCCESS);
}
