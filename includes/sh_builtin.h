/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:36:31 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/27 16:39:28 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_BUILTIN_H
# define SH_BUILTIN_H

# if __APPLE__ && __MACH__
#  define NB_BUILTINS	13
# else
#  define NB_BUILTINS	12
# endif

# define CD_OPT_LOGIC	0x01
# define CD_OPT_PHYSIC	0x02
# define CD_OPT_HYPHEN	0x04

# define NB_FLAG_UNARY	15
# define NB_FLAG_BINARY	8

enum e_built_test_unary {TEST_B, TEST_C, TEST_D, TEST_E, TEST_F, TEST_G, TEST_L,
	TEST_P, TEST_R, TEST_SS, TEST_S, TEST_U, TEST_W, TEST_X, TEST_Z};
enum e_built_test_binary {TEST_EQU, TEST_NOEQU, TEST_EQ, TEST_NE, TEST_GT,
	TEST_GE, TEST_LT, TEST_LE};

typedef struct s_binary			t_binary;
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
** sh_builtin.c
*/
t_builtin_container	*get_builtins(void);
t_builtin			sh_builtin_find_name(char *name);
t_builtin			sh_builtin_find(t_context *context);

/*
** sh_builtin_cd.c
*/
int					sh_builtin_cd(t_context *context);

/*
** sh_builtin_cd_last_rules.c
*/
int					sh_builtin_cd_rule10(
	t_context *context, char *curpath, int flags, char *param);

/*
** sh_builtin_cd_post_rules.c
*/
int					sh_builtin_cd_rule7(
	t_context *context, char **curpath, char flags);
int					sh_builtin_cd_rule8_1(char **curpath);

/*
** sh_builtin_cd_pre_rules.c
*/
int					sh_builtin_cd_parser(
	t_context *context, int *i, char *flag, char **curpath);
int					sh_builtin_cd_pre_rules(
	t_context *context, char *param, char **curpath);
int					sh_builtin_cd_rule5(
	t_context *context, char **curpath, char *param);

/*
** sh_builtin_echo.c
*/
int					sh_builtin_echo(t_context *context);

/*
** sh_builtin_exit.c
*/
int					sh_builtin_exit(t_context *context);

/*
** sh_builtin_export.c
*/
int					sh_builtin_export_show(t_context *context);
int					sh_builtin_export_assign(
	t_context *context, char *arg);
int					sh_builtin_export(t_context *context);

/*
** sh_builtin_hash.c
*/
int					sh_builtin_hash(t_context *context);

/*
** sh_builtin_hash_tools.c
*/
int					sh_builtin_hash_add_utility(
	t_context *context, char *utility);
void				sh_builtin_hash_empty_table(t_shell *shell);
int					sh_builtin_hash_show(
	t_context *context, t_shell *shell);
void				sh_builtin_hash_update_stats(
	t_hash_table *table, t_binary_stats *stats);

/*
** sh_builtin_parser.c
*/
int					sh_builtin_parser_is_boolean(t_args args[], char opt);
int					sh_builtin_parser(
	int argc, char **argv, t_args args[], int *index);
void				sh_builtin_parser_show(t_args args[]);
int					sh_builtin_usage(
	t_args args[], char *name, char *usage, t_context *context);

/*
** sh_builtin_pwd.c
*/
char				*sh_builtin_pwd_physical(int fd_err);
char				*sh_builtin_pwd_logical(t_dy_tab *env, int fd_err);
int					sh_builtin_pwd(t_context *context);

/*
** sh_builtin_set.c
*/
int					sh_builtin_set(t_context *context);

/*
** sh_builtin_test.c
*/
int					sh_builtin_test(t_context *context);

/*
** sh_builtin_test_binary.c
*/
int					sh_builtin_test_binary(char **params, int ope);

/*
** sh_builtin_test_unary.c
*/
int					sh_builtin_test_unary(char **params, int arg);

/*
** sh_builtin_type.c
*/
int					sh_builtin_type(t_context *context);

/*
** sh_builtin_type_path.c
*/
int					sh_builtin_type_search_in_dir(
	char *path, DIR *dir, t_context *context, char *name);
int					sh_builtin_type_search_in_path(
	t_context *context, char *name, t_args args[]);

/*
** sh_builtin_unset.c
*/
int					sh_builtin_unset(t_context *context);

/*
** sh_builtin_verbose.c
*/
int					sh_builtin_verbose(t_context *context);

#endif
