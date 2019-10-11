/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:41:27 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/10 16:00:39 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_perror(const char *error, const char *suffix)
{
	if (isatty(2))
	{
		if (suffix)
			ft_dprintf(2, "%s%s: %s: %s%s\n", SH_ERR_COLOR,
				SH_NAME, error, suffix, COLOR_END);
		else
			ft_dprintf(2, "%s%s: %s%s\n", SH_ERR_COLOR,
				SH_NAME, error, COLOR_END);
	}
	else
	{
		if (suffix)
			ft_dprintf(2, "%s: %s: %s\n", SH_NAME, error, suffix);
		else
			ft_dprintf(2, "%s: %s\n", SH_NAME, error);
	}
	return (FAILURE);
}

int		sh_perror_err(const char *error, const char *suffix)
{
	sh_perror(error, suffix);
	return (ERROR);
}

void	*sh_perrorn(const char *error, const char *suffix)
{
	sh_perror(error, suffix);
	return (NULL);
}
