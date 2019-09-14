/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:45:00 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/15 00:01:59 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <termios.h>
#include "sh_grammar.h"
# define JOB_ACCESS_LOCKED		1
# define JOB_ACCESS_UNLOCKED	0

typedef struct s_process		t_process;
typedef struct s_job			t_job;
typedef struct s_job_control	t_job_control;
typedef struct termios			t_term;

struct	s_process
{
	t_process		*next;			/* next process in pipeline */
	char			**argv;			/* for exec */
	pid_t			pid;			/* process ID */
	char			completed;		/* true if process has completed */
	char			stopped;		/* true if process has stopped */
	int				status;			/* reported status value */
};

struct	s_job
{
	t_job			*next;			/* next active job */
	int				number;
	char			*command;		/* command line, used for messages */
	t_process		*first_process;	/* list of processes in this job */
	pid_t			pgid;			/* process group ID */
	char			notified;		/* true if user told about stopped job */
	char			empty_process;	/* true if no processes are in the job */
	// t_term			tmodes;			/* saved terminal modes */
	// int stdin, stdout, stderr;	/* standard i/o channels */
};

struct	s_job_control
{
	int				term_fd;
	t_shell			*shell;
	char			shell_is_interactive;
	int				job_count;
	t_job			*first_job;
	pid_t			shell_pgid;
};

t_job_control	*g_job_control;

t_job			*find_job_by_pgid(pid_t pgid);
int				job_stopped_completed(t_job *j);
int				job_completed(t_job *j);
int				job_add(void);
void			job_print(void);
int				process_add(t_context *context, pid_t pid);
void			str_tab_print(char **char_tab);		//put in libft
char			**str_tab_duplicate(char **from);	//put in libft
int				init_job_control(t_shell *shell);
int				job_start(t_job *j, int foreground);
int				job_exec(void);
int				j_process_start(t_process *p, pid_t pgid, int foreground);
