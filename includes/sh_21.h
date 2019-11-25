/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_21.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 15:48:56 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/25 22:38:23 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_21_H
# define SH_21_H

# include <stdio.h>

# include <stdarg.h>
# include <termcap.h>
# include <term.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>

/*
** wait(2)
*/
# include <sys/wait.h>

/*
** read(2)
*/
# include <fcntl.h>

# include "libft.h"
# include "sh_perror.h"
# include "sh_tokens.h"
# include "sh_parser.h"
# include "sh_productions.h"
# include "sh_grammar.h"
# include "sh_autocompletion.h"
# include "sh_lexer.h"
# include "sh_exec.h"
# include "sh_builtin.h"
# include "sh_traverse.h"
# include "sh_traverse_tools.h"
# include "sh_command_line.h"
# include "sh_expansions.h"
# include "sh_globbing.h"
# include "sh_vars.h"
# include "sh_shortcuts.h"
# include "sh_history.h"
# include "sh_redirection.h"
# include "sh_job_control.h"
# include "sh_arithmetic_productions.h"
# include "sh_arithmetic.h"

# define SUCCESS		0
# define ERROR			1
# define FAILURE		2
# define ATTR_ERROR		3
# define STOP_CMD_LINE	4
# define BLT_TEST_ERROR	5

# define CTRL_D			5
# define CTRL_C			6

# define KEEP_READ		7
# define HIST_EXP_ERROR	8

# define RETURN_COMMAND	 9

# define MAX_YANK				2000
# define BINARIES_TABLE_SIZE	200
# define MAX_EXEC_RECURSIONS	100

/*
** Macros of fdin, fdout and fderr in context->fd
*/
# define FD_IN		STDIN_FILENO
# define FD_OUT		STDOUT_FILENO
# define FD_ERR		STDERR_FILENO

# define CWD_LEN		1000
# define NB_OPERATIONS	12

/*
** Pipe input and output indexes in a int[2]
*/
# define PIPE_IN		1
# define PIPE_OUT		0

/*
** Colors defines
*/
# define COLOR_BLACK	"\033[1;30m"
# define COLOR_RED		"\033[1;31m"
# define COLOR_GREEN	"\033[1;32m"
# define COLOR_YELLOW	"\033[1;33m"
# define COLOR_BLUE		"\033[1;34m"
# define COLOR_PINK		"\033[1;35m"
# define COLOR_CYAN		"\033[1;36m"
# define COLOR_GREY		"\033[1;37m"
# define COL_MAGENTA	"\033[0;35m"
# define COL_B_MAGENTA	"\033[1;35m"
# define COLOR_END		"\033[1;0m"

/*
** ANSI color constants
*/
# define RED        "\x1B[31m"
# define GREEN      "\x1B[32m"
# define YELLOW     "\x1B[33m"
# define BLUE       "\x1B[34m"
# define MAGENTA    "\x1B[35m"
# define CYAN       "\x1B[36m"
# define WHITE      "\x1B[37m"
# define L_GREY     "\x1B[90m"
# define L_BLUE     "\x1B[94m"
# define L_MAGENTA  "\x1B[95m"
# define L_CYAN     "\x1B[96m"
# define L_GREEN    "\e[1;32m"
# define BRED       "\x1B[41m"
# define BGREEN     "\x1B[42m"
# define BYELLOW    "\x1B[43m"
# define BBLUE      "\x1B[44m"
# define BMAGENTA   "\x1B[44m"
# define BCYAN      "\x1B[46m"
# define BWHITE     "\x1B[47m"
# define BL_BLUE    "\x1B[104m"
# define BL_MAGENTA "\x1B[105m"
# define BL_CYAN    "\x1B[106m"
# define BOLD       "\x1b[1m"
# define UNDERLINE  "\x1b[4m"
# define EOC        "\033[0m"

/*
** Activate or not bonuses that require forbidden functions
*/

# define BONUS_HOME_AS_TILDE_PROMPT	1
# define BONUS_REDIRECT_SIGNAL		1
# define BONUS_DOLLAR_VARIABLE		1
# define BONUS_TILDE_EXP			1

/*
** The tty can only be open on the fd :
*/
# define TTY_FD	10

/*
** The default terminal to launch the shell with
*/

# define DEFAULT_TERM "xterm-256color"

typedef struct s_shell		t_shell;

struct				s_shell
{
	t_lr_parser		parser;
	t_lr_parser		parser_ar;
	t_history		history;
	t_dy_tab		*env;
	t_dy_tab		*saved_env;
	t_dy_tab		*vars;
	t_dy_tab		*alias;
	t_hash_table	*binaries;
	char			running;
	struct termios	term;
	int				ret_value_set;
	int				ret_value;
	int				exec_depth;
	t_exec			*exec;
	char			*hist_dup;
};

/*
** Added by mdaoud
** This the variable that points to the terminal fd
*/

int		g_term_fd;

/*
********************************************************************************
*/

/*
** canonical_mode.c
*/
int					sh_process_canonical_mode(t_shell *shell, char **env);

/*
** check_term.c
*/
char				**get_operations(void);
int					sh_check_term(void);

/*
** execute_command.c
*/
void				free_execution_tools(
	t_list **tokens, t_ast_node **ast_root, t_ast_node **cst_root);
int					execute_command(
	t_shell *shell, char *command, int should_add);

/*
** free_all.c
*/
void				sh_free_binary(t_binary *binary);
void				sh_free_binary_lst(void *b, size_t dummy);
void				free_file(t_file *file);
void				sh_free_all(t_shell *shell);

/*
** free_all_dlist.c
*/
void				free_file_dlst(void *f, size_t dummy);
void				free_entry_dlst(void *e, size_t dummy);

/*
** hash_binaries.c
*/
t_binary			*sh_new_binary(char *path, char *name);
int					compare_str_to_binary(void *str, void *binary);
int					sh_update_hash_table(
	t_shell *shell, char *path, char *name);

/*
** history.c
*/
void				print_history(t_history *history);
int					sh_append_to_history(
	t_history *history, char *command, int append_file);

/*
** home.c
*/
char				*get_home_dup(t_shell *shell);
int					process_subst_home(t_shell *shell, char **str);

/*
** index.c
*/
int					sh_index_4(t_symbol_id id);
int					sh_index_3(t_symbol_id id);
int					sh_index_2(t_symbol_id id);
int					sh_index(int id);

/*
** init.c
*/
int					sh_init_allocations(t_shell *shell, char **env);
int					sh_init_shell(t_shell *shell, char **env);

/*
** init_env.c
*/
int					sh_main_init_env(t_shell *shell, char **env);

/*
** init_term.c
*/
int					sh_init_terminal_database(char **env);
int					sh_set_term_sig(int value);
int					sh_init_terminal(t_shell *shell, char **env);

/*
** init_vars.c
*/
int					sh_main_init_vars(t_shell *shell);

/*
** non_canonical_mode.c
*/
int					sh_process_noncanonical_mode(t_shell *shell);

/*
** set_signals.c
*/
void				reset_signals(void);
void				handler_sighup(int signo);
void				handler_sigwinch(int signo);
void				init_signals(void);

/*
** sh_split_path.c
*/
char				**sh_split_path(char const *path);

/*
** shell_tools.c
*/
int					sh_reset_shell(int ret);
int					sh_set_shell_back(int ret);
int					clear_all(void);

/*
** signal_tools.c
*/
void				transmit_sig_and_exit(int signal);
void				handle_stp(int sgnl);
void				handle_cont(int sgnl);

/*
** signals.c
*/
void				transmit_sig_and_die(int signal);
void				default_sig_bonus(int sgnl);
void				default_sig(int sgnl);
void				handle_resize(int signal);

/*
** t_entry.c
*/
t_entry				*t_entry_new(int number, char *command);
void				t_entry_free(t_entry *entry);
void				t_entry_print(t_entry *entry, int print_number);

/*
** tools.c
*/
int					end_with_char(char *str, char c);
int					get_file_in_dir(char *filename, char *dirname);
int					get_path_from_absolute_path(char *str, char **path);
int					get_path_and_file_from_str(
	char *str, char **path, char **file);

#endif
