/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_history.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 15:40:47 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/15 15:40:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_HISTORY_H
# define SH_HISTORY_H

#include "libft.h"

# define HISTORY_FILE			".history"
# define MAX_LEN_HISTORY_ENTRY	5000
# define HISTSIZE				32767

typedef struct		s_entry
{
	int				number;
	char			*command;
}					t_entry;

typedef struct      s_history
{
	t_dlist         *head;
	t_dlist         *commands;
	t_dlist         head_start;
	int             should_add : 1;
	int				start_index;
	int				nb_entries;
	int				from;
	int				to;
}					t_history;

/*
********************************************************************************
*/

#endif
