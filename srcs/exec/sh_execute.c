#include "sh_21.h"
#include "sh_job_control.h"

/*
** For each process in the current job-
**	We add that process to the current job group.
** Current job is designated by the g_job_ctrl->curr_job.
** This needs to be done by both the child and the parent processe-
** 	in order to avoid any possible race-conditions.
** First process of each job is appointed as the group leader.
** Example: ls | wc ; echo done
** "ls" and "wc" are in the same process group (with "ls" as the leader)
** "echo" is in another process group (and it's its leader).
*/

static int	sh_exec_binaire(t_context *context)
{
	int			res;
	pid_t		cpid;

	if (sh_pre_execution() != SUCCESS)
		return (FAILURE);
	if (g_job_ctrl->job_added == 0)
	{
		jobs_add();
		g_job_ctrl->job_added = 1;
	}
	if ((cpid = fork()) == -1)
		return (sh_perror(SH_ERR1_FORK, "sh_process_process_execute"));
	if (cpid == 0)
	{
		cpid = getpid();
		set_child_pgid(cpid);
		if (g_job_ctrl->curr_job->foreground == 1)
			if (tcsetpgrp(g_job_ctrl->term_fd, g_job_ctrl->curr_job->pgid) < 0)
				exit(ERROR);
		sh_execute_binary(context);
	}
	else
	{
		ft_printf("Adding process: %d %s to job %d\n", cpid, context->path, g_job_ctrl->curr_job->number);
		process_add(context, cpid);
		set_child_pgid(cpid);
		if (g_job_ctrl->curr_job->foreground == 1)
			job_put_in_fg(g_job_ctrl->curr_job, 0, &res);
		else
			res = 0;
		g_job_ctrl->job_added = 0;
		sh_env_update_ret_value_wait_result(context, res);
		if (sh_post_execution() != SUCCESS)
			return (FAILURE);
		g_glob.command_line.interrupted = WIFSIGNALED(res);
		return (SUCCESS);
	}
	return (SUCCESS);
}

static int		sh_no_slash_cmd(t_context *context)
{
	if ((context->builtin = sh_builtin_find(context)))
		return (SUCCESS);
	if (sh_traverse_sc_search_in_hash(context) != SUCCESS)
	{
		if (sh_traverse_sc_search_in_path(context) == FAILURE)
			return (FAILURE);
	}
	if (context->path)
		return (SUCCESS);
	else
	{
		sh_perror_err(context->params->tbl[0], SH_ERR1_CMD_NOT_FOUND);
		return (SH_RET_CMD_NOT_FOUND);
	}
}

static int		sh_slash_cmd(t_context *context)
{
	if (!(context->path = ft_strdup(context->params->tbl[0])))
		return (sh_perror(SH_ERR1_MALLOC, "traverse_simple_command"));
	if (sh_traverse_sc_check_perm(context,
				context->params->tbl[0], context->params->tbl[0]) != SUCCESS)
		return (SH_RET_NO_PERM);
	return (SUCCESS);
}

int 	sh_execute_simple_command(t_context *context)
{
	int 	ret;

	ret = SUCCESS;
	if (!context->params->tbl || !context->params->tbl[0])
		return (SUCCESS);
	if (!ft_strchr(context->params->tbl[0], '/'))
		ret = sh_no_slash_cmd(context);
	else
		ret = sh_slash_cmd(context);
	if (ret == SUCCESS)
	{
		if (context->builtin)
			ret = sh_execute_builtin(context);
		else
			ret = sh_exec_binaire(context);
	}
	return (ret);
}