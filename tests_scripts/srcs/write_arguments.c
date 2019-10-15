/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 22:26:28 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/14 22:29:26 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		main(int argc, char **argv)
{
	if (argc == 1)
		return (1);
	argv++;
	while (*argv)
	{
		printf("%s@", *argv);
		argv++;
	}
	printf("\n");
	return (0);
}
