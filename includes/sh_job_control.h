/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_job_control.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:45:00 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/29 14:50:50 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SH_JOB_CONTROL_H
# define SH_JOB_CONTROL_H

# include "libft.h"
# include <termios.h>
# include "sh_grammar.h"

# define MAX_JOBS				17
# define ANY_CHILD_PROCESS		-1
# define MAX_PROCESS_LEN		1000

typedef struct s_process		t_process;
typedef struct s_job			t_job;
typedef struct s_job_control	t_job_control;
typedef struct s_job_cmd		t_job_cmd;
typedef struct termios			t_term;

/*
** This is the structure to follow up on process execution.
** Each job has a linked list of t_process.
** @completed: The process had completed (exited normally or with a signal).
** @stopped: process has stopped (but not completed).
** @pid: the pid of the process.
** @next: pointer to the next process in the job.
*/
struct	s_process
{
	char			completed;
	char			continued;
	char			stopped;
	char			cmd[MAX_PROCESS_LEN];
	int				status;
	pid_t			pid;
	t_process		*next;
};

/*
** Out job structure.
** @notified:	0: the job is done or stopped, but the user is not yet notified.
** 				1: the job is done or stopped, user is notified (will not be notified again).
** @command: the string that represent the command, for example "ls | wc".
** @signal_num: If the job has been stopped/ended by a signal. the signal_num will hold
**		the signal number of the last signal that was sent to any process in the job.
** @foregroud:	1: job is in the forground. 0 otherwise.
** @simple_cmd: 1: if the job is only a simple command. 0 otherwise (piped/and_or command).
** @number: the job number (1->MAX_JOBS)
** @pgid: the process group id of the job (the same as the pid of the job leader)
**	the job leader is always the first process in that job.
** @first_process: the head of the process list in the job.
** @next: pointer the next job.
*/
struct	s_job
{
	char			notified;
	char			*command;
	char			*cmd_copy;
	char			signal_num;	//Don't think this is needed anymore
	char			sign;
	char			foreground;
	int				number;
	pid_t			pgid;
	t_process		*first_process;
	t_job			*next;
};

struct	s_job_cmd
{
	char			*str;
	t_job_cmd		*next;
};

/*
**	Out global structure for job control.
**	interactive: 1 if the shell is running interactively, 0 otherwise.
**		A shell running non-interactively should not handle job control.
**		"./42sh < in" is a non-interacive shell.
**	job_added: a boolean. If at some point we add a job, we should not add another one
**		before current the command is done.
**		example: in command "ls" we add the job at the simple command level.
**		in command "ls | wc" we add it at the pipeline level, we set the job_added at 1
**			so that in the simple command level we don't add another job for "ls".
**	ampersand_eol : in the parser.c we check the list of tokens to see if the command
**		ends with "&"
**		(This should be changed because it won't work for subshell commands like
**		ls ; (sleep 5 &).
** shell_pgid: The group pid of our shell (the shell has its own group
**		and it's the only process in it).
**	term_fd: the fd of the terminal where we write all of the job messages
**		Such as "[1] Stopped" when we press a ctrl_z.
**	job_count and job_num: variables to get the right job number when we add a job.
**	job_cmd: this will be a linked list of strings that represent the commands.
**		for example: ls ; ls | wc & echo hi
**		Will have 3 nods, "ls" -> "ls | wc" -> "echo hi".
**		This is needed to for the "jobs" builtin and message reporting about jobs status.
**	first_job: This is the head of our jobs list (linked list also).
**	current_job: Last added job where we add our processes.
*/
struct	s_job_control
{
	char			interactive;
	char			job_added;
	char			ampersand_eol;
	char			ampersand;
	pid_t			shell_pgid;
	int				job_num[MAX_JOBS];
	t_job_cmd		*job_cmd;
	t_job			*first_job;
	t_job			*curr_job;
	t_list			*tokens;
};

t_job_control	*g_job_ctrl;

int				job_add(int fg);
int				job_check_changes(pid_t cpid, int status);
void			job_control_free(void);
void			job_free(t_job *j);
int				job_is_completed(t_job *j);
int				job_is_continued(t_job *j);
int				job_is_stopped(t_job *j);
void			job_notify(void);
void			job_print_status(t_job *j, const char *new_status);
void			job_print(t_job *j, int opt, int fd);
int				job_put_in_bg(t_job *j);
int				job_put_in_fg(t_job *j, int cont, int *res);
void			job_wait(t_job *j, int *res);
// int				jobs_create_cmds(t_list *token_list);
int				jobs_error_free(const char *err, const char *suff,
				int to_free, int ret);
void			jobs_free_cmds(void);
int				jobs_init(void);
void			jobs_print_cmds(void);
int				process_add(pid_t pid);
int				set_pgid_child(int cpid);
int				set_pgid_parent(int cpid);
char			**str_tab_duplicate(char **from);	//put in libft
void			str_tab_free(char **str);			//put in libft
void			str_tab_print(char **char_tab);		//put in libft
int				jobs_free_str(void);
char			*ft_strtok_pipe(char *str, char *delim);
void			jobs_copy_tokens(t_list *tokens);
void			jobs_free_tokens(void);

/*
** job_tools.c
*/
t_job			*job_get_by_num(int num);
t_job			*job_get_by_sign(char c);

/*
** job_sign_tools.c
*/

void			job_reset_sign(char c);
void			job_set_plus_sign(t_job *j);
void			job_added_update_sign(t_job *j);
t_job			*job_get_unsigned(void);
void			job_exited_update_sign(char j_sign);


/*
** jobs_str_tools.c
*/
int				next_sep_is_ampersand(t_list *ptr, t_list **rbrace);
int				token_break(t_symbol_id id);
int				add_job_cmd(t_job_cmd *cmd);
char			*create_cmd_word(t_token *t);

/*
** jobs_create_compound_str.c
*/
t_list			*create_brace_str(t_list *e);
t_list			*create_subshell_str(t_list *e);
t_list			*jobs_create_compound_str(t_list **s, t_list *e, t_symbol_id start_symb);

/*
** jobs_create_str.c
*/
int				jobs_create_str(t_list *token_list);

// int			jobs_create_cmds(t_list *token_list);

/*
** jobs_create_strings
*/
//char	*jobs_string_default(t_ast_node *node);
int				jobs_string_default(t_ast_node *node, char **str);
int				jobs_string_opn_par(t_ast_node *node, char **str);
int				jobs_string_cls_par(t_ast_node *node, char **str);
int				jobs_string_lbrace(t_ast_node *node, char **str);
int				jobs_string_rbrace(t_ast_node *node, char **str);
int				jobs_string_and(t_ast_node *node, char **str);
int				jobs_string_pipe(t_ast_node *node, char **str);
int				jobs_string_and_if(t_ast_node *node, char **str);
int				jobs_string_or_if(t_ast_node *node, char **str);
int				jobs_string_semicol(t_ast_node *node, char **str);
int				jobs_string_bang(t_ast_node *node, char **str);
int				jobs_string_less(t_ast_node *node, char **str);
int				jobs_string_great(t_ast_node *node, char **str);
int				jobs_string_dgreat(t_ast_node *node, char **str);
int				jobs_string_dless(t_ast_node *node, char **str);
int				jobs_string_less_and(t_ast_node *node, char **str);
int				jobs_string_great_and(t_ast_node *node, char **str);
int				jobs_string_word(t_ast_node *node, char **str);


#endif


