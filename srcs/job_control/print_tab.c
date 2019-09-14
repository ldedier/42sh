/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 01:20:44 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/14 01:24:01 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Dummy function to print a **array (like argv)
** To be deleted or added to the libft
*/

void			print_tab(char **char_tab)
{
	int	i;

	i = 0;
	while (char_tab[i])
	{
		ft_printf("%s ", char_tab[i]);
		i++;
	}
	ft_printf("\n");
}