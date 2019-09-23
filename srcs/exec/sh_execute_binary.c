/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_binary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 11:14:49 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/09 18:46:10 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

void		sh_execute_binary(t_context *context)
{
	// reset signals AFTER tcsetpgrp
	ft_dprintf(g_job_ctrl->term_fd, "Executing \"%s\"\t\tpid: %d, pgid: %d\n",
		context->path, getpid(), getpgid(getpid()));
	execve(context->path, (char **)context->params->tbl,
			(char **)context->env->tbl);
	exit(SUCCESS);
}