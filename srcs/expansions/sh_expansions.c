/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 10:59:30 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/20 11:49:36 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

//static int 	sh_save_non_var_form_splitting(char **input, int index)
//{
//	int 	quote[2];
//
//	quote[0] = index;
//	while ((*input)[index] != '\'' && (*input)[index] != '"'
//		&& (*input)[index] != '\\' && (*input)[index] != '$'
//		&& (*input)[index] != '<' && (*input)[index] != '>'
//		&& (*input)[index] != '`' && (*input)[index])
//		index++;
//	quote[1] = index;
//	if (quote[0] < quote[1] && ft_strninsert_free(input, quote, '\'', 2) < 0)
//			return (sh_perror(SH_ERR1_MALLOC, "sh_expansions"));
//	if ((*input)[index] == 0)
//		return (SUCCESS);
//	else if ()
//}

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
	if (node->token->id == LEX_TOK_ASSIGNMENT_WORD && ft_strchr(*input, '='))
		ret = sh_expansions_tilde_assignment(input, context, quotes);
	else if ((*input)[0] == '~')
		ret = sh_expansions_tilde(input, context, quotes, &ret);
	if (!ret)
		ret = sh_expansions_scan(input, index, context, quotes);
	if (sh_verbose_expansion() && (t_quote**)quotes->tbl[0])
		ft_dprintf(2, "input : %s\n", *input);
	if (!ret)
		ret = sh_expansions_splitting(context, node, quotes);
	if (!ret)
		ret = sh_expansions_globbing(node, quotes);
	if (!ret)
		sh_expansions_quote_removal((t_quote**)quotes->tbl);
	if (ret == ERROR || ret == FAILURE)
		sh_env_update_ret_value(context->shell, ret);
	ft_dy_tab_del_ptr(quotes);
	if (ret)
		return (ret);
	return (SUCCESS);
}
