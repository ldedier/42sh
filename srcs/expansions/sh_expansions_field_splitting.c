/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_field_splitting.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:47:32 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/11 07:07:59 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

// static int	sh_splitting_parse_ifs(char **ws, char **nws, char *ifs)
// {
// 	int		i;
// 	int		iws;
// 	int		inws;


// 	if (ft_strlen(ifs) > 99)
// 		return (ERROR);
// 	i = 0;
// 	iws = 0;
// 	inws = 0;
// 	while (ifs[i])
// 	{
// 		if (ft_iswhite(ifs[i]))
// 		{
// 			*ws[iws] = ifs[i];
// 			iws++;
// 		}
// 		else
// 		{
// 			*nws[inws] = ifs[i];
// 			inws++;
// 		}
// 		i++;
// 	}
// 	(*ws)[iws] = '\0';
// 	(*nws)[inws] = '\0';
// 	return (SUCCESS);
// }

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

// static int	sh_splitting_non_white_ifs(t_ast_node *node, t_context *context, char *ifs, char *input)
// {
// 	char	ws[100];
// 	char	nws[100];
// 	int		i;
// 	int		start;
// 	char	save; // does it can replace any deleted char by an element of ws.

// 	if (sh_splitting_parse_ifs((char**)&ws, (char**)&nws, ifs))
// 		return (SUCCESS);
// 	i = 0;
// 	while (input[i] && ft_strchr(ws, input[i]))
// 		i++;
// 	while (input[i])
// 	{
// 		if (ft_strchr(ws, input[i]))
// 		{
// 			while (input[i] && ft_strchr(ws, input[i]))
// 				i++;
// 			if (input[i] && ft_strchr(nws, input[i]))
// 				i++;
// 			while (input[i] && ft_strchr(ws, input[i]))
// 				i++;
// 		}
// 		start = i;
// 		while (input[i] && !ft_strchr(ws, input[i]) && !ft_strchr(nws, input[i]))
// 			i++;
// 		if (!input[i])
// 		{
// 			if (!sh_add_to_ast_node(node, node->symbol->id, input + start))
// 				return (FAILURE);
// 			break ;
// 		}
// 		save = input[i];
// 		input[i] = 0;
// 		if (!sh_add_to_ast_node(node, node->symbol->id, input + start))
// 			return (FAILURE);
// 		input[i] = save;
// 		i++;
// 	}
// 	return (SUCCESS);
// 	(void)context;
// }

// int			sh_expansions_splitting(t_ast_node *node, t_context *context)
// {
// 	char	*ifs;

// 	if (!node)
// 		return (SUCCESS); // node is null when called from heredocs
// 	ifs = sh_vars_get_value(context->env, context->vars, "IFS");
// 	if (!ifs || ft_strequ(ifs, " \t\n"))
// 	{
// 		if (!ft_strpbrk(node->token->value, " \t\n"))
// 			return (SUCCESS);
// 		return (sh_splitting_white_ifs(node, context));
// 	}
// 	else if (!*ifs)
// 		return (SUCCESS);
// 	else
// 	{
// 		if (!ft_strpbrk(node->token->value, ifs)) // Need to keep ??
// 			return (SUCCESS);
// 		return (sh_splitting_non_white_ifs(node, context, ifs, node->token->value));
// 	}
// 	return (SUCCESS); // usefull ?
// 	(void)node;
// 	(void)context;
// }

static void	field_splitting_pass_quotes(char *str, int *i)
{
	char		quote;

	if (str[*i] == '\\')
	{
		(*i) += 2;
		return ;
	}
	quote = str[*i];
	(*i) += 1;
	while (str[*i] && str[*i] != quote)
		(*i) += 1;
	(*i) += 1;
}



int			sh_expansions_splitting(t_context *context, t_ast_node *node)
{
	int			i;
	int			start;
	char		*input;
	const char	*ifs = "\n\t \0";
	const char	*quotes = "\"\'\\\0";
	t_ast_node	*original_node;

	if (!node)
		return (SUCCESS);  // node is null when called from heredocs
	if (!ft_strpbrk(node->token->value, ifs))
		return (SUCCESS);
	input = node->token->value;
	original_node = node;

	i = 0;
	start = -2;
	while (input[i])
	{
		// ft_dprintf(2, "%c : %s\n", input[i], input + i);
		if (ft_strchr(quotes, input[i]))
		{
			field_splitting_pass_quotes(input, &i);
			// ft_dprintf(2, "going threw quotes\n");
		}
		else if (ft_strchr(ifs, input[i]))
		{
			if (start == -2)
			{
				input[i] = 0;
				i++;
				start = -1;
				// ft_dprintf(2, "adding first node : %s|\n", input);
			}
			else
			{
				// ft_dprintf(2, "adding node : %s\n", ft_strndup(input + start, i - start));
				if (!(node = sh_add_word_to_ast(node, ft_strndup(input + start, i - start)))) //protect
					return (FAILURE);
			}
			while (input[i] && ft_strchr(ifs, input[i]))
				i++;
			start = i;
			// ft_dprintf(2, "new start : %d (%c)\n", i, input[i]);
			i--;
		}
		i++;
	}
	if (start >= 0)
	{
		// ft_dprintf(2, "adding last node : %s\n", ft_strndup(input + start, i - start));
		if (!(node = sh_add_word_to_ast(node, ft_strndup(input + start, i - start)))) //protect
			return (FAILURE);
	}
	// sh_print_token_list(context->shell->parser.tokens, &context->shell->parser.cfg);
	// sh_print_ast(node, 0);
	// sh_print_ast(context->shell->parser.ast_root, 0);
	return (SUCCESS);
	(void)context;
}
