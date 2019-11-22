/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 14:47:59 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/22 11:55:56 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** t_token_node_new
**	Create a new t_list node containing a new token
*/

t_list	*t_token_node_new(int id, char *value, t_cfg *cfg)
{
	t_list		*link;
	t_token		*token;

	if (!(token = t_token_new(id, value, cfg)))
		return (NULL);
	if (!(link = ft_lstnew(token, sizeof(token))))
	{
		t_token_free(token);
		return (NULL);
	}
	return (link);
}

/*
** t_token_free_list
**	Free a t_token encpsuled in a t_list.
*/

void	t_token_free_list(t_list **head)
{
	t_list	*buf;

	while (*head)
	{
		buf = *head;
		*head = (*head)->next;
		t_token_free(buf->content);
		free(buf);
	}
}

/*
** sh_free_token_lst:
**		Function added to be used with ft_lst_del.
*/

void	sh_free_token_lst(void *t, size_t dummy)
{
	(void)dummy;
	t_token_free((t_token *)t);
}

/*
** sh_get_token_by_index:
**	Look in a token list if any token was, in original input,
**	at index sent.
**
**	Return Value:
**		NULL : No token correpond to index
**		Else : Address of token correspoding
*/

t_token	*sh_get_token_by_index(t_list *tokens, int index, t_list **prev)
{
	t_token		*token;
	t_list		*ptr;

	ptr = tokens;
	*prev = NULL;
	while (ptr)
	{
		token = (t_token *)(ptr->content);
		if (token->index_start <= index && token->index_end > index)
			return (token);
		else if (token->index_end > index)
			return (NULL);
		*prev = ptr;
		ptr = ptr->next;
	}
	return (NULL);
}
