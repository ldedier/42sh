/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitting_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 15:38:10 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/10 05:32:09 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static t_ast_node	*sh_add_word_to_ast_first(t_ast_node *parent,
		t_ast_node **to_add)
{
	if (ft_lstaddnew_ptr(&parent->children, *to_add,
		sizeof(t_ast_node *)))
	{
		sh_free_ast_node(to_add, 0);
		return (sh_perrorn(SH_ERR1_MALLOC, "sh_add_word_to_ast_first"));
	}
	return (*to_add);
}

static int			sh_process_add_new_ast_node(t_list *ptr,
			t_ast_node *previous_word, t_ast_node **new_node)
{
	t_ast_node	*node_ptr;
	t_list		*new_ptr;

	node_ptr = ptr->content;
	if (node_ptr == previous_word)
	{
		if (!(new_ptr = ft_lstnew(*new_node, sizeof(t_ast_node *))))
		{
			sh_free_ast_node(new_node, 0);
			*new_node = NULL;
			return (1);
		}
		new_ptr->next = ptr->next;
		ptr->next = new_ptr;
		(*new_node)->parent = previous_word->parent;
		return (1);
	}
	return (0);
}

/*
** add a new ast node of token LEX_TOK_WORD of value 'value' after
** the ast_node 'previous word' in the list of children of ast_node 'parent'
**
** returns the newly created node or NULL on errors
*/

t_ast_node			*sh_add_word_to_ast(t_ast_node *previous_word, char *value)
{
	t_list		*ptr;
	t_ast_node	*new_node;
	int			ret;

	ptr = previous_word->parent->children;
	if (!(new_node = sh_new_ast_node(LEX_TOK_WORD, value)))
	{
		free(value);
		return (NULL);
	}
	if (previous_word == NULL)
		return (sh_add_word_to_ast_first(previous_word->parent, &new_node));
	while (ptr != NULL)
	{
		if ((ret = sh_process_add_new_ast_node(ptr, previous_word, &new_node)))
			return (new_node);
		ptr = ptr->next;
	}
	free(value);
	return (NULL);
}


static void		sh_process_delete_node_from_parent(t_ast_node *parent,
		t_list *prev, t_list *ptr)
{
	if (prev == NULL)
	{
		parent->children = parent->children->next;
		sh_free_ast_node((t_ast_node **)&ptr->content, 0);
		free(ptr);
	}
	else
	{
		sh_free_ast_node((t_ast_node **)&ptr->content, 0);
		prev->next = ptr->next;
		free(ptr);
	}
}

/*
** delete the ast_node 'node' in the list of children of ast_node 'parent'
*/

void			sh_delete_node_from_parent(t_ast_node *node)
{
	t_list *ptr;
	t_list *prev;

	prev = NULL;
	ptr = node->parent->children;
	while (ptr != NULL)
	{
		if (node == ptr->content)
		{
			sh_process_delete_node_from_parent(node->parent, prev, ptr);
			return ;
		}
		prev = ptr;
		ptr = ptr->next;
	}
}
