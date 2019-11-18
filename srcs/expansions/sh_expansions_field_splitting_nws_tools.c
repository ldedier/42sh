/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_field_splitting_nws_tools.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 18:57:14 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/18 09:51:58 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

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

static int 	sh_skip_ws(t_split_data *data, int i)
{
	while (data->input[i] && ft_strchr(data->ws, data->input[i]))
	{
		ft_strdelchar(data->input, i);
		decrease_quotes(data->quotes); // be carefull if used with IFS using quotes
	}
	return (i);
}

int	start_nws_split(t_ast_node **node, t_split_data *data)
{
	int		i;
	int		is_quote;

	i = 0;
	while (data->input[i]
			&& (ft_strchr(data->ws, data->input[i])
				|| ft_strchr(data->nws, data->input[i])))
	{
		sh_skip_ws(data, i);
		while (data->input[i] && ft_strchr(data->nws, data->input[i]))
		{
			(*node)->token->give_as_arg = 1;
			if ((is_quote = t_quote_is_original_quote(i, data->quotes)) > 0)
				return (i);
			else if (is_quote < 0)
				return (-1);
			if (split_input(node, data, i, i) != SUCCESS)
				return (-1);
			i++;
		}
	}
	return (i);
}

static int 	is_nws(t_split_data *data, int i)
{
	int	is_quote;

	is_quote = 0;
	if (!ft_strchr(data->nws, data->input[i]))
		return (0);
	if ((is_quote = t_quote_is_original_quote(i, data->quotes)) < 0)
		return (-1);
	if (is_quote)
		return (0);
	return (1);
}

int 	sh_skip_word_nws(t_split_data *data, t_split_word *word, int *i)
{
	int	is_quote;

	is_quote = 0;
	if (!data->input[*i] || ft_strchr(data->ws, data->input[*i])
			|| (is_quote = is_nws(data, *i) == 1))
	{
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
	if (is_quote < 0)
		return (-1);
	if ((*i = sh_skip_quote(data->quotes, *i)) < 0)
		return (-1);
	while (data->input[*i] && (is_quote = is_nws(data, *i) == 0) && !ft_strchr(data->ws, data->input[*i]))
		*i += 1;
	if (is_quote < 0)
		return (-1);
	return (sh_skip_word_nws(data, word, i));
}
