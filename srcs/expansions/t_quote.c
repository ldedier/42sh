/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 21:49:08 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/26 20:12:21 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_quote		*t_quote_new(int index, char *c)
{
	t_quote		*new;

	if (!(new = malloc(sizeof(*new))))
		return (NULL);
	new->index = index;
	new->c = c;
	return (new);
}

int			t_quote_add_new(t_dy_tab *quotes, int index, char *c)
{
	t_quote	*new;

	if (!(new = t_quote_new(index, c)))
		return (FAILURE);
	if (ft_dy_tab_add_ptr(quotes, new))
		return (FAILURE);
	return (SUCCESS);
}

void		t_quote_show_tab(t_quote **quotes)
{
	size_t		i;

	i = 0;
	if (!quotes[i])
		return ;
	while (quotes[i])
	{
		ft_dprintf(2, "%d : %c || ", quotes[i]->index, *(quotes[i]->c));
		i++;
	}
	ft_dprintf(2, "\n");
	return ;
}

/*
** t_quote_is_original_quote:
**	Check if current index correspond for start of 
**
**	Returned Values :
**		-1 : Error occured
**		>= 0 : Index of the end of end quoting char
*/

int		t_quote_is_original_quote(int i, t_quote **quotes)
{
	int		j;

	j = 0;
	while (quotes[j] && quotes[j]->index <= i)
	{
		if (quotes[j]->index == i)
			return (1);
		j++;
	}
	return (0);
}

/*
** t_quote_get_offset:
**	if t_quote_is_original_quote return True, get_offset will look for
**	matching end quote and return it's index in input,
**	or index of escaped char if quoting char is a '\'.
**
**	Returned Values :
**		-1 : Error occured
**		>= 0 : Index of the end of end quoting char, or escaped char if '\'
*/

int		t_quote_get_offset(int i, t_quote **quotes)
{
	int		j;
	char	quoted;

	j = 0;
	while (quotes[j] && quotes[j]->index <= i)
	{
		if (quotes[j]->index == i)
			break ;
		j++;
	}
	if (!quotes[j] || !(quotes[j]->index == i))
		return (-1);
	quoted = *(quotes[j]->c);
	if (quoted == '\\')
		return (i + 1);
	j++;
	while (quotes[j] && *(quotes[j]->c) != quoted)
		j++;
	if (*(quotes[j]->c) == quoted)
		return (quotes[j]->index);
	return (-1);
}