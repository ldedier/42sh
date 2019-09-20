/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 01:19:07 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/20 02:18:31 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void		child_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("CHILD RECEIVED SIGINT\n");
	}
}

int	parent_pid = 0;

int main(int argc, char * argv[]){

	pid_t	cpid;
	pid_t	pid;
	int		parent_gid;
	int		parent_pid;
	int		tty_fd;
	int		res;

	cpid = fork();

	// tty_fd = open("/dev/tty", O_RDWR);
	tty_fd = 0;
	printf("tty_fd: %d\n", tty_fd);
	if (parent_pid == 0)
		parent_pid = getpid();
	setpgid(parent_pid, parent_pid);
	if (cpid == 0)
	{
	/* CHILD */
		signal(SIGINT, child_handler);
		// set process group to itself
		pid = getpid();
		setpgid(pid, pid);
		printf("CHILD:->\tpid: %d, ppid: %d, pgid: %d\n", pid, getppid(), getpgid(pid));
		printf("CHILD->\tCONTROLLING PROCESS GROUP %d\n", tcgetpgrp(tty_fd));
		sleep(3);
		printf("CHILD DONE\n");
		// if ((tcsetpgrp(tty_fd, getppid())) < 0)
		// 	printf("tcsetpgrp failed\n");
		// exit(0);
	}
	else if (cpid > 0){
		/* PARRENT */

		//set the proccess group of child
		setpgid(cpid, cpid);
		if ((tcsetpgrp(tty_fd, cpid)) < 0)
			printf("tcsetpgrp failed\n");
		wait(&res);
		printf("PARENT:->\tpid: %d, pgid: %d\n", getpid(), getpgid(getpid()));
		if ((tcsetpgrp(tty_fd, getpid())) < 0)
			printf("tcsetpgrp failed\n");
		printf("PARENT->\tCONTROLLING PROCESS GROUP %d\n", tcgetpgrp(0));
		//Parent loops forever
		// while(1);
		printf("PARENT DONE\n");
	}
	else
	{
		perror("fork");
		_exit(1);
	}
	return (0);
}