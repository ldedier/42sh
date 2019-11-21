/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 08:15:26 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/13 03:41:12 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	init_cycle(t_strsep *sep, char **original_start)
{
	sep->saved_start = original_start;
	sep->head = *original_start;
	sep->end = ft_strchr(*original_start, '\0');
	sep->save = '\0';
	return ;
}

static void	restore_previous_delimiter(t_strsep *sep)
{
	sep->head = ft_strchr(sep->head, '\0');
	if (sep->head && sep->head != sep->end)
	{
		*(sep->head) = sep->save;
		sep->save = '\0';
		sep->head += 1;
	}
}

static char	*finish_cycle(t_strsep *sep)
{
	if (sep->save)
		restore_previous_delimiter(sep);
	ft_bzero(sep, sizeof(*sep));
	return (NULL);
}

/*
** s_strsep:
**	Structure used for ft_strsep, decalre a static element to store infos.
**	- saved_start is used to check that we are still working on the same
**	string, in the same conditions, if original_start do not match it,
**	sep struc is reinitialized to start a new process from the begining.
**	- end store the original end of the string given, it determine when to
**	stop process.
**	-head : begining of the last delimited token, or of the string if it's the
**	first cycle. It can also contain sep.end, it means that it is last cycle.
**	-save : last delimiter char deleted, to be able to restore original string.
*/

/*
** ft_strsep:
**	ft_strsep, is trying to reproduce strsep function, but it restore original
**	string when you finished processing.
**	If you always force cycle to finish, by calling ft_strsep(NULL, NULL), when
**	processing a string, you won't need to initialize it.
**	original_sart is only asked to cehck that we are working on the same string
**	all process long. Delim contain characters that shall delimit two fields.
**	Ft_strsep returns start of the current token, or NULL if preocess is
**	finished.
**	If you abort processing (do not wait for function to return NULL), and you
**	want the original string to restore, just call ft_strsep(NULL, NULL).
**	WAARNING : not to follow instruction above may produce segfault, if you
**	call ft_strsep somewhere else, with null params, to reset it later.
*/

char		*ft_strsep(char **original_start, char *delim)
{
	static t_strsep	sep;
	char			*buffer;

	if (!original_start || !*original_start)
		return (finish_cycle(&sep));
	if (sep.saved_start != original_start)
		init_cycle(&sep, original_start);
	else if (sep.head && sep.head == sep.end)
		return (finish_cycle(&sep));
	if (sep.save)
		restore_previous_delimiter(&sep);
	if (!(buffer = ft_strpbrk(sep.head, delim)))
	{
		buffer = sep.head;
		sep.head = ft_strchr(sep.head, '\0');
		return (buffer);
	}
	sep.save = *buffer;
	*buffer = '\0';
	return (sep.head);
}
