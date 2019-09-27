/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 10:59:30 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/26 03:05:53 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_expansions:
**	Mother function of expansions process. Read the current token in context,
**	and perform various expansions on it. It first detect its category,
**	then perform it, and finally replace original value by result.
**
**	Returned Values:
**		FAILURE : malloc error
**		ERROR : bad expansion detected
**		STOP_CMD_LINE : ${?} or ${:?} returned an error => stop current line
**		SUCCESS : expansion successfuly replaced in
*/

int			sh_expansions(t_context *context, t_ast_node *node)
{
	char		**input;
	int			ret;
	int			index;
	t_dy_tab	*quotes;

	if (!node || !node->token || !node->token->value)
		return (SUCCESS);
	index = 0;
	input = &node->token->value;
	ret = SUCCESS;
	if (!(quotes = ft_dy_tab_new(5)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions"));
	if ((*input)[0] == '~')
		ret = sh_expansions_tilde(input, *input, context, quotes);
	if (!ret)
		ret = sh_expansions_scan(input, index, context, quotes);
	if (sh_verbose_expansion())
	{
		ft_dprintf(2, "input : %s\n", *input);
		t_quote_show_tab((t_quote**)quotes->tbl);
	}
	if (sh_verbose_expansion())
		t_quote_show_tab((t_quote**)quotes->tbl);
	if (!ret)
		ret = sh_expansions_splitting(context, node, quotes);
	if (!ret)
		sh_expansions_quote_removal((t_quote**)quotes->tbl);
	if (ret == ERROR || ret == FAILURE)
		sh_env_update_ret_value(context->shell, ret);
	if (sh_env_update_question_mark(context->shell) == FAILURE)
		return (FAILURE);
	ft_dy_tab_del(quotes); // leaks in error cases
	if (ret)
		return (ret);
	return (SUCCESS);
}
