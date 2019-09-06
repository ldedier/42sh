/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:29:18 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/14 19:17:54 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** t_token_update_id:
**	Update a token id by changing it's id, and looking for it's new index.
*/

void	t_token_update_id(int id, t_token *token)
{
	token->id = id;
	token->index = sh_index(id);
}

t_token	*t_token_new(int id, char *value)
{
	t_token		*token;

	if (!(token = malloc(sizeof(*token))))
		return (NULL);
	token->value = NULL;
	if (value)
	{
		if (!(token->value = ft_strdup(value)))
		{
			free(token);
			return (NULL);
		}
	}
	token->id = id;
	token->index = sh_index(id);
	token->ast_node = NULL;
	token->expansion = 0;
	token->apply_heredoc_expansion = 1;
	return (token);
}

/*
** t_token_free:
**	Free a t_token and it's value, if it had been filled.
*/

void	t_token_free(t_token *token)
{
	if (token->value)
		free(token->value);
	free(token);
}
