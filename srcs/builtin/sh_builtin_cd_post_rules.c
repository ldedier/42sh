/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd_post_rules.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:33:24 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/30 15:03:50 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_builtin_cd_rule7(t_context *context, char **curpath, t_args *args)
{
	char	*pwd;

	if (args[CD_L_OPT].priority > args[CD_P_OPT].priority)
	{
		if (**curpath != '/')
		{
			pwd = sh_builtin_pwd_logical(context->env, context->fd[FD_ERR]);
			if (!pwd)
			{
				free(*curpath);
				return (ERROR);
			}
			if (!(*curpath = ft_strjoin_path_free(pwd, *curpath, 0x01 + 0x02)))
				return (sh_perror_fd(context->fd[FD_ERR],
					SH_ERR1_MALLOC, "sh_builtin_cd_rule7"));
		}
	}
	return (SUCCESS);
}

static int	sh_builtin_cd_rule8_2(char **curpath)
{
	int		len;
	char	*find;

	while ((find = ft_strstr(*curpath, "//")))
		ft_strdelchars(find, 0, 1);
	len = ft_strlen(*curpath);
	if (len > 1 && (*curpath)[len - 1] == '/')
		ft_strdelchar(*curpath, len - 1);
	return (SUCCESS);
}

int			sh_builtin_cd_rule8_1(char **curpath)
{
	char	*find;
	char	*end;
	char	*start;

	while ((find = ft_strnstr(*curpath, "./", 2)))
		ft_strdelchars(find, 0, 2);
	while ((find = ft_strstr(*curpath, "/./")))
		ft_strdelchars(find, 0, 2);
	while ((find = ft_strrnstr(*curpath, "/.", 2)))
		ft_strdelchars(find, 0, 2);
	while ((find = ft_strstr(*curpath, "/../")) || (find = ft_strrnstr(*curpath, "/..", 3)))
	{
		end = find + 3;
		if (find == *curpath)
				start = find;
		else
		{
				*find = 0;
				start = ft_strrchr(*curpath, '/');
				*find = '/';
				if (start == *curpath) //is it usefull ?
					start++;
		}
		ft_strdelchars(start, 0, end - start);
		ft_dprintf(2, "curpath (3) : %s\n", *curpath);
	}
	return (sh_builtin_cd_rule8_2(curpath));
}
