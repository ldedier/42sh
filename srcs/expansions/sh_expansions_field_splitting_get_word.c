/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_field_splitting_get_word.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:13:34 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/17 19:20:29 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int 	sh_get_next_word_nws(t_split_data *data, t_split_word *word, int *i)
{
	int	is_quote;

	is_quote = 0;
	if (!sh_skip_ws_2(data, i))
		return (0);
	word->start = *i;
	if (!ft_strchr(data->nws, data->input[*i])
			|| (is_quote = t_quote_is_original_quote(*i, data->quotes) > 0))
	{
		word->start = *i;
		if (sh_skip_word_nws(data, word, i) < 0)
			return (-1);
	}
	else if (is_quote < 0)
		return (-1);
	else
	{
		word->end = *i;
		*i += 1;
	}
	return (1);
}
