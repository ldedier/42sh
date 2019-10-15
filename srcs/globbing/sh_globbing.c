/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_globbing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:31:28 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/15 23:19:56 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			fill_regexp(t_list **value, char *str)
{

	return (SUCCESS);
	(void)value;
	(void)str;
}

/*
** pattern matching (globing) : *, ?, [], !, intervals with '-'
*/

int			sh_expansions_pattern_matching(t_context *context, t_ast_node *father)
{
	t_list		*head;
	t_ast_node	*child;
	char		*str;
	t_list		*matches;

	head = father->children;
	while (head)
	{
		child = (t_ast_node*)head->content;
		str = child->token->value;
		matches = NULL;
		ft_printf("value: %s\n", str);
		head = head->next;
	}
	(void)context;
	(void)child;
	return (SUCCESS);
}
