/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 10:59:30 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/05 04:04:32 by jmartel          ###   ########.fr       */
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
	if (node->token->id == LEX_TOK_ASSIGNMENT_WORD)
		ret = sh_expansions_tilde_assignment(input, context, quotes);
	else if (sh_expansions_variable_valid_name(*input) && ft_strchr(*input, '='))
		ret = sh_expansions_tilde_assignment(input, context, quotes);
	else if ((*input)[0] == '~')
		ret = sh_expansions_tilde(input, context, quotes, &ret);
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
	ft_dy_tab_del_ptr(quotes);
	if (ret)
		return (ret);
	return (SUCCESS);
}
