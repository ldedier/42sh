/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:29:18 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/15 15:58:39 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** t_token_update_id:
**	Update a token id by changing it's id, and looking for it's new index.
*/

void	t_token_update_id(int id, t_token *token, t_cfg *cfg)
{
	token->id = id;
	token->index = cfg->index_func(id);
}

t_token	*t_token_new_ptr(int id, char *value, t_cfg *cfg)
{
	t_token		*token;

	if (!(token = malloc(sizeof(*token))))
		return (NULL);
	token->value = NULL;
	if (value)
		token->value = value;
	token->id = id;
	token->index = cfg->index_func(id);
	token->ast_node = NULL;
	token->expansion = 0;
	token->apply_heredoc_expansion = 1;
	return (token);
}

t_token	*t_token_new(int id, char *value, t_cfg *cfg)
{
	t_token		*token;

	if (!(token = ft_memalloc(sizeof(*token))))
		return (NULL);
	if (value)
	{
		if (!(token->value = ft_strdup(value)))
		{
			free(token);
			return (NULL);
		}
	}
	token->id = id;
	token->index = cfg->index_func(id);
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
		ft_strdel(&token->value);
	free(token);
}
