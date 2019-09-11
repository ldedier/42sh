#include <stdio.h>

int	main(int argc, char **argv)
{
	printf("False\n");
	if (argc == 1)
		return (1);
	printf("%s\n", argv[1]);
	return (1);
}
