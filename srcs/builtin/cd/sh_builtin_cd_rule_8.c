/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd_rule_8.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:33:24 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/16 19:59:01 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	sh_builtin_cd_rule8_a(char **curpath)
{
	char	*find;

	while ((find = ft_strnstr(*curpath, "./", 2)))
		ft_strdelchars(find, 0, 2);
	while ((find = ft_strstr(*curpath, "/./")))
		ft_strdelchars(find, 0, 2);
	while ((find = ft_strrnstr(*curpath, "/.", 2)) && find != *curpath)
		ft_strdelchars(find, 0, 2);
	return ;
}

static void	sh_builtin_cd_rule8_b(char **curpath)
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
			*find = '/';
		}
		ft_strdelchars(start, 0, end - start);
	}
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
	return ;
}

/*
** sh_builtin_cd_rule8:
**	Check that file defined by curpath exists, and then simplify *curpath.
**	Proceed curpath simplifications in three times :
**		a - Delete all '.' and '/' separating next component if any.
**		b - Delete all '..' components with previous component in path (if any).
**		c - Simplify curpath by deleting any unecessary '/' (ex : "//foo//bar")
**
**	Returned Values:
**		ERROR : file designated by *curpath do no exists (Error message shown)
**		SUCCESS : Everything is fine
*/

int			sh_builtin_cd_rule8(char **curpath)
{
	sh_builtin_cd_rule8_a(curpath);
	if (sh_verbose_builtin())
		ft_dprintf(2, MAGENTA"cd : removed . : curpath = %s\n"EOC, *curpath);
	sh_builtin_cd_rule8_b(curpath);
	if (sh_verbose_builtin())
		ft_dprintf(2, MAGENTA"cd : removed .. : curpath = %s\n"EOC, *curpath);
	sh_builtin_cd_rule8_c(curpath);
	if (sh_verbose_builtin())
		ft_dprintf(2, MAGENTA"cd : removed // : curpath = %s\n"EOC, *curpath);
	return (SUCCESS);
}
