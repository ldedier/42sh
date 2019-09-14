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

void		sh_execute_binary(t_context *context)
{
	reset_signals();
	execve(context->path, (char **)context->params->tbl,
			(char **)context->env->tbl);
	sh_perror(((char**)context->params->tbl)[0], SH_ERR1_EXECVE_FAIL);
	exit(SH_RET_NOT_EXECUTABLE);
}