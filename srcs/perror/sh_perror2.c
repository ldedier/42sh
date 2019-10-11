/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_perror2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:41:27 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/10 16:00:48 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_perror2(const char *error, const char *prefix, const char *suffix)
{
	if (isatty(2))
	{
		ft_dprintf(2, "%s%s: %s: %s: %s%s\n",
			SH_ERR_COLOR, SH_NAME, prefix, error, suffix, COLOR_END);
	}
	else
		ft_dprintf(2, "%s: %s: %s: %s\n", SH_NAME, prefix, error, suffix);
	return (FAILURE);
}

int		sh_perror2_err(
	const char *error, const char *prefix, const char *suffix)
{
	sh_perror2(error, prefix, suffix);
	return (ERROR);
}

void	*sh_perror2n(const char *error, const char *prefix, const char *suffix)
{
	sh_perror2(error, prefix, suffix);
	return (NULL);
}
