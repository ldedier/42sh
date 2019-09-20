/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 00:39:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/20 03:19:06 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "job_control.h"

void		signal_send(pid_t to)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		sleep (2);
		ft_printf("SENDING SIGINT TO %d (%d)\n", to, g_job_control->current_job->pgid);
		kill(SIGINT, to);
		exit(0);
	}
}
/*
** case: simple command (no pipes, no builtins)
*/

static void			handler_sigint_process2(int signo)
{
	(void)SIGINT;
	// if (signo == SIGINT)
	// {
		// ft_printf("HANDLER_PROCESS_SIGINT : pid: %d pgid: %d\n", getpid(), getpgid(getpid()));
		char *msg = "HANDLER_PROCESS_SIGINT\n";
		write(1, msg, ft_strlen(msg));
		exit (1);
		// kill(0, SIGINT);
		// tcsetpgrp(g_job_control->term_fd, g_job_control->shell_pgid);
	// }
}

int			sh_process_process_execute(t_context *context)
{
	int			res;
	pid_t		child_pid;

	if (sh_pre_execution(context) != SUCCESS)
		return (FAILURE);
	if ((child_pid = fork()) == -1)
		return (sh_perror(SH_ERR1_FORK, "sh_process_process_execute"));
	if (child_pid == 0)
	{
		// if (signal(SIGINT, handler_sigint_process2) == SIG_ERR)
		// 	ft_printf("ERROR SIGNAL\n");
		// else
		// 	ft_printf("SIGNAL HANDLER SET\n");

		// reset_signals();
		child_pid = getpid();
		if (g_job_control->current_job->pgid == 0)
			g_job_control->current_job->pgid = child_pid;
		setpgid(child_pid, g_job_control->current_job->pgid);
		sh_execute_child_binary(context, NULL);
	}
	else
	{
		if (g_job_control->current_job->pgid == 0)
			g_job_control->current_job->pgid = child_pid;
		setpgid(child_pid, g_job_control->current_job->pgid);
		ft_printf("Shell giving control to child\n");
		tcsetpgrp (g_job_control->term_fd, g_job_control->current_job->pgid);
		ft_printf("SHELL WAITING\n");
		wait(&res);
		if (WIFEXITED(res))
			ft_printf("child exited normally\n");
		else
			ft_printf("child was terminated by a signal\n");
		tcsetpgrp (g_job_control->term_fd, g_job_control->shell_pgid);
		pid_t grp = tcgetpgrp(0);
		ft_printf("CONTROLLING GROUP: %d\n", grp);
		// ft_printf("\t\tSHELL CONTROLLING TERMINAL\n");
		g_parent = 0;
		sh_env_update_ret_value_wait_result(context, res);
		sh_process_execute_close_pipes(context);
		if (sh_post_execution() != SUCCESS)
			return (FAILURE);
		g_glob.command_line.interrupted = WIFSIGNALED(res);
	}
	return (SUCCESS);
}
/*
int			sh_process_process_execute(t_context *context)
{
	int			res;

	if (sh_pre_execution(context) != SUCCESS)
		return (FAILURE);
	process_add(context, 0);
	if ((g_parent = fork()) == -1)
		return (sh_perror(SH_ERR1_FORK, "sh_process_process_execute"));
	if (g_parent == 0)
		sh_execute_child_binary(context, NULL);
	else
	{
		wait(&res);
		g_parent = 0;
		sh_env_update_ret_value_wait_result(context, res);
		sh_process_execute_close_pipes(context);
		if (sh_post_execution() != SUCCESS)
			return (FAILURE);
		g_glob.command_line.interrupted = WIFSIGNALED(res);
	}
	return (SUCCESS);
}
*/
int			sh_add_to_pipe_sequence(t_context *context)
{
	t_context	*context_dup;

	context->current_pipe_sequence_node
		->metadata.pipe_metadata.last_ret_value = 0;
	if (!(context_dup = t_context_dup(context)))
		return (FAILURE);
	if (ft_lstaddnew_ptr_last(&context->current_pipe_sequence_node->
		metadata.pipe_metadata.contexts, context_dup,
			sizeof(t_context)))
		return (FAILURE);
	return (SUCCESS);
}

int			sh_process_execute(t_context *context)
{
	if (context->current_pipe_sequence_node)
		return (sh_add_to_pipe_sequence(context));
	else
		return (sh_process_process_execute(context));
}
