/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_field_splitting_quote_tools.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:01:27 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/21 09:08:36 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	update_quotes(t_quote **quotes, int i, int start, t_ast_node *node)
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

int		sh_skip_quote(t_quote **quotes, int i)
{
	int	is_quote;

	if ((is_quote = t_quote_is_original_quote(i, quotes)) < 0)
		return (-1);
	if (is_quote)
	{
		if ((is_quote = t_quote_get_offset(i, quotes)) < 0)
			return (-1);
		i = is_quote + 1;
	}
	return (i);
}
