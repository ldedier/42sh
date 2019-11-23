/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_proc_subst_tools.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 11:08:16 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/22 11:08:27 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

char		*sh_get_fd_string(int fd)
{
	char *str;
	char *fd_str;

	if (!(fd_str = ft_itoa(fd)))
		return (sh_perrorn(SH_ERR1_MALLOC, "sh_get_fd_string"));
	if (!(str = ft_strjoin_free("/dev/fd/", fd_str, 2)))
		return (sh_perrorn(SH_ERR1_MALLOC, "sh_get_fd_string"));
	return (str);
}
