/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 14:52:02 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/14 05:41:15 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	sh_env_update_ret_value_treat_sig(t_context *context, int sig)
{
	if (sig == 1)
		sh_perror("Abort : 1", context->params->tbl[0]);
	else if (sig == 2)
		;
	else if (sig == 3)
		sh_perror("Quit : 3", context->params->tbl[0]);
	else if (sig == 4)
		sh_perror("Illegal instruction : 4", context->params->tbl[0]);
	else if (sig == 8)
		sh_perror("Floating point exception: 8", context->params->tbl[0]);
	else if (sig == 9)
		sh_perror("Killed: 9", context->params->tbl[0]);
	else if (sig == 10)
		sh_perror("Bus error", context->params->tbl[0]);
	else if (sig == 11)
		sh_perror("Segmentation fault", context->params->tbl[0]);

	sh_env_update_ret_value(context->shell, SH_RET_SIG_RECEIVED + sig);
	return ;
}

/*
** sh_env_update_ret_value_wait_result:
**	If not already set update the value of shell->ret_value.
**	res is considered as the value stored by a wait (2) function.
*/

void		sh_env_update_ret_value_wait_result(t_context *context, int res)
{
	t_shell		*shell;

	shell = context->shell;
	if (!shell->ret_value_set)
	{
		if (SH_RET_VALUE_SIG_RECEIVED(res))
		{
			// mdaoud: To handle stopped processes.
			if (WIFSTOPPED(res))
				sh_env_update_ret_value_treat_sig(context, WSTOPSIG(res));
			else
				sh_env_update_ret_value_treat_sig(
					context, SH_RET_VALUE_SIG_RECEIVED(res));
		}
		if (sh_verbose_exec())
		{
			ft_dprintf(2, COLOR_CYAN"Process signal sent : %d\n"COLOR_END,
			res & 0xff);
		}
	}
	sh_env_update_ret_value(shell, SH_RET_VALUE_EXIT_STATUS(res));
	return ;
}

/*
** sh_env_update_ret_value:
**	If not already set update the value of shell->ret_value.
*/

void		sh_env_update_ret_value(t_shell *shell, int res)
{
	if (!shell->ret_value_set)
	{
		shell->ret_value = res;
		shell->ret_value_set = 1;
		if (sh_verbose_exec())
			ft_dprintf(2, COLOR_CYAN"ret value set : %d\n"COLOR_END, res);
	}
	else
	{
		if (sh_verbose_exec())
		{
			ft_dprintf(2, COLOR_CYAN"ret value already set     : %d\n"COLOR_END,
			shell->ret_value);
			ft_dprintf(2, COLOR_CYAN"ret value tried to be set : %d\n"COLOR_END,
			res);
		}
	}
	return ;
}

/*
** sh_env_update_status_and_question:
**	Update $? env variable. It use shell->ret_value, if it had been set.
**
**	Returned Values:
**		ERROR : ret_value unset
**		FAILURE : malloc error
**		SUCCESS
*/

int			sh_env_update_question_mark(t_shell *shell)
{
	char	*str;
	int		res;

	if (!shell->ret_value_set)
		return (ERROR);
	shell->ret_value_set = 0;
	if (sh_verbose_exec())
		ft_dprintf(2, COLOR_CYAN"Updating ? <=> %d\n"COLOR_END,
		shell->ret_value);
	if (!(str = ft_itoa(shell->ret_value)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_env_update_question_mark"));
	res = sh_vars_assign_key_val(NULL, shell->vars, "?", str);
	free(str);
	return (res);
}

/*
** sh_env_update_ret_value_and_question:
**	Update status and $? in one function.
**
**	Returned Values:
**		FAILURE : malloc error
**		SUCCESS
*/

int			sh_env_update_ret_value_and_question(t_shell *shell, int res)
{
	sh_env_update_ret_value(shell, res);
	return (sh_env_update_question_mark(shell));
}
