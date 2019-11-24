/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 20:38:02 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/24 20:39:11 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	pid_t	ppid;
	int		signal;

	if (argc < 2)
		return (0);
	signal = atoi(argv[1]);
	ppid = getppid();
	kill(ppid, signal);
	(void)argc;
	(void)argv;
}
