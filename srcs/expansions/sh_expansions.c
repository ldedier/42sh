/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 10:59:30 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/26 08:46:35 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_expansions_return_value(
	int ret, t_dy_tab *quotes, t_context *context)
{
	if (ret == ERROR || ret == FAILURE)
		sh_env_update_ret_value(context->shell, ret);
	ft_dy_tab_del_ptr(quotes);
	if (ret)
		return (ret);
	return (SUCCESS);
}

static int	sh_expansions_call_tilde(
	t_context *context, t_ast_node *node, char **input, t_dy_tab *quotes)
{
	int		index;

	index = 0;
	if (node->token->id == LEX_TOK_ASSIGNMENT_WORD && ft_strchr(*input, '='))
		return (sh_expansions_tilde_assignment(input, context, quotes));
	else if ((*input)[0] == '~')
		return (sh_expansions_tilde(input, context, quotes, &index));
	return (SUCCESS);
}

/*
** sh_expansions:
**	Mother function of expansions process. Read the current token in context,
**	and perform various expansions on it. It first detect its category,
**	then perform it, and finally replace original value by result.
**	Checking lvalue is here to avoid performing expansions on token resulting
**	from globbing.
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

	if (!node || !node->token || !node->token->value || node->token->lval == -1)
		return (SUCCESS);
	index = 0;
	input = &node->token->value;
	if (!(quotes = ft_dy_tab_new(5)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions"));
	ret = sh_expansions_call_tilde(context, node, input, quotes);
	if (!ret)
		ret = sh_expansions_scan(input, index, context, quotes);
	if (!ret)
		ret = sh_expansions_splitting(context, node, quotes);
	if (!ret)
		ret = sh_expansions_globbing(node, quotes, 0);
	if (!ret)
		sh_expansions_quote_removal((t_quote**)quotes->tbl);
	return (sh_expansions_return_value(ret, quotes, context));
}
