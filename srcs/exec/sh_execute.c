#include "sh_21.h"

static int	sh_exec_binaire(t_context *context)
{
	int			res;
	pid_t		child;

	if (sh_pre_execution(context) != SUCCESS)
		return (FAILURE);
	if ((child = fork()) == -1)
		return (sh_perror(SH_ERR1_FORK, "sh_process_process_execute"));
	if (child == 0)
		sh_execute_binary(context);
	else
	{
		waitpid(child, &res, 0);
		sh_env_update_ret_value_wait_result(context, res);
		sh_process_execute_close_pipes(context);
		if (sh_post_execution() != SUCCESS)
			return (FAILURE);
		g_glob.command_line.interrupted = WIFSIGNALED(res);
		return (res >> 8);
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
	{
		sh_process_execute_close_pipes(context);
		return (sh_perror(SH_ERR1_MALLOC, "traverse_simple_command"));
	}
	if (sh_traverse_sc_check_perm(context,
				context->params->tbl[0], context->params->tbl[0]) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

int 	sh_execute_simple_command(t_context *context)
{
	int 	ret;

	ret = SUCCESS;
	//execute redirection
	// sh_process_execute_dup(context);
	//chercher commande (dans env)
	if (!context->params->tbl || !context->params->tbl[0])
		return (SUCCESS);
	if (!ft_strchr(context->params->tbl[0], '/'))
		ret = sh_no_slash_cmd(context);
	else
		ret = sh_slash_cmd(context);
	if (ret == ERROR || ret == FAILURE)
		sh_process_execute_close_pipes(context);
	else if (context->builtin)
		ret = sh_execute_builtin(context);
	else
		// ft_printf("binaire a exec.\n");
		ret = sh_exec_binaire(context);
	sh_process_execute_close_pipes(context);
	return (ret);
}
