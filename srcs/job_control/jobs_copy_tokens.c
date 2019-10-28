/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_copy_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:53:10 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/26 12:23:29 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void		jobs_copy_tokens(t_list *tokens)
{
	t_list	*it;
	t_list	*node;

	// sh_print_token_list(tokens, g_glob.cfg);
	if (!g_job_ctrl->interactive)
		return ;
	it = tokens;
	while (it != NULL)
	{
			node = ft_lstnew_value(it->content, sizeof(t_token));
			// ((t_token *)node->content)->ast_node = NULL;
			ft_lstadd_last(&(g_job_ctrl->tokens),node);
		it = it->next;
	}
}