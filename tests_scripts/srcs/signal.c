#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	pid_t	ppid;
	int	signal;

	if (argc < 2)
		return (0);
	signal = atoi(argv[1]);
	ppid = getppid();
	kill(ppid, signal);
	(void)argc;
	(void)argv;
}
