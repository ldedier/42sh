/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:05:14 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/13 04:44:00 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

#define PWD_USAGE			"[-LP]"
#define PWD_P_OPT			0
#define PWD_P_OPT_USAGE		"Find pathname without any symlinks"
#define PWD_L_OPT			1
#define PWD_L_OPT_USAGE		"Find pathname including symlinks (default)"

/*
** sh_builtin_pwd_physical:
**	Return an absolute pathname, that do not contain any symlinks.
**
**	returned Values :
**		NULL : Malloc error
**		Else : New malloced string, containing path
*/

char		*sh_builtin_pwd_physical(void)
{
	char	*pwd;

	if (!(pwd = getcwd(NULL, CWD_LEN)))
	{
		sh_perrorn("getcwd(3) error", "sh_builtin_pwd_logical");
		return (NULL);
	}
	return (pwd);
}

/*
** sh_builtin_pwd_logical:
**	Return an absolute pathname, not containing any dot or dot-dot.
**	Symlinks may appear in the path.
**	Print error messages if needed.
**
**	returned Values :
**		NULL : Malloc error
**		Else : New malloced string, containing path
*/

char		*sh_builtin_pwd_logical(t_dy_tab *env)
{
	char	*pwd;

	pwd = sh_vars_get_value(env, NULL, "PWD");
	if (pwd && *pwd == '/' && !ft_strchr(pwd, '.'))
	{
		if (!(pwd = ft_strdup(pwd)))
			return (sh_perrorn(SH_ERR1_MALLOC, "sh_builtin_pwd_logical"));
		return (pwd);
	}
	else
		return (sh_builtin_pwd_physical());
}

static void	sh_builtin_pwd_init_args(t_args *args)
{
	const t_args model[] = {
		{E_ARGS_BOOL, 'P', NULL, NULL, PWD_P_OPT_USAGE, 0},
		{E_ARGS_BOOL, 'L', NULL, NULL, PWD_L_OPT_USAGE, 0},
		{E_ARGS_END, 0, NULL, NULL, NULL, 0},
	};

	ft_memcpy(args, model, sizeof(model));
}

/*
** sh_builtin_pwd:
**	Function called as the pwd builtin. First options are parsed,
**	Then it use the pwd "api" to get the path, depending on given options.
**
**	returned Values :
**		FAILURE : malloc error
**		ERROR : invalid option detected (print usage)
**		SUCCESS : Path had been printed
*/

int			sh_builtin_pwd(t_context *context)
{
	int		index;
	char	**argv;
	char	*pwd;
	t_args	args[3];

	sh_builtin_pwd_init_args(args);
	argv = (char**)context->params->tbl;
	if (sh_builtin_parser(ft_strtab_len(argv), argv, args, &index))
		return (sh_builtin_usage(args, argv[0], PWD_USAGE, context));
	if (write(FD_OUT, NULL, 0))
	{
		return (sh_perror2_err("write error",
			"export", SH_ERR1_BAD_FD));
	}
	if (args[PWD_P_OPT].value
		&& args[PWD_P_OPT].priority > args[PWD_L_OPT].priority)
		pwd = sh_builtin_pwd_physical();
	else
		pwd = sh_builtin_pwd_logical(context->env);
	if (!pwd)
		return (FAILURE);
	ft_putstrn(pwd);
	free(pwd);
	return (SUCCESS);
}
