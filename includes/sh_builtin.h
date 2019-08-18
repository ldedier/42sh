/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:36:31 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/18 16:37:59 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_BUILTIN_H
# define SH_BUILTIN_H

# define NB_BUILTINS	10

# define CD_OPT_LOGIC	0x01
# define CD_OPT_PHYSIC	0x02
# define CD_OPT_HYPHEN	0x04

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
** sh_builtin_bonus.c
*/
int					sh_builtin_🐑(t_context *context);

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
** sh_builtin_env.c
*/
void				sh_builtin_env_usage(int fdout);
int					sh_builtin_env(t_context *context);

/*
** sh_builtin_env_parser.c
*/
int					sh_builtin_env_parser(
	t_context *context, t_dy_tab **new_env, t_dy_tab **new_param);

/*
** sh_builtin_env_process.c
*/
int					sh_builtin_env_no_args(t_context *context);
int					sh_builtin_env_process_command (
	t_context *context, t_dy_tab *new_env);

/*
** sh_builtin_exit.c
*/
int					sh_builtin_exit(t_context *context);

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
void				sh_builtin_hash_show(t_shell *shell);
void				sh_builtin_hash_update_stats(
	t_hash_table *table, t_binary_stats *stats);

/*
** sh_builtin_parser.c
*/
int					sh_builtin_usage(
	t_args args[], char *name, char *usage);
int					sh_builtin_parser_is_boolean(t_args args[], char opt);
int					sh_builtin_parser(
	int argc, char **argv, t_args args[], int *index);
void				sh_builtin_parser_show(t_args args[]);

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
** sh_builtin_setenv.c
*/
int					sh_builtin_setenv_process (
	char *entry, t_dy_tab *env, t_context *context);
int					sh_builtin_setenv(t_context *context);

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
** sh_builtin_unsetenv.c
*/
int					sh_builtin_unsetenv(t_context *context);

/*
** sh_builtin_verbose.c
*/
int					sh_builtin_verbose(t_context *context);

/*
** sh_builtin_where.c
*/
int					sh_builtin_where(t_context *context);

#endif
