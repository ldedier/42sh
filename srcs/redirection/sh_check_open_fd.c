#include "sh_21.h"

int			sh_check_open_fd(t_redirection_type type, int fd)
{
	if (type == OUTPUT)
	{
		if (write(fd, "", 0) == 0)
			return (fd);
	}
	else
	{
		if (read(fd, "", 0) == 0)
			return (fd);
	}
	return (-1);
}