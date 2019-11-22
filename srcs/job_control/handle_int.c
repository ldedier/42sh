/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_no_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:40:13 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/04 11:46:30 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	handle_int(int signo)
{
	if (signo == SIGINT)
	{
		get_down_from_command(&g_glob.command_line);
		g_glob.command_line.interrupted = 1;
	}
}
