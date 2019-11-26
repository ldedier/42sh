/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:36:31 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/26 08:50:49 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_BUILTIN_H
# define SH_BUILTIN_H

# define NB_BUILTINS	19

# include "sh_grammar.h"
# include "sh_21.h"
# include "sh_job_control.h"

# define NB_FLAG_UNARY	15
# define NB_FLAG_BINARY	8

/*
** Macros for cd builtin
*/
# define CD_USAGE			"[-LP] [dir] || cd -"
# define CD_P_OPT			0
# define CD_P_OPT_USAGE		"Resolve pathname without any symlinks"
# define CD_L_OPT			1
# define CD_L_OPT_USAGE		"Resolve pathname including symlinks (default)"
# define CD_HYPHEN_OPT		2

/*
** Macros for type builtin
*/
# define TYPE_USAGE			"[-atp] name [name ...]"
# define TYPE_A_OPT			0
# define TYPE_A_OPT_USAGE	"Print all places that contain valid executable"
# define TYPE_P_OPT			1
# define TYPE_P_OPT_USAGE	"Print path that name would execute"
# define TYPE_T_OPT			2
# define TYPE_T_OPT_USAGE	"Print a string describing the file type"

/*
** Macros for export builtin
*/
# define EXPORT_MSG			"export"
# define EXPORT_USAGE		"name[=word]"
# define EXPORT_P_OPT		0
# define EXPORT_P_OPT_USAGE	"print all exported variables (default option)"

/*
** Macros for alias builtin
*/

# define ALIAS_MSG			"alias"
# define ALIAS_USAGE			"[alias-name[=string]...]"
# define ALIAS_P_OPT			0
# define ALIAS_P_OPT_USAGE	"print all alias stored (default option)"

enum	e_built_test_unary {TEST_B, TEST_C, TEST_D, TEST_E, TEST_F, TEST_G,
	TEST_L, TEST_P, TEST_R, TEST_SS, TEST_S, TEST_U, TEST_W, TEST_X, TEST_Z};
enum	e_built_test_binary {TEST_EQU, TEST_NOEQU, TEST_EQ, TEST_NE, TEST_GT,
	TEST_GE, TEST_LT, TEST_LE};

typedef struct s_binary			t_binary;
typedef struct s_history		t_history;
typedef struct s_binary_stats	t_binary_stats;
typedef	int	(*t_builtin)(t_context *);

struct				s_binary
{
	char			*path;
	char			*name;
	int				hits;
};

struct				s_binary_stats
{
	int				max_path_len;
	int				max_name_len;
	int				max_hits_str_len;
};

typedef enum		e_fc_op_type
{
	E_FC_STRING,
	E_FC_INTEGER
}					t_fc_op_type;

typedef union		u_fc_op_union
{
	int				integer;
	char			*string;
}					t_fc_op_union;

typedef struct		s_fc_operand
{
	t_fc_op_type	type;
	t_fc_op_union	un;
	char			parsed : 1;
}					t_fc_operand;

typedef struct		s_fc_options
{
	t_fc_operand	from;
	t_fc_operand	to;
	char			opt_s : 1;
	char			opt_l : 1;
	char			opt_n : 1;
	char			opt_r : 1;
	char			*editor;

}					t_fc_options;

typedef struct		s_builtin_container
{
	char			*name;
	t_builtin		builtin;
}					t_builtin_container;

typedef enum		e_arg_type
{
	E_ARGS_END = 0,
	E_ARGS_STRING,
	E_ARGS_INT,
	E_ARGS_BOOL,
}					t_arg_type;

typedef struct		s_args
{
	t_arg_type	type;
	const char	name_short;
	const char	*name_long;
	void		*value;
	const char	*usage;
	int			priority;
}					t_args;

# if __APPLE__ && __MACH__

/*
** sh_builtin_bonus.c
*/
int					sh_builtin_🐑(t_context *context);

# endif

/*
********************************************************************************
*/

/*
** alias/sh_builtin_alias.c
*/
int					alias_valid_name(char *str);
int					sh_builtin_alias(t_context *context);

/*
** alias/sh_builtin_alias_show.c
*/
void				show_alias(char *str);
int					sh_builtin_alias_show(t_context *context);

/*
** bg/sh_builtin_bg.c
*/
int					sh_builtin_bg(t_context *context);

/*
** bg/sh_builtin_bg_tools.c
*/
int					parse_bg_spec(char *str, int j_lst[], int *it);
int					parse_bg_args(char **argv, int job_lst[]);
t_job				*bg_get_job_by_spec(int num);

/*
** cd/sh_builtin_cd.c
*/
int					sh_builtin_cd(t_context *context);

/*
** cd/sh_builtin_cd_parser.c
*/
int					sh_builtin_cd_parser(
	t_context *context, t_args *args, int *index, char **curpath);

/*
** cd/sh_builtin_cd_pre_rules.c
*/
int					sh_builtin_cd_pre_rules(
	t_context *context, char *param, char **curpath, t_args *args);

/*
** cd/sh_builtin_cd_rule_10.c
*/
int					sh_builtin_cd_check_perms(char *curpath, char *param);
int					sh_builtin_cd_rule10(
	t_context *context, char *curpath, t_args *args, char *param);

/*
** cd/sh_builtin_cd_rule_5.c
*/
int					sh_builtin_cd_rule5(
	t_context *context, char **curpath, char *param, t_args *args);

/*
** cd/sh_builtin_cd_rule_7.c
*/
int					sh_builtin_cd_rule7(
	t_context *context, char **curpath, t_args *args);

/*
** cd/sh_builtin_cd_rule_8.c
*/
int					sh_builtin_cd_rule8(char **curpath);

/*
** export/sh_builtin_export.c
*/
int					sh_builtin_export(t_context *context);

/*
** export/sh_builtin_export_show.c
*/
int					sh_builtin_export_show(t_context *context);

/*
** fc/sh_builtin_fc.c
*/
int					sh_builtin_fc(t_context *context);

/*
** fc/sh_builtin_fc_default_synopsis.c
*/
int					sh_builtin_fc_fill_text(
	t_history *history, t_dlist *from, t_dlist *to);
char				*sh_get_editor(char *editor, t_shell *shell);
void				fill_default_opts_default_synopsis(t_fc_options *opts);
int					sh_execute_editor(char *editor, t_shell *shell);
int					sh_builtin_fc_default_synopsis(
	t_context *context, t_fc_options *opts);

/*
** fc/sh_builtin_fc_get_command_to_execute.c
*/
char				*ft_substitute_occurences(
	char *str, char *to_replace, char *replacement);
char				*get_command_to_execute_fc(
	char *command, char *substitution_str);

/*
** fc/sh_builtin_fc_get_entry.c
*/
t_dlist				*get_entry_from_fc_operand(
	t_history *history, t_fc_operand *op, int fc);

/*
** fc/sh_builtin_fc_l_synopsis.c
*/
int					get_true_rank(t_history *history, int number);
int					get_listing_way(
	t_history *history, t_dlist *from, t_dlist *to);
void				sh_builtin_fc_list(
	t_history *history, t_dlist *from, t_dlist *to, int opt_n);
void				swap_entries(
	t_history *history, t_dlist **from, t_dlist **to);
int					sh_builtin_fc_l_synopsis(
	t_context *context, t_fc_options *opts);

/*
** fc/sh_builtin_fc_options.c
*/
int					invalid_argument(char *str, char c);
int					parse_fc_options(
	t_context *context, int *index, t_fc_options *opts);
int					describe_number(char *str);

/*
** fc/sh_builtin_fc_parse_operands.c
*/
int					sh_atoi_fc(const char *str, int *error);
int					parse_fc_operands(
	t_context *context, int index, t_fc_options *options);

/*
** fc/sh_builtin_fc_s_synopsis.c
*/
int					sh_builtin_fc_s_synopsis(
	t_context *context, t_fc_options *opts);

/*
** fc/sh_execute_commands_from_file.c
*/
int					sh_execute_commands_from_file(
	t_shell *shell, char *filename);

/*
** fg/sh_builtin_fg.c
*/
int					sh_builtin_fg(t_context *context);

/*
** fg/sh_builtin_fg_tools.c
*/
int					parse_fg_spec(char *str, int j_lst[], int *it);
int					parse_fg_args(char **argv, int job_lst[]);
t_job				*fg_get_job_by_spec(int num);

/*
** hash/sh_builtin_hash.c
*/
int					sh_builtin_hash(t_context *context);

/*
** hash/sh_builtin_hash_tools.c
*/
int					sh_builtin_hash_add_utility(
	t_context *context, char *utility);
void				sh_builtin_hash_empty_table(t_shell *shell);
int					sh_builtin_hash_show(t_shell *shell);
void				sh_builtin_hash_update_stats(
	t_hash_table *table, t_binary_stats *stats);

/*
** jobs/sh_builtin_jobs.c
*/
int					sh_builtin_jobs(t_context *context);

/*
** jobs/sh_builtin_jobs_tools.c
*/
int					parse_jobs_args(char **argv, int j_lst[], int *opt);

/*
** set/sh_builtin_set.c
*/
int					sh_builtin_set_param(t_context *context, int *index);
int					sh_builtin_set_args(t_context *context);
int					sh_builtin_set(t_context *context);

/*
** set/sh_builtin_set_options.c
*/
int					fill_option_value(
	int **address_ptr, int *value_ptr, int *address, int value);
int					get_option(
	t_shell *shell, char *option_name, int **option, int *value);
int					add_option(t_context *context, int index);
int					remove_option(t_context *context, int index);

/*
** set/sh_builtin_set_print.c
*/
int					sh_builtin_set_print(t_context *context);

/*
** set/sh_builtin_set_print_options.c
*/
void				print_builtin_usage(void);
int					print_options_minus(t_shell *shell);
int					print_options_plus(t_shell *shell);

/*
** sh_builtin.c
*/
t_builtin_container	*get_builtins(void);
t_builtin			sh_builtin_find_name(char *name);
t_builtin			sh_builtin_find(t_context *context);

/*
** sh_builtin_bonus.c
*/
int					sh_builtin_bonus(t_context *context);

/*
** sh_builtin_echo.c
*/
int					sh_builtin_echo(t_context *context);

/*
** sh_builtin_exit.c
*/
int					sh_builtin_exit(t_context *context);

/*
** sh_builtin_parser.c
*/
int					sh_builtin_parser(
	int argc, char **argv, t_args args[], int *index);

/*
** sh_builtin_parser_usage.c
*/
void				sh_builtin_parser_show(t_args args[]);
int					sh_builtin_usage(
	t_args ag[], char *name, char *usage, t_context *context);

/*
** sh_builtin_pwd.c
*/
char				*sh_builtin_pwd_physical(void);
char				*sh_builtin_pwd_logical(t_dy_tab *env);
int					sh_builtin_pwd(t_context *context);

/*
** sh_builtin_unalias.c
*/
int					sh_builtin_unalias(t_context *context);

/*
** sh_builtin_unset.c
*/
int					sh_builtin_unset(t_context *context);

/*
** sh_builtin_verbose.c
*/
int					sh_builtin_verbose(t_context *context);

/*
** test/sh_builtin_test.c
*/
int					sh_builtin_test(t_context *context);

/*
** test/sh_builtin_test_binary.c
*/
int					sh_builtin_test_binary(char **params, int ope);

/*
** test/sh_builtin_test_unary.c
*/
int					sh_builtin_test_unary(char **params, int arg);

/*
** type/sh_builtin_type.c
*/
int					sh_builtin_type(t_context *context);

/*
** type/sh_builtin_type_search.c
*/
int					sh_builtin_type_search_alias(
	char *name, t_args args[], t_context *context);
int					sh_builtin_type_search_reserved(
	char *name, t_args args[]);
int					sh_builtin_type_search_builtin(
	char *name, t_args args[]);
int					sh_builtin_type_search_hash(
	t_context *context, char *name, t_args args[]);

/*
** type/sh_builtin_type_search_path.c
*/
int					sh_builtin_type_search_in_path(
	t_context *context, char *name, t_args args[]);

#endif
