/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_field_splitting_tools.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 14:22:54 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/23 11:38:22 by jdugoudr         ###   ########.fr       */
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

static int	sh_skip_ws(t_split_data *data, int i)
{
	while (data->input[i] && ft_strchr(data->ws, data->input[i]))
	{
		ft_strdelchar(data->input, i);
		decrease_quotes(data->quotes);
	}
	return (i);
}

int			start_nws_split(t_ast_node **node, t_split_data *data)
{
	int		i;
	int		is_quote;

	i = 0;
	(*node)->token->give_as_arg = 0;
	while (data->input[i]
			&& (ft_strchr(data->ws, data->input[i])
				|| ft_strchr(data->nws, data->input[i])))
	{
		sh_skip_ws(data, i);
		while (data->input[i] && ft_strchr(data->nws, data->input[i]))
		{
			if ((is_quote = t_quote_is_original_quote(i, data->quotes)) > 0)
				return (i);
			else if (is_quote < 0)
				return (-1);
			(*node)->token->give_as_arg = 1;
			if (split_input(node, data, i, i) != SUCCESS)
				return (-1);
			i++;
		}
	}
	if (i >= 1 || data->input[i])
		(*node)->token->give_as_arg = 1;
	return (i);
}

int			sh_skip_ws_2(t_split_data *data, int *i)
{
	int	is_quote;

	is_quote = 0;
	if (data->input[*i] == 0)
		return (0);
	while (data->input[*i] && ft_strchr(data->ws, data->input[*i]))
		*i += 1;
	if (!data->input[*i])
		return (0);
	if (ft_strchr(data->nws, data->input[*i])
			&& !(is_quote = t_quote_is_original_quote(*i, data->quotes)))
		if (data->skip_nws)
		{
			*i += 1;
			data->skip_nws = 0;
			return (sh_skip_ws_2(data, i));
		}
	if (is_quote < 0)
		return (-1);
	return (1);
}

int			split_input(
		t_ast_node **node, t_split_data *data, int start, int end)
{
	char	*str;

	if (data->not_first == 0)
	{
		data->not_first = 1;
		(*node)->token->value[end] = 0;
		return (SUCCESS);
	}
	if (!(str = ft_strndup(data->input + start, end - start)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_splitting_non_white_ifs (1)"));
	else if (!(*node = sh_add_word_to_ast(*node, str, g_glob.cfg)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_splitting_non_white_ifs (2)"));
	if (sh_verbose_expansion())
		ft_dprintf(2, "non white ifs : Added node : start : %d, i : %d\n",
				start, end);
	update_quotes(data->quotes, end, start, *node);
	if (sh_verbose_expansion())
		ft_dprintf(2, "non white ifs : Added node : %s\n", str);
	return (SUCCESS);
}
