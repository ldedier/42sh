/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vars.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:35:18 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/30 15:54:53 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_VARS_H
# define SH_VARS_H

# define VERBOSE_AST		0x0001
# define VERBOSE_LEXER		0x0002
# define VERBOSE_EXEC		0x0004
# define VERBOSE_PIPE		0x0008
# define VERBOSE_EXPANSION	0x0010
# define VERBOSE_BUILTIN	0x0020
# define VERBOSE_TRAVERSE	0x0040

# ifndef SIGHUP
#  define SIGHUP	1
# endif
# ifndef SIGINT
#  define SIGINT	2
# endif
# ifndef SIGQUIT
#  define SIGQUIT	3
# endif
# ifndef SIGILL
#  define SIGILL	4
# endif
# ifndef SIGTRAP
#  define SIGTRAP	5
# endif
# ifndef SIGABRT
#  define SIGABRT	6
# endif
# ifndef SIGIOT
#  define SIGIOT	SIGABRT
# endif
# ifndef SIGEMT
#  define SIGEMT	7
# endif
# ifndef SIGFPE
#  define SIGFPE	8
# endif
# ifndef SIGKILL
#  define SIGKILL	9
# endif
# ifndef SIGBUS
#  define SIGBUS	10
# endif
# ifndef SIGSEGV
#  define SIGSEGV	11
# endif
# ifndef SIGSYS
#  define SIGSYS	12
# endif
# ifndef SIGPIPE
#  define SIGPIPE	13
# endif
# ifndef SIGALRM
#  define SIGALRM	14
# endif
# ifndef SIGTERM
#  define SIGTERM	15
# endif
# ifndef SIGURG
#  define SIGURG	16
# endif
# ifndef SIGSTOP
#  define SIGSTOP	17
# endif
# ifndef SIGTSTP
#  define SIGTSTP	18
# endif
# ifndef SIGCONT
#  define SIGCONT	19
# endif
# ifndef SIGCHLD
#  define SIGCHLD	20
# endif
# ifndef SIGTTIN
#  define SIGTTIN	21
# endif
# ifndef SIGTTOU
#  define SIGTTOU	22
# endif
# ifndef SIGIO
#  define SIGIO		23
# endif
# ifndef SIGXCPU
#  define SIGXCPU	24
# endif
# ifndef SIGXFSZ
#  define SIGXFSZ	25
# endif
# ifndef SIGVTALRM
#  define SIGVTALRM 26
# endif
# ifndef SIGPROF
#  define SIGPROF	27
# endif
# ifndef SIGWINCH
#  define SIGWINCH	28
# endif
# ifndef SIGINFO
#  define SIGINFO	29
# endif
# ifndef SIGUSR1
#  define SIGUSR1 30
# endif
# ifndef SIGUSR2
#  define SIGUSR2 31
# endif

/*
********************************************************************************
*/

/*
** sh_verbose_check.c
*/
int		sh_verbose_ast(void);
int		sh_verbose_lexer(void);
int		sh_verbose_exec(void);
int		sh_verbose_pipe(void);
int		sh_verbose_expansion(void);

/*
** sh_env_tools.c
*/
char	*sh_env_get_value(char **env, char *str);

/*
** sh_vars_tools_1.c
*/
int		sh_vars_key_exist(t_dy_tab *vars, char *key);
int		sh_vars_get_index(t_dy_tab *vars, char *key);
char	*sh_vars_get_value(t_dy_tab *env, t_dy_tab *vars, char *key);

/*
** sh_verbose.c
*/
void	sh_verbose_update(t_shell *shell);
int		sh_verbose_traverse(void);
int		sh_verbose_builtin(void);

/*
** sh_env.c
*/
void	sh_env_update_ret_value_wait_result(t_context *context, int res);
void	sh_env_update_ret_value(t_shell *shell, int res);
int		sh_env_update_question_mark(t_shell *shell);
int		sh_env_update_ret_value_and_question(t_shell *shell, int res);

/*
** sh_vars_tools_2.c
*/
int		sh_vars_mod_key(t_dy_tab *vars, char *key, char *value);
int		sh_vars_add_key(t_dy_tab *vars, char *key, char *value);
int		sh_vars_assignment(
	t_dy_tab *env, t_dy_tab *vars, char *assignment);
int		sh_vars_assign_key_val(
	t_dy_tab *env, t_dy_tab *vars, char *key, char *value);

#endif
