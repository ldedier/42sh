/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 17:13:39 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/03 21:36:16 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

char	*sh_color_depth(int i)
{
	if ((i % 5) == 0)
		return (CYAN);
	else if (i % 5 == 1)
		return (YELLOW);
	else if (i % 5 == 2)
		return (BLUE);
	else if (i % 5 == 3)
		return (GREEN);
	else
		return (MAGENTA);
}

void	sh_print_ast_child(int depth, int *j, t_cfg *cfg, t_ast_node *child)
{
	int k;
	int i;

	i = depth;
	k = 0;
	while (i--)
		ft_dprintf(2, "%s| "EOC, sh_color_depth(k++));
	ft_dprintf(2, "%sɸ %s%schild #%d:%s", sh_color_depth(k), EOC,
			sh_color_depth(k + 1), ++(*j), EOC);
	sh_print_ast(child, cfg, depth + 1);
}

void	sh_print_ast(t_ast_node *node, t_cfg *cfg, int depth)
{
	t_list	*ptr;
	int		j;

	if (!node)
	{
		ft_dprintf(2, "LEAF NODE");
		return ;
	}
	if (!node->token)
		sh_print_symbol(node->symbol, cfg);
	else
		sh_print_token(node->token, cfg);
	ft_dprintf(2, "\n");
	ptr = node->children;
	j = 0;
	while (ptr != NULL)
	{
		sh_print_ast_child(depth, &j, cfg, (t_ast_node *)ptr->content);
		ptr = ptr->next;
	}
}

void	sh_print_ast_root(t_ast_node *node, t_cfg *cfg)
{
	t_ast_node *root;

	if (!node)
		ft_printf("LEAF NODE\n");
	else
	{
		root = node;
		while (root->parent)
			root = root->parent;
		sh_print_ast(root, cfg, 0);
	}
}
