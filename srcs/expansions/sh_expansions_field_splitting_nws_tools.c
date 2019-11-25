/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_field_splitting_nws_tools.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 18:57:14 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/25 10:59:54 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	is_nws(t_split_data *data, int i)
{
	int	is_quote;

	if (!ft_strchr(data->nws, data->input[i]))
		return (0);
	if ((is_quote = t_quote_is_original_quote(i, data->quotes)) < 0)
		return (-1);
	if (is_quote)
		return (0);
	return (1);
}

static int	end_of_word(t_split_data *data, t_split_word *word, int *i)
{
	int	is_quote;

	word->end = *i;
	if (data->input[*i])
	{
		data->skip_nws = 1;
		if ((is_quote = is_nws(data, *i)) < 0)
			return (-1);
		else if (is_quote)
			data->skip_nws = 0;
		data->input[*i] = 0;
		*i += 1;
	}
	return (0);
}

int			sh_skip_word_nws(t_split_data *data, t_split_word *word, int *i)
{
	int	is_quote;

	is_quote = 0;
	if (!data->input[*i] || ft_strchr(data->ws, data->input[*i])
			|| (is_quote = is_nws(data, *i)) == 1)
		return (end_of_word(data, word, i));
	if (is_quote < 0)
		return (-1);
	if ((*i = sh_skip_quote(data->quotes, *i)) < 0)
		return (-1);
	while (data->input[*i] && !(is_quote = is_nws(data, *i))
			&& !ft_strchr(data->ws, data->input[*i])
			&& (is_quote = t_quote_is_original_quote(*i, data->quotes) == 0))
		*i += 1;
	if (is_quote < 0)
		return (-1);
	return (sh_skip_word_nws(data, word, i));
}
