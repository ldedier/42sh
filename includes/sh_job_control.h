/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:45:00 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/17 00:13:11 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SH_JOB_CONTROL_H
# define SH_JOB_CONTROL_H

# include "libft.h"
# include <termios.h>
# include "sh_grammar.h"
# define MAX_JOBS				16

typedef struct s_process		t_process;
typedef struct s_job			t_job;
typedef struct s_job_control	t_job_control;
typedef struct termios			t_term;

struct	s_process
{
	char			completed;
	char			stopped;
	int				status;
	pid_t			pid;
	char			**argv;
	t_process		*next;
};

struct	s_job
{
	char			notified;
	char			*command;
	char			signal_num;
	char			foreground;
	int				number;
	pid_t			pgid;
	t_process		*first_process;
	t_job			*next;
};

struct	s_job_control
{
	char			shell_is_interactive;
	char			job_added;
	int				term_fd;
	int				job_count;
	int				job_num[MAX_JOBS];
	t_shell			*shell;
	t_job			*first_job;
	t_job			*curr_job;
	pid_t			shell_pgid;
};

t_job_control	*g_job_ctrl;

int				jobs_add(void);
void			jobs_print(void);
int				process_add(t_context *context, pid_t pid);
void			str_tab_print(char **char_tab);		//put in libft
char			**str_tab_duplicate(char **from);	//put in libft
int				jobs_init(t_shell *shell);
int				set_child_pgid(pid_t cpid);
void			job_wait(t_job *j, int *res);
int				job_put_in_bg(t_job *j, int cont);
int				job_put_in_fg(t_job *j, int cont, int *res);
int				job_is_completed(t_job *j);
int				job_is_stopped(t_job *j);
int				job_check_changes(pid_t cpid, int status);
void			job_free(t_job *j);
void			job_print_status(t_job *j, const char *new_status);
void			job_notify(void);
t_job			*get_active_job(void);

#endif