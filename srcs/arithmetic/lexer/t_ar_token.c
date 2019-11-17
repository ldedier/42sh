/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ar_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 21:12:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/17 21:24:29 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

// t_token		*t_ar_token_new_link(int id, char *value)
// {
// 	t_token		*token;
// 	t_list		*link;

// 	if (!(token = ft_memalloc(sizeof(*token))))
// 		return (NULL);
// 	if (value && !(token->value = ft_strdup(value)))
// 	{
// 		free(token);
// 		return (NULL);
// 	}
// 	if (!(ft_lstnew(token, sizeof(token))))
// 	{
// 		free(token);
// 		free(value);
// 		return (NULL);
// 	}
// 	token->id = id;
// 	return (token);
// }

/*
** t_ar_token_free:
**	Free a t_token and it's value, if it had been filled.
*/

void	t_ar_token_free(t_token *token)
{
	if (token->value)
		ft_strdel(&token->value);
	free(token);
}

