/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 08:15:26 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/12 08:21:49 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*init_variables(char **stored_start, char **stored_end)
{
	*stored_start = NULL;
	*stored_end = NULL;
	return (NULL);
}

/*
** ft_strsep:
**	Function used to parse a string, using a delimitor. The aim is to have
**	after all string, same string as it was when started.
**	Function take all the time address of the original start, to compare it
**	with the one it have in memory. If it is different it start a new process
**	from the begining.
**	Else, if it modified somethin it restore it, then it look for the next
**	delimiter char, or to the end, change it to a '\0', and return address
**	of the begining of this new token.
**	You shall run ft_strsep until it returns NULL in every cases, if you want
**	to retrieve the original string.
**
**	Returned Values
**		NULL : reached the end of the string, or reseted stored variables
**		Else : address of the begining of the new token
*/

char		*ft_strsep(char **original_start, char delim)
{
	static char		*stored_start = NULL;
	static char		*stored_end = NULL;
	static char		*head = NULL;
	char			*end;

	if (!original_start || !*original_start)
		return (init_variables(&stored_start, &stored_end));
	if (*original_start != stored_start)
	{
		stored_start = *original_start;
		head = stored_start;
		stored_end = ft_strchr(stored_start, '\0');
		if ((end = ft_strchr(head, delim)))
			*end = '\0';
		return (head);
	}
	if ((head = ft_strchr(head, '\0')) == stored_end)
		return (init_variables(&stored_start, &stored_end));
	*head = delim;
	head += 1;
	if ((end = ft_strchr(head, delim)))
		*end = '\0';
	return (head);
}
