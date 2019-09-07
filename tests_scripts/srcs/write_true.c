#include <stdio.h>

int	main(int argc, char **argv)
{
	printf("True\n");
	if (argc == 1)
		return (0);
	printf("%s\n", argv[1]);
	return (0);
}
