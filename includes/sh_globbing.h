/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_globbing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 23:13:55 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/15 23:21:03 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_GLOBBING_H
# define SH_GLOBBING_H

typedef struct s_regexp		t_regexp;
typedef enum e_regexp_type	t_regexp_type;

enum					e_regexp_type
{
	REG_STR,
	REG_STAR,
	REG_CHAR,
};

struct					s_regexp
{
	t_regexp_type	type;
	int				start;
	int				len;
	char			*value;
};

/*
********************************************************************************
*/

/*
** sh_globbing.c
*/
int		fill_regexp(t_list **value, char *str);
int		sh_expansions_pattern_matching(
	t_context *context, t_ast_node *father);

/*
** t_regexp.c
*/

#endif
