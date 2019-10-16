/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_globbing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 23:13:55 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/16 07:29:23 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_GLOBBING_H
# define SH_GLOBBING_H

typedef struct s_regexp		t_regexp;
typedef enum e_regexp_type	t_regexp_type;

enum						e_regexp_type
{
	REG_STR,
	REG_STAR,
	REG_QUEST,
	REG_BRACE
};

struct						s_regexp
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
int							sh_expansions_globbing(
	t_context *context, t_ast_node *father, t_dy_tab *quotes);

/*
** sh_pattern_matching.c
*/
int							sh_is_pattern_matching(
	char *name, t_list *regexp_head);

/*
** sh_regexp_parse.c
*/
int							sh_regexp_parse(
	char *str, t_dy_tab **regexp_tab);

/*
** t_regexp.c
*/
t_regexp					*t_regexp_new_push(t_list **regexp_list);
void						t_regexp_show_list(t_list *head);
void						t_regexp_show(t_regexp *regexp);

#endif
