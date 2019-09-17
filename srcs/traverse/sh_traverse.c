/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 21:45:25 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/17 01:39:02 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "job_control.h"

static int	init_jobs(void)
{
	g_job_control->first_job = NULL;	//free old first_job
	g_job_control->current_job = NULL;	//free old first_job
	g_job_control->job_count = 1;
}

int			sh_process_traverse(t_shell *shell)
{
	t_context	context;
	int			ret;

	if (t_context_init(&context, shell) == FAILURE)
		return (FAILURE);
	if (init_jobs() == FAILURE)
		return (FAILURE);
	context.phase = E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS;
	if ((ret = g_grammar[shell->parser.ast_root->symbol->id].
		traverse(shell->parser.ast_root, &context)))
	{
		ft_dy_tab_del(context.params);
		return (ret);
	}
	context.phase = E_TRAVERSE_PHASE_EXPANSIONS;
	ret = g_grammar[shell->parser.ast_root->symbol->id].
		traverse(shell->parser.ast_root, &context);
	t_context_free_content(&context);
	return (ret);
}
