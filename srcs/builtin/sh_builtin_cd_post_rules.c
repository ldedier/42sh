/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd_post_rules.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:33:24 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/10 08:54:34 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_builtin_cd_rule7:
**	Only if in logical mode. (Else execute rule 10)
**	If curpath is a relative path (do not start with '/'), set curpath to
**	concatenation of current working directory and curpath. A '/' is added
**	between them if needed.
**
**	Returned Values:
**		FAILURE
**		ERROR : Can't get current working directory (sh_builtin_pwd)
**		SUCCESS
*/

int			sh_builtin_cd_rule7(
	t_context *context, char **curpath, t_args *args)
{
	char	*pwd;

	if (args[CD_L_OPT].priority > args[CD_P_OPT].priority)
	{
		if (**curpath != '/')
		{
			pwd = sh_builtin_pwd_logical(context->env);
			if (!pwd)
			{
				free(*curpath);
				return (ERROR);
			}
			if (!(*curpath = ft_strjoin_path_free(pwd, *curpath, 0x01 + 0x02)))
				return (sh_perror(SH_ERR1_MALLOC, "sh_builtin_cd_rule7"));
		}
	}
	if (sh_verbose_builtin())
		ft_dprintf(2, MAGENTA"cd : after 7 : curpath = %s\n"EOC, *curpath);;
	return (SUCCESS);
}

static void	sh_builtin_cd_rule8_a(char **curpath)
{
	char	*find;

	while ((find = ft_strnstr(*curpath, "./", 2)))
		ft_strdelchars(find, 0, 2);
	while ((find = ft_strstr(*curpath, "/./")))
		ft_strdelchars(find, 0, 2);
	while ((find = ft_strrnstr(*curpath, "/.", 2)) && find != *curpath)
		ft_strdelchars(find, 0, 2);
	if (sh_verbose_builtin())
		ft_dprintf(2, MAGENTA"cd : removed . : curpath = %s\n"EOC, *curpath);;
	return ;
}

static int	sh_builtin_cd_rule8_b(char **curpath, char *param)
{
	char	*find;
	char	*end;
	char	*start;

	while (((find = ft_strstr(*curpath, "/../")))
		|| (find = ft_strrnstr(*curpath, "/..", 3)))
	{
		end = find + 3;
		if (find == *curpath && ft_strnstr(find, "/../", 4))
			start = find;
		else if (find == *curpath)
			break ;
		else
		{
			while (*find == '/' && find > *curpath)
				find--;
			find++;
			*find = 0;
			start = ft_strrchr(*curpath, '/');
			if (start == *curpath)
				start++;
			if (sh_builtin_cd_check_perms(*curpath, param))
				return (ERROR);
			*find = '/';
		}
		ft_strdelchars(start, 0, end - start);
	}
	if (sh_verbose_builtin())
		ft_dprintf(2, MAGENTA"cd : removed .. : curpath = %s\n"EOC, *curpath);
	return (SUCCESS);
}

static void	sh_builtin_cd_rule8_c(char **curpath)
{
	int		len;
	char	*find;

	while ((find = ft_strstr(*curpath, "//")))
		ft_strdelchars(find, 0, 1);
	len = ft_strlen(*curpath);
	if (len > 1 && (*curpath)[len - 1] == '/')
		ft_strdelchar(*curpath, len - 1);
	if (sh_verbose_builtin())
		ft_dprintf(2, MAGENTA"cd : removed // : curpath = %s\n"EOC, *curpath);
	return ;
}

/*
** sh_builtin_cd_rule8:
**	Proceed curpath simplifications in three times :
**		a - Delete all '.' and '/' separating next component if any.
**		b - Delete all '..' components with previous component in path (if any).
**		c - Simplify curpath by deleting any unecessary '/' (ex : "//foo//bar")
**
**	Returned Values:
**		ERROR : A file designated by curpath was invalid (cf rule 8b)
**		SUCCESS : Everything is fine
*/

int			sh_builtin_cd_rule8(char **curpath, char *param)
{
	sh_builtin_cd_rule8_a(curpath);
	if (sh_builtin_cd_rule8_b(curpath, param))
		return (ERROR);
	sh_builtin_cd_rule8_c(curpath);
	return (SUCCESS);
}
