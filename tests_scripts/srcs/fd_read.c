#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int		main(int argc, char **argv)
{
	int		fd;
	char	buf;
	int		ret;

	if (argc > 1)
		fd = atoi(argv[1]);
	else
		fd = 1;
	while ((ret = read(fd, &buf, 1)))
	{
		if (ret == -1)
		{
			dprintf(1, "Read error\n");
			return (1);
		}
		dprintf(1, "%c", buf);
	}
	return (0);
}
