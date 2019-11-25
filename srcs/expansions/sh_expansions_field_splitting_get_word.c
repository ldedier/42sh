/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_field_splitting_get_word.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:13:34 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/25 10:59:18 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_get_next_word_nws(t_split_data *data, t_split_word *word, int *i)
{
	int	is_quote;

	is_quote = 0;
	if (!sh_skip_ws_2(data, i))
		return (0);
	word->start = *i;
	if (!ft_strchr(data->nws, data->input[*i])
			|| (is_quote = t_quote_is_original_quote(*i, data->quotes)) > 0)
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

static int	sh_skip_word_ws(t_split_data *data, t_split_word *word, int *i)
{
	int	is_quote;

	is_quote = 0;
	if (!data->input[*i] || ft_strchr(data->ws, data->input[*i]))
	{
		word->end = *i;
		if (data->input[*i])
		{
			data->input[*i] = 0;
			*i += 1;
		}
		return (0);
	}
	if ((*i = sh_skip_quote(data->quotes, *i)) < 0)
		return (-1);
	while (data->input[*i] && !ft_strchr(data->ws, data->input[*i])
			&& !(is_quote = t_quote_is_original_quote(*i, data->quotes)))
		*i += 1;
	if (is_quote < 0)
		return (-1);
	return (sh_skip_word_ws(data, word, i));
}

int			sh_get_next_word_ws(t_split_data *data, t_split_word *word, int *i)
{
	if (!sh_skip_ws_2(data, i))
		return (0);
	word->start = *i;
	if (data->input[*i])
	{
		if (sh_skip_word_ws(data, word, i) < 0)
			return (-1);
	}
	return (1);
}
