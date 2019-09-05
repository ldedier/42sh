#include <stdio.h>
#include <stdlib.h>

int		main(int argc, char **argv)
{
	int		fd;
	char	*str;

	if (argc > 1)
		fd = atoi(argv[1]);
	else
		fd = 0;
	if (argc > 2)
		str = argv[2];
	else
		str = "Okalmos speculos";
	dprintf(fd, "%s\n", str);
	return (0);
}
