/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_perror_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:18:33 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/11 14:20:13 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_perror2_fd(
	int fd, const char *error, const char *prefix, const char *suffix)
{
	ft_dprintf(fd, "%s%s: %s: %s: %s%s\n",
		SH_ERR_COLOR, SH_NAME, prefix, error, suffix, COLOR_END);
	return (FAILURE);
}

int		sh_perror_fd(int fd, const char *error, const char *suffix)
{
	if (suffix && *suffix)
		ft_dprintf(fd, "%s%s: %s: %s%s\n", SH_ERR_COLOR,
			SH_NAME, error, suffix, COLOR_END);
	else
		ft_dprintf(fd, "%s%s: %s%s\n", SH_ERR_COLOR, SH_NAME, error, COLOR_END);
	return (FAILURE);
}
