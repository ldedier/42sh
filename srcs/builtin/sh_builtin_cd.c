/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:43:29 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/26 16:32:37 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		sh_builtin_cd_print_errors(char *path, t_context *context)
{
	struct stat st;

	if (access(path, F_OK))
		sh_perror2_fd(context->fd[FD_ERR],
			SH_ERR2_NO_SUCH_FILE_OR_DIR, "cd", path);
	else
	{
		if (stat(path, &st) == -1)
			return (FAILURE);
		if (!S_ISDIR(st.st_mode))
			sh_perror2_fd(context->fd[FD_ERR], SH_ERR1_NOT_A_DIR, "cd", path);
		else if (access(path, X_OK))
			sh_perror2_fd(context->fd[FD_ERR], SH_ERR1_PERM_DENIED, "cd", path);
	}
	return (SUCCESS); // return ERROR ??
}

static int		sh_builtin_cd_process(char *path, t_cd_opt flag, t_context *context)
{
	char		old_pwd[CWD_LEN];

	if (!getcwd(old_pwd, CWD_LEN))
	{
		perror("getcwd");
		ft_printf("ca va pas\n");
		return (FAILURE);
	}
	if (chdir(path) != 0)
		return (sh_builtin_cd_print_errors(path, context));
	else if (ft_update_old_pwd(old_pwd, path, flag, context) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int		sh_builtin_cd_args(t_context *context, int flag, int i)
{
	char	*str;

	if (!ft_strcmp("-", context->params->tbl[i]))
	{
		if ((str = get_env_value((char **)context->env->tbl, "OLDPWD")))
		{
			if (sh_builtin_cd_process(str, flag, context) == FAILURE)
				return (FAILURE);
			return (sh_builtin_pwd(context));
		}
		else
			return (sh_perror2_fd(context->fd[FD_ERR],
				SH_ERR1_ENV_NOT_SET, "cd", "OLDPWD"));
	}
	else
		return (sh_builtin_cd_process(context->params->tbl[i], flag, context));
}

static int		sh_builtin_cd_home(t_context *context, int flag)
{
	char	*home_str;

	if ((home_str = get_env_value((char **)context->env->tbl, "HOME")))
		return (sh_builtin_cd_process(home_str, flag, context));
	else
	{
		sh_perror2_fd(context->fd[FD_ERR],
				SH_ERR1_ENV_NOT_SET, "cd", "HOME");
		return (ERROR);
	}
}

int				sh_builtin_cd(t_context *context)
{
	int		i;
	int		flag;

	flag = e_cd_opt_logic;
	i = 1;
	while (context->params->tbl[i])
	{
		if (!ft_strcmp(context->params->tbl[i], "-P"))
			flag = e_cd_opt_physic;
		else if (!ft_strcmp(context->params->tbl[i], "-L"))
			flag = e_cd_opt_logic;
		else
			return (sh_builtin_cd_args(context, flag, i));
		i++;
	}
	return (sh_builtin_cd_home(context, flag));
}
