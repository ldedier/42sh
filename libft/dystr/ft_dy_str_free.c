/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dy_str_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 15:12:03 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/14 15:12:06 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dy_str_free(t_dy_str **dy_str)
{
	free((*dy_str)->str);
	free(*dy_str);
	*dy_str = NULL;

}
