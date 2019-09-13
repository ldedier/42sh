/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:45:00 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/11 17:58:41 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <termios.h>

typedef struct s_process	t_process;
typedef struct s_job		t_job;
typedef struct termios		t_term;

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
	char			*command;		/* command line, used for messages */
	t_process		*first_process;	/* list of processes in this job */
	pid_t			pgid;			/* process group ID */
	char			notified;		/* true if user told about stopped job */
	t_term			tmodes;			/* saved terminal modes */
	// int stdin, stdout, stderr;	/* standard i/o channels */
};

t_job	*g_job = NULL;

t_job			*find_job_by_pgid(pid_t pgid);
int				job_stopped_completed(t_job *j);
int				job_completed(t_job *j);
