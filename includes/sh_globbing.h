/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_globbing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 23:13:55 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/23 19:44:56 by jmartel          ###   ########.fr       */
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
	REG_BRACE,
	REG_FINAL_SLASH
};

struct						s_regexp
{
	t_regexp_type	type;
	int				len;
	char			*value;
};

typedef struct				s_glob_lexer
{
	char					*input;
	char					c;
	char					quoted;
	int						tok_len;
	int						tok_start;
	t_dy_tab				*quotes;
	t_dy_tab				*regexp_tab;
	int						regexp_tab_index;
}							t_glob_lexer;

/*
********************************************************************************
*/

/*
** lexer/sh_glob_lexer.c
*/
int							t_glob_lexer_add_str(t_glob_lexer *lexer);
int							sh_glob_lexer(
	char *str, t_dy_tab **regexp_tab, t_dy_tab *quotes);

/*
** lexer/sh_glob_lexer_rule_1.c
*/
int							sh_glob_lexer_rule_1(t_glob_lexer *lexer);

/*
** lexer/sh_glob_lexer_rule_2.c
*/
int							sh_glob_lexer_rule_2(t_glob_lexer *lexer);

/*
** lexer/sh_glob_lexer_rule_3.c
*/
int							sh_glob_lexer_rule_3(t_glob_lexer *lexer);

/*
** lexer/sh_glob_lexer_rule_4.c
*/
int							sh_glob_lexer_rule_4(t_glob_lexer *lexer);

/*
** lexer/sh_glob_lexer_rule_5.c
*/
int							sh_glob_lexer_rule_5(t_glob_lexer *lexer);

/*
** lexer/sh_glob_lexer_rule_6.c
*/
int							sh_glob_lexer_rule_6(t_glob_lexer *lexer);

/*
** sh_globbing.c
*/
int							sh_expansions_globbing(
	t_ast_node *node, t_dy_tab *quotes, int ret);

/*
** sh_globbing_for_substring_removal.c
*/
int							sh_globbing_substring_removal_get_word(
	char *param, char **word, t_expansion *exp, char *format);

/*
** sh_is_pattern_matching.c
*/
int							sh_globbing_call_pattern_function(
	char *name, int *i, t_list **regexp_head);
int							sh_is_pattern_matching(
	char *name, t_list *regexp_head);
int							sh_is_pattern_matching_for_substring_removal(
	char *name, t_list *regexp_head);

/*
** sh_pattern_matching.c
*/
int							sh_expansions_pattern_matching(
	char *path, t_list **regexp_list, t_list **matchs);

/*
** sh_pattern_matching_brace.c
*/
int							sh_pattern_matching_brace(
	char *name, t_regexp *regexp, int *i);

/*
** sh_pattern_matching_brace_tools.c
*/
int							sh_pattern_matching_brace_dash(
	char *name, t_regexp *regexp, int *i, int *j);
int							sh_pattern_matching_brace_simple(
	char *name, t_regexp *regexp, int *i, int *j);

/*
** sh_pattern_matching_push_new.c
*/
int							pattern_matching_push_new(
	t_list **matches, char *path);

/*
** sh_pattern_matching_quest.c
*/
int							sh_pattern_matching_quest(
	char *name, t_regexp *regexp, int *i);

/*
** sh_pattern_matching_star.c
*/
int							sh_pattern_matching_star(
	char *name, int *i, t_list *regexp_head);

/*
** sh_pattern_matching_str.c
*/
int							sh_pattern_matching_str(
	char *name, t_regexp *regexp, int *i);

/*
** sh_regexp_parse.c
*/
int							sh_regexp_parse_path_component(
	char *str, t_list **regexp_list);

/*
** sh_regexp_parse_new_brace.c
*/
int							sh_regexp_parse_new_brace(
	char *str, int *i, t_list **regexp_list);

/*
** sh_regexp_parse_new_quest.c
*/
int							sh_regexp_parse_new_quest(
	int *i, t_list **regexp_list);

/*
** sh_regexp_parse_new_star.c
*/
int							sh_regexp_parse_new_star(
	int *i, t_list **regexp_list);

/*
** sh_regexp_parse_new_string.c
*/
int							sh_regexp_parse_new_string(
	char *str, int *i, t_list **regexp_list);

/*
** t_regexp.c
*/
t_regexp					*t_regexp_new_push(t_list **regexp_list);
void						t_regexp_show_list(t_list *head);
void						t_regexp_show(t_regexp *regexp);
void						t_regexp_free(void *ptr, size_t size);
void						t_regexp_free_tab(t_dy_tab **regexp_tab);

#endif
