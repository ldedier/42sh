/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 16:05:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/30 20:19:15 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sys/signal.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void			reset_signals(void)
{
	int i;

	// ft_dprintf(g_term_fd, "SIGNAL RESET\n");
	i = 1;
	while (i <= 31)
		signal(i++, SIG_DFL);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
}

void			handler_sighup(int signo)
{
	if (signo == SIGHUP)
	{
		jobs_terminate();
		sh_post_execution();
		exit(128 + SIGHUP);
	}
}

void			init_signals(void)
{
	int i;

	i = 1;
	while (i <= 31)
		signal(i++, SIG_DFL);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGHUP, handler_sighup);
}
