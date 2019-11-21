/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tab_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:12:55 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/21 11:12:56 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Dummy function to print a **array (like argv)
** To be deleted or added to the libft
*/

void			str_tab_print(char **char_tab)
{
	int	i;

	if (char_tab == NULL)
		return ;
	i = 0;
	while (char_tab[i])
	{
		ft_printf("%s ", char_tab[i]);
		i++;
	}
}
