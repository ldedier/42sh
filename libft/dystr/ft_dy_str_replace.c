/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dy_str_replace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 06:45:43 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/20 01:57:04 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_dy_str_replace(t_dy_str *dy_str, char *str)
{
	size_t		len;

	if (dy_str->str)
		ft_strdel(&(dy_str->str));
	if (!(dy_str->str = ft_strdup(str)))
		return (1);
	len = ft_strlen(str);
	dy_str->current_size = len;
	dy_str->max_size = len;
	return (0);
}
