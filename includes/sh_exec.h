/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:11:16 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/22 11:50:21 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_EXEC_H
# define SH_EXEC_H

# include "sh_21.h"
# include "sh_job_control.h"

# define SH_RET_VALUE_EXIT_STATUS(res)	res >> 8
# define SH_RET_VALUE_SIG_RECEIVED(res)	res & 0xff

# define SH_RET_SUCCESS			0
# define SH_RET_ERROR			1
# define SH_RET_SYNTAX_ERROR	2
# define SH_RET_NO_PERM			126
# define SH_RET_NOT_EXECUTABLE	126
# define SH_RET_CMD_NOT_FOUND	127
# define SH_RET_SIG_RECEIVED	128
# define SH_RET_CTRL_C			130

/*
** For job control
*/

# define SIMPLE_NODE			1
# define PIPE_NODE				2
# define AND_OR_NODE			4
# define CMD_TYPE				7
# define BG_NODE				8
# define FG_NODE				16
# define CMD_BG_FG				24

# define IS_BG(x)				x & BG_NODE
# define IS_PIPE(x)				x & PIPE_NODE
# define IS_SIMPLE(x)			x & SIMPLE_NODE

/*
** Builtin return value
*/
# define SH_RET_ARG_ERROR		2

extern pid_t g_parent;

typedef struct s_redirection	t_redirection;

typedef enum		e_phase
{
	E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS,
	E_TRAVERSE_PHASE_PIPE,
	E_TRAVERSE_PHASE_EXPANSIONS,
	E_TRAVERSE_PHASE_REDIRECTIONS,
	E_TRAVERSE_PHASE_EXECUTE
}					t_phase;

typedef struct		s_context
{
	char			wflags;
	int				cmd_type;
	char			*cmd_string;
	t_shell			*shell;
	struct termios	*term;
	t_dy_tab		*env;
	t_dy_tab		*saved_env;
	t_dy_tab		*vars;
	t_dy_tab		*alias;
	char			*path;
	t_dy_tab		*params;
	int				(*builtin)(struct s_context *);
	int				redirected_fd;
	t_phase			phase;
	t_ast_node		*current_command_node;
	t_ast_node		*current_pipe_sequence_node;
	t_list			*redirections;
	pid_t			pid;
	int				is_builtin;
	int				arithmetic_error;
}					t_context;

typedef struct		s_pipe
{
	int				**tab_pds;
	int				nb_pipe;
	int				nb_cmd;
	pid_t			*tab_pid;
}					t_pipe;

/*
********************************************************************************
*/

/*
** sh_debug.c
*/
void				print_redirection(t_redirection *redirection);
void				print_redirection_list(t_list *list);

/*
** sh_execute_and_or.c
*/
int					sh_execute_and_or(
	t_ast_node *node, t_context *context);

/*
** sh_execute_binary.c
*/
int					sh_execute_binary(
	t_ast_node *father_node, t_context *context);

/*
** sh_execute_builtin.c
*/
int					sh_execute_builtin(
	t_ast_node *parent_node, t_context *context);

/*
** sh_execute_execve.c
*/
void				sh_execute_execve(
	t_ast_node *parent_node, t_context *context);

/*
** sh_execute_pipe.c
*/
int					loop_pipe_exec(
	int curr_cmd,
	t_pipe *pipes,
	t_list *lst_sequences,
	t_context *context);
int					sh_execute_pipe(t_ast_node *node, t_context *context);

/*
** sh_execute_pipe_close_tools.c
*/
void				close_all_pipes_but_one(
	int nb_pipe, int curr_cmd, int **tab_pds);
void				close_pipes_and_free(
	int curr_cmd, t_pipe *pipes, t_context *context);
void				close_one_pipe(int curr, t_pipe *pipes);
void				close_all_pipes(t_pipe *pipes);

/*
** sh_execute_pipe_tools.c
*/
pid_t				fork_for_pipe(void);
int					create_all_pipe(
	int nb_pipe,
	t_pipe *pipes,
	t_list *lst_psequences,
	t_context *context);
int					pipe_fail_protocol(t_context *context, int ret);

/*
** sh_execute_prefix_postfix.c
*/
int					sh_pre_execution(void);
int					sh_post_execution(void);

/*
** sh_execute_redirection.c
*/
int					sh_execute_redirection(
	t_redirection *el, int is_builtin);

/*
** sh_execute_simple_command.c
*/
int					sh_execute_simple_command(
	t_ast_node *father_node, t_context *context);

/*
** t_context.c
*/
int					t_context_init(t_context *context, t_shell *shell);
void				t_context_free_content(t_context *context);
void				t_context_reset(t_context *context);

#endif
