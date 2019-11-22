/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_scan_double_quote.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:02:16 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/22 12:56:09 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	scan_quote_loop(
		char **input, t_context *context, t_dy_tab *quotes, int *index)
{
	int	ret;

	while ((*input)[*index] && (*input)[*index] != '\"')
	{
		if ((*input)[*index] == '$')
		{
			if ((ret = sh_expansions_process(input, context, index, quotes)))
				return (ret);
		}
		else if ((*input)[*index] == '\\'
				&& ft_strchr("$`\"\\", (*input)[*index + 1]))
		{
			if (t_quote_add_new(quotes, *index, (*input) + *index, 1))
				return (sh_perror(SH_ERR1_MALLOC, "double_quote"));
			(*index) += 2;
		}
		else if ((*input)[*index] == '\\' && (*input)[*index + 1] == '\n')
			ft_strdelchars((*input) + *index, 0, 2);
		else
			*index += 1;
	}
	return (SUCCESS);
}

int			sh_expansions_scan_double_quote(
		char **input, int *index, t_context *context, t_dy_tab *quotes)
{
	int	ret;

	if (t_quote_add_new(quotes, *index, (*input) + *index, 1))
		return (sh_perror(SH_ERR1_MALLOC, "double_quote"));
	*index += 1;
	if ((ret = scan_quote_loop(input, context, quotes, index)) != SUCCESS)
		return (ret);
	if (!(*input)[*index])
		return (ERROR);
	if (t_quote_add_new(quotes, *index, (*input) + *index, 1))
		return (sh_perror(SH_ERR1_MALLOC, "double_quote"));
	*index += 1;
	return (SUCCESS);
}
