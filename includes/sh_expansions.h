/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:46:46 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/05 11:12:35 by jdugoudr         ###   ########.fr       */
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
};

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
** sh_expansion_process.c
*/
int			sh_expansions_process(
	char **input, char *original, t_context *context, int *index);

/*
** sh_expansion_replace.c
*/
int			sh_expansions_replace(
	t_expansion *expansion, char **input, int index);

/*
** sh_expansions.c
*/
int			sh_expansions(t_context *context, t_ast_node *node);

/*
** sh_get_heredoc.c
*/
char		*get_heredoc(t_context *context, t_heredoc *heredoc_data, int *ret);

/*
** sh_expansions_field_splitting.c
*/
int		sh_expansions_splitting(t_ast_node *node, t_context *context);

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

/*
** sh_expansions_parameter_tools.c
*/
int		sh_expansions_parameter_format(t_expansion *exp, char *format);
char	*sh_expansions_parameter_get_param(
	t_context *context, t_expansion *exp);
char	*sh_expansions_parameter_get_word(t_expansion *exp, char *format);

/*
** sh_expansions_scan.c
*/
int		sh_expansions_scan(
	char **input, int index, int do_expansion, t_context *context);

/*
** sh_expansions_tilde.c
*/
int		sh_expansions_tilde_detect(char *start);
int		sh_expansions_tilde_fill(t_expansion *exp, char *start);
int		sh_expansions_tilde_process(t_context *context, t_expansion *exp);

/*
** sh_expansions_tilde_process.c
*/
int		sh_expansions_tilde(
	char **input, char *original, t_context *context);

/*
** sh_expansions_variable.c
*/
int		sh_expansions_variable_valid_name(char *name);
int		sh_expansions_variable_detect(char *start);
int		sh_expansions_variable_fill(t_expansion *exp, char *start);
int		sh_expansions_variable_process(
	t_context *context, t_expansion *exp);

/*
** sh_unquoted_var.c
*/
int		sh_unquoted_var(char **input, int *index, t_context *context);

/*
** t_expansion.c
*/
void	t_expansion_free_content(t_expansion *expansion);
void	t_expansion_show(t_expansion *exp);
void	t_expansion_show_type(t_expansion *exp);

#endif
