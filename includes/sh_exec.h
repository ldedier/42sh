/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:11:16 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/16 18:11:45 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_EXEC_H
# define SH_EXEC_H

# include "sh_21.h"

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
** Builtin return value
*/
# define SH_RET_ARG_ERROR		2

extern pid_t g_parent;

typedef struct		s_redirection t_redirection;
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
}					t_context;

typedef	struct		s_pipe{
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
** sh_execute.c
*/
int 				sh_execute_simple_command(t_context *context);

/*
** sh_execute_binary.c
*/
void				sh_execute_binary(t_context *context);

/*
** sh_execute_builtin.c
*/
int					sh_execute_builtin(t_context *context);

/*
** sh_execute_pipe.c
*/
int					sh_execute_pipe(t_ast_node *node, t_context *context);

/*
** sh_execute_prefix_postfix.c
*/
int					sh_pre_execution();
int					sh_pre_execution_pipes(t_list *contexts);
int					sh_post_execution(void);

/*
** sh_execute_redirection.c
*/
int 				sh_execute_redirection(t_list *lst, t_redirection *el);

/*
** t_context.c
*/
int					t_context_init(t_context *context, t_shell *shell);
void				t_context_free_content(t_context *context);
void				t_context_reset(t_context *context);

/*
** sh_execute_pipe_tool.c
*/
void				close_one_pipe(int curr, t_pipe *pipes);
void				close_and_free(
		int curr_cmd, t_pipe *pipes, t_context *context);
void				close_all_pipe_but_one(
		int nb_pipe, int curr_cmd, int **tab_pds);
#endif
