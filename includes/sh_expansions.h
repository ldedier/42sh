/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:46:46 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/09 14:40:37 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_EXPANSIONS_H
# define SH_EXPANSIONS_H

/*
** Expansion header
*/
typedef struct s_expansion	t_expansion;
typedef enum e_exp_type		t_exp_type;

enum					e_exp_type
{
	EXP_VAR = 1,
	EXP_PARAM,
	EXP_CMD,
	EXP_ARITH,
	EXP_TILDE,
	EXP_CMD_SUBST,
	EXP_PROC_SUBST_IN, // >()
	EXP_PROC_SUBST_OUT, // <()
};

typedef struct			s_quote
{
	int		index;
	char	*c;
}						t_quote;

struct					s_expansion
{
	t_dy_str			*res;
	char				*original;
	char				*expansion;
	t_exp_type			type;
	int					(*process)(t_context *, t_expansion *);
};

/*
********************************************************************************
*/

/*
** sh_expansions.c
*/
int		sh_expansions(t_context *context, t_ast_node *node);

/*
** sh_expansions_cmd_subst.c
*/
int		sh_expansions_cmd_subst_detect_backquotes(char *start);
int		sh_expansions_cmd_subst_detect_dollar(char *start);
int		sh_expansions_cmd_subst_fill(t_expansion *exp, char *start);
char	*get_string_from_fd(int fd);
char 	*get_subshell_output(t_shell *shell, char *command);
int		sh_expansions_cmd_subst_process(
	t_context *context, t_expansion *exp);

/*
** sh_expansions_field_splitting.c
*/
int		sh_expansions_splitting(
	t_context *context, t_ast_node *node, t_dy_tab *quotes);

/*
** sh_expansions_history.c
*/
char	*ft_strdup_word_delim(char *str, int delim);
int		sh_history_expand(
	t_shell *shell,
	t_command_line *command_line,
	int *index,
	int *double_quoted);
int		sh_expansions_history(
	t_shell *shell, t_command_line *command_line, int *expanded);

/*
** sh_expansions_parameter.c
*/
int		sh_expansions_parameter_detect(char *start);
int		sh_expansions_parameter_fill(t_expansion *exp, char *start);
int		sh_expansions_parameter_process(
	t_context *context, t_expansion *exp);

/*
** sh_expansions_parameter_process.c
*/
int		sh_expansions_parameter_minus(
	t_context *context, t_expansion *exp, char *format);
int		sh_expansions_parameter_equal(
	t_context *context, t_expansion *exp, char *format);
int		sh_expansions_parameter_quest(
	t_context *context, t_expansion *exp, char *format);
int		sh_expansions_parameter_plus(
	t_context *context, t_expansion *exp, char *format);
int		sh_expansions_parameter_hash(
	t_context *context, t_expansion *exp, char *format);
int		sh_expansions_parameter_percent(
	t_context *context, t_expansion *exp, char *format);

/*
** sh_expansions_parameter_tools.c
*/
int		sh_expansions_parameter_format(
	t_expansion *exp, char *format, t_context *context);
char	*sh_expansions_parameter_get_param(
	t_context *context, t_expansion *exp);
int		sh_expansions_parameter_get_word(
	t_context *context, t_expansion *exp, char *format, char **word);

/*
** sh_expansions_proc_subst_in.c
*/
int		sh_expansions_proc_subst_in_detect(char *start);
int		sh_expansions_proc_subst_in_fill(t_expansion *exp, char *start);
char	*sh_get_fd_string(int fd);
char	*sh_get_process_subst_in(t_shell *shell, char *command);
int		sh_expansions_proc_subst_in_process(
	t_context *context, t_expansion *exp);

/*
** sh_expansions_proc_subst_out.c
*/
int		sh_expansions_proc_subst_out_detect(char *start);
int		sh_expansions_proc_subst_out_fill(t_expansion *exp, char *start);
char	*sh_get_process_subst_out(t_shell *shell, char *command);
int		sh_expansions_proc_subst_out_process(
	t_context *context, t_expansion *exp);

/*
** sh_expansions_process.c
*/
int		sh_expansions_process(
	char **input,
	char *original,
	t_context *context,
	int *index,
	t_dy_tab *quotes);

/*
** sh_expansions_quote_removal.c
*/
void	sh_expansions_quote_removal(t_quote **quotes);
void	sh_expansions_quote_removal_in_str(char *input);

/*
** sh_expansions_replace.c
*/
int		sh_expansions_replace(
	t_expansion *exp, char **input, int index, t_quote **quotes);

/*
** sh_expansions_scan.c
*/
int		sh_expansions_scan(
	char **input, int index, t_context *context, t_dy_tab *quotes);

/*
** sh_expansions_tilde.c
*/
int		sh_expansions_tilde_detect(char *start);
int		sh_expansions_tilde_process(t_context *context, t_expansion *exp);
int		sh_expansions_tilde(
	char **input, t_context *context, t_dy_tab *quotes, int *index);
int		sh_expansions_tilde_assignment(
	char **input, t_context *context, t_dy_tab *quotes);

/*
** sh_expansions_variable.c
*/
int		sh_expansions_variable_valid_name(char *name);
int		sh_expansions_variable_detect(char *start);
int		sh_expansions_variable_fill(t_expansion *exp, char *start);
int		sh_expansions_variable_process(
	t_context *context, t_expansion *exp);

/*
** t_expansion.c
*/
void	t_expansion_free_content(t_expansion *expansion);
void	t_expansion_show(t_expansion *exp);
void	t_expansion_show_type(t_expansion *exp);

/*
** t_quote.c
*/
t_quote	*t_quote_new(int index, char *c);
int		t_quote_add_new(t_dy_tab *quotes, int index, char *c);
void	t_quote_show_tab(t_quote **quotes);
int		t_quote_is_original_quote(int i, t_quote **quotes);
int		t_quote_get_offset(int i, t_quote **quotes);

#endif
