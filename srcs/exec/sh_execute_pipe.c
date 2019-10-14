/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/14 05:43:03 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

typedef	struct s_pipe{
	int		**tab_pds;
	int		nb_pipe;
	int		nb_cmd;
	pid_t	*tab_pid;
}			t_pipe;

/*
** close_all_pipe_but_one
** As we create pipe in shell process, all child process
** have a reference to all the pipe.
** Before execution we close all unused pipe.
*/
static void			close_all_pipe_but_one(int nb_pipe, int curr_cmd, int **tab_pds)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
	{
		if (i == curr_cmd)
			close(tab_pds[i][INPUT]);
		else if (i == curr_cmd - 1)
			close(tab_pds[i][OUTPUT]);
		else
		{
			close(tab_pds[i][OUTPUT]);
			close(tab_pds[i][INPUT]);
		}
		i++;
	}
}

static pid_t 		fork_for_pipe()
{
	pid_t 	child;
	int		ret;

	if ((child = fork()) < 0)
	{
		sh_perror(SH_ERR1_FORK, "execution fork for pipe");
		return (-1);
	}
	if (child == 0)
	{
		if (g_job_ctrl->interactive)
		{
			if ((ret = set_pgid_child(child)) != SUCCESS)
				return (ret);
		}
		// ft_dprintf(g_term_fd, "%sChild: pid: %d, ppid: %d, pgid: %d%s\n",
		// 	YELLOW, getpid(), getppid(), getpgid(getpid()), EOC);
	}
	else
	{
		if (g_job_ctrl->interactive)
		{
			// ft_printf("%sInteractive shell%s\n", BLUE, EOC);
			if ((ret = set_pgid_parent(child)) != SUCCESS)
				return (ret);
			// ft_dprintf(g_term_fd, "%sParent: pid: %d, ppid: %d, pgid: %d%s\n",
			// 	BLUE, child, getppid(), getpgid(child), EOC);
		}
	}

	// ft_dprintf(g_term_fd, "Fork: pid: %d\tppid: %d\tpgid: %d\n", getpid(), getppid(), getpgid(getpid()));
	return (child);
}

/*
** close_and_free
** After the execution, we have to close used pipe, to send a signal
** at the other side of the pipe
** free to not have any leaks
*/
static void		close_and_free(int curr_cmd, t_pipe *pipes, t_context *context)
{
	sh_reset_redirection(&context->redirections);
	sh_free_all(context->shell);
	if (pipes->nb_pipe > curr_cmd)
	{
		close(pipes->tab_pds[curr_cmd][OUTPUT]);
		close(STDOUT_FILENO);
	}
	if (curr_cmd > 0)
	{
		close(pipes->tab_pds[curr_cmd - 1][INPUT]);
		close(STDIN_FILENO);
	}
	free(pipes->tab_pds);
	free(pipes->tab_pid);
}

/*
** child_exec
** Apply pipe redirection and call next level on ast, simple_command
*/
static int 		child_exec(
	int curr_cmd, t_pipe *pipes, t_ast_node *node_to_execute, t_context *context)
{
	int 		ret;

	ret = 0;
	close_all_pipe_but_one(pipes->nb_pipe, curr_cmd, pipes->tab_pds);
	if (curr_cmd > 0)
		ret = dup2(pipes->tab_pds[curr_cmd - 1][INPUT], STDIN_FILENO);
	if (ret >= 0 && pipes->nb_pipe > curr_cmd)
		ret = dup2(pipes->tab_pds[curr_cmd][OUTPUT], STDOUT_FILENO);
	if (ret < 0)
		ret = ERROR;
	else
		ret = SUCCESS;
	if (ret == SUCCESS)
		ret = sh_traverse_simple_command(node_to_execute, context);
	close_and_free(curr_cmd, pipes, context);
	return (ret);
}

/*
** loop_pipe_exec
** This function look over the t_list pipe_sequece (grammar)
** fork and execute in the child process the current pipe sequence.
*/
static int 		loop_pipe_exec(
	int curr_cmd, t_pipe *pipes, t_list *lst_sequences, t_context *context)
{
	int 		ret;
	t_ast_node	*curr_sequence;

	curr_sequence = lst_sequences->content;
	if (curr_cmd == pipes->nb_cmd - 1 && lst_sequences->next == NULL)
	{
		if ((pipes->tab_pid[curr_cmd] = fork_for_pipe()) < 0)
			return (ERROR);
		else if (!pipes->tab_pid[curr_cmd])
			exit(child_exec(curr_cmd, pipes, curr_sequence, context));
	}
	else if (curr_sequence->symbol->id == sh_index(LEX_TOK_PIPE))
		return (loop_pipe_exec(curr_cmd, pipes, lst_sequences->next, context));
	else
	{
		if ((ret = loop_pipe_exec(
						curr_cmd + 1, pipes, lst_sequences->next, context)))
			return (ret);
		if ((pipes->tab_pid[curr_cmd] = fork_for_pipe()) < 0)
			return (ERROR);
		else if (!pipes->tab_pid[curr_cmd])
			exit(child_exec(curr_cmd, pipes, curr_sequence, context));
	}
	return (SUCCESS);
}

/*
** close_all_pipe
** As we create all pipe in the shell process,
** we need to close all of them, after fork all cmd,
** in the shell process
*/
static void		close_all_pipe(int nb_pipe, int **tab_pds)
{
	while (nb_pipe >= 0)
	{
		close(tab_pds[nb_pipe][INPUT]);
		close(tab_pds[nb_pipe][OUTPUT]);
		nb_pipe--;
	}
}

static int		create_all_pipe(int nb_pipe, t_pipe *pipes,
					t_list *lst_psequences, t_context *context)
{
	int	pds[2];
	int	ret;

	if (nb_pipe == -1)
	{
		ret = loop_pipe_exec(0, pipes, lst_psequences, context);
		close_all_pipe(pipes->nb_pipe - 1, pipes->tab_pds);
		return (ret);
	}
	if (pipe(pds))//checker si pas d'erreur au milieu d'une pipe sequence
	{
		sh_perror(SH_ERR1_PIPE, "execution commande pipe");
		return (ERROR);
	}
	pipes->tab_pds[nb_pipe] = pds;
	return (create_all_pipe(nb_pipe - 1, pipes, lst_psequences, context));
}

static int		get_last_ret_value(t_job *j)
{
	if (j == NULL || j->first_process == NULL)
		return (-1);
	ft_dprintf(g_term_fd, "Last ret value, pid: %d, ret: %#X (%d)\n", j->first_process->pid, j->first_process->status, j->first_process->status);
	return (j->first_process->status);
}

/*
** sh_execute_pipe
** This the execution file of pipe.
**
** The shell call all cmd of the pipe sequence and stock
** each of them and all pipe in a structure t_pipe.
** After fork for all cmd we wait for the end of all of them.
*/
int				sh_execute_pipe(t_ast_node *node, t_context *context)
{
	t_list		*lst_psequences;
	int 		ret;
	t_pipe		pipes;

	lst_psequences = node->children;
	pipes.nb_pipe = ft_lstlen(lst_psequences) / 2;
	pipes.nb_cmd = pipes.nb_pipe + 1;
	if ((pipes.tab_pds = malloc(pipes.nb_pipe * sizeof(int *))) == NULL)
		return (ERROR);
	if ((pipes.tab_pid = malloc(pipes.nb_cmd * sizeof(pid_t))) == NULL)
	{
		free(pipes.tab_pds);
		return (ERROR);
	}
	if (sh_pre_execution() != SUCCESS)
		return (FAILURE);
	if (!create_all_pipe(pipes.nb_pipe - 1, &pipes, lst_psequences, context))
	{
		if (g_job_ctrl->interactive)
		{
			if (g_job_ctrl->curr_job->foreground == 0)
					ret = job_put_in_bg(g_job_ctrl->curr_job, 0);
			else if (job_put_in_fg(g_job_ctrl->curr_job, 0, &ret) != SUCCESS)
				return (ret);
			if (sh_post_execution() != SUCCESS)
				return (FAILURE);
			if ((ret = get_last_ret_value(g_job_ctrl->curr_job)) < 0)
				return (ERROR);
			sh_env_update_ret_value_wait_result(context, ret);
			// ft_dprintf(g_term_fd, "%sRet in pipe: %#X (%d)\n%s",BLUE, context->shell->ret_value, context->shell->ret_value, EOC);
		}
		else
		{
			while (--pipes.nb_cmd >= 0)
				waitpid(pipes.tab_pid[pipes.nb_cmd], &ret, 0);
			sh_env_update_ret_value_wait_result(context, ret);
		}
	}
	free(pipes.tab_pds);
	free(pipes.tab_pid);
	return (SUCCESS);
}
