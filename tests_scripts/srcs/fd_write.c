/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 20:37:59 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/24 20:37:59 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
