/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_field_splitting.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:47:32 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/02 17:04:18 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_splitting_parse_ifs(char **ws, char **nws, char *ifs)
{
	int		i;
	int		iws;
	int		inws;


	if (ft_strlen(ifs) > 99)
		return (ERROR);
	i = 0;
	iws = 0;
	inws = 0;
	while (ifs[i])
	{
		if (ft_iswhite(ifs[i]))
		{
			*ws[iws] = ifs[i];
			iws++;
		}
		else
		{
			*nws[inws] = ifs[i];
			inws++;
		}
		i++;
	}
	(*ws)[iws] = '\0';
	(*nws)[inws] = '\0';
	return (SUCCESS);
}

// static int	sh_splitting_white_ifs(t_ast_node *node, t_context *context)
// {
// 	const char	ifs[] = " \t\n";
// 	char		*input;
// 	int			i;
// 	int			start;

// 	i = 0;
// 	input = node->token->value;
// 	while (input[i])
// 	{
// 		while (input[i] && ft_strchr(ifs, input[i]))
// 			i++;
// 		start = i;
// 		while (input[i] && !ft_strchr(ifs, input[i]))
// 			i++;
// 		if (start == i) // To try : ignore empty tokens
// 			continue ; // To try
// 		if (!input[i])
// 		{
// 			if (!sh_add_to_ast_node(node, node->symbol->id, input + start))
// 				return (FAILURE);
// 			ft_dprintf(1, "splitted (last) : %s\n", input + start);
// 			break ;
// 		}
// 		input[i] = '\0';
// 		ft_dprintf(1, "splitted : %s\n", input + start);
// 		if (!sh_add_to_ast_node(node, node->symbol->id, input + start))
// 			return (FAILURE);
// 		input[i] = ' ';
// 		i++;
// 	}
// 	sh_print_token_list(context->shell->parser.tokens, &context->shell->parser.cfg);
// 	return (SUCCESS);
// 	(void)context;
// }

static int	sh_splitting_white_ifs(t_ast_node *node, t_context *context)
{
	const char	ifs[] = " \t\n";
	char		*input;
	int			i;
	int			start;

	i = 0;
	input = node->token->value;
	while (input[i])
	{
		while (input[i] && ft_strchr(ifs, input[i]))
			i++;
		start = i;
		while (input[i] && !ft_strchr(ifs, input[i]))
			i++;
		if (start == i) // To try : ignore empty tokens
			continue ; // To try
		if (!input[i])
		{
			if (!sh_add_to_ast_node(node, LEX_TOK_WORD, input + start))
				return (FAILURE);
			ft_dprintf(1, "splitted (last) : %s\n", input + start);
			break ;
		}
		input[i] = '\0';
		ft_dprintf(1, "splitted : %s\n", input + start);
		if (!sh_add_to_ast_node(node, LEX_TOK_WORD, input + start))
			return (FAILURE);
		input[i] = ' ';
		i++;
	}
	sh_print_token_list(context->shell->parser.tokens, &context->shell->parser.cfg);
//	sh_print_ast(node, 0);
	sh_print_ast(context->shell->parser.ast_root, 0);
	return (SUCCESS);
	(void)context;
}
static int	sh_splitting_non_white_ifs(t_ast_node *node, t_context *context, char *ifs, char *input)
{
	char	ws[100];
	char	nws[100];
	int		i;
	int		start;
	char	save; // does it can replace any deleted char by an element of ws.

	if (sh_splitting_parse_ifs((char**)&ws, (char**)&nws, ifs))
		return (SUCCESS);
	i = 0;
	while (input[i] && ft_strchr(ws, input[i]))
		i++;
	while (input[i])
	{
		if (ft_strchr(ws, input[i]))
		{
			while (input[i] && ft_strchr(ws, input[i]))
				i++;
			if (input[i] && ft_strchr(nws, input[i]))
				i++;
			while (input[i] && ft_strchr(ws, input[i]))
				i++;
		}
		start = i;
		while (input[i] && !ft_strchr(ws, input[i]) && !ft_strchr(nws, input[i]))
			i++;
		if (!input[i])
		{
			if (!sh_add_to_ast_node(node, node->symbol->id, input + start))
				return (FAILURE);
			break ;
		}
		save = input[i];
		input[i] = 0;
		if (!sh_add_to_ast_node(node, node->symbol->id, input + start))
			return (FAILURE);
		input[i] = save;
		i++;
	}
	return (SUCCESS);
	(void)context;
}

int			sh_expansions_splitting(t_ast_node *node, t_context *context)
{
	char	*ifs;

	ifs = sh_vars_get_value(context->env, context->vars, "IFS");
	if (!ifs || ft_strequ(ifs, " \t\n"))
	{
		if (!ft_strpbrk(node->token->value, " \t\n"))
			return (SUCCESS);
		return (sh_splitting_white_ifs(node, context));
	}
	else if (!*ifs)
		return (SUCCESS);
	else
	{
		if (!ft_strpbrk(node->token->value, ifs)) // Need to keep ??
			return (SUCCESS);
		return (sh_splitting_non_white_ifs(node, context, ifs, node->token->value));
	}
	return (SUCCESS); // usefull ?
	(void)node;
	(void)context;
}
