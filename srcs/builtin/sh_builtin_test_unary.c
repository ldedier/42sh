/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_test_unary.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 10:15:48 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/08/07 15:41:51 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static int	get_flag(char *str)
{
	char	*flags[NB_FLAG_UNARY];
	int		i;

	i = 0;
	flags[0] = "-b";
	flags[1] = "-c";
	flags[2] = "-d";
	flags[3] = "-e";
	flags[4] = "-f";
	flags[5] = "-g";
	flags[6] = "-L";
	flags[7] = "-p";
	flags[8] = "-r";
	flags[9] = "-S";
	flags[10] = "-s";
	flags[11] = "-u";
	flags[12] = "-w";
	flags[13] = "-x";
	flags[14] = "-z";
	while (i < NB_FLAG_UNARY && ft_strcmp(str, flags[i]))
		i++;
	return (i);
}

static int	get_stat_cont_1(char *str, int ope, struct stat sb)
{
	int			ret;

	ret = 0;
	if (ope == TEST_L)
	{
		if (lstat(str, &sb) == -1)
			return (1);
		ret = (sb.st_mode & S_IFMT) == S_IFLNK ? 0 : 1;
	}
	else if (ope == TEST_P)
		ret = (sb.st_mode & S_IFMT) == S_IFIFO ? 0 : 1;
	else if (ope == TEST_R)
		ret = (sb.st_mode & S_IRUSR) != 0 ? 0 : 1;
	else if (ope == TEST_SS)
		ret = (sb.st_mode & S_IFMT) == S_IFSOCK ? 0 : 1;
	else if (ope == TEST_S)
		ret = sb.st_size == 0 ? 0 : 1;
	else if (ope == TEST_U)
		ret = (sb.st_mode & S_ISUID) != 0 ? 0 : 1;
	else if (ope == TEST_W)
		ret = (sb.st_mode & S_IWUSR) != 0 ? 0 : 1;
	else if (ope == TEST_X)
		ret = (sb.st_mode & S_IXUSR) != 0 ? 0 : 1;
	return (ret);
}

static int	get_stat(char *str, int ope)
{
	struct stat	sb;
	int			ret;

	if (stat(str, &sb) == -1)
		return (1);
	else if (ope == TEST_B)
		ret = (sb.st_mode & S_IFMT) == S_IFBLK ? 0 : 1;
	else if (ope == TEST_C)
		ret = (sb.st_mode & S_IFMT) == S_IFCHR ? 0 : 1;
	else if (ope == TEST_D)
		ret = (sb.st_mode & S_IFMT) == S_IFDIR ? 0 : 1;
	else if (ope == TEST_E)
		return (0);
	else if (ope == TEST_F)
		ret = (sb.st_mode & S_IFMT) == S_IFREG ? 0 : 1;
	else if (ope == TEST_G)
		ret = (sb.st_mode & S_ISGID) != 0 ? 0 : 1;
	else
		ret = get_stat_cont_1(str, ope, sb);
	return (ret);
}

int			sh_builtin_test_unary(char **params, int arg)
{
	int	ope;

	if (arg == 1)
	{
		if (!params[0][0])
			return (1);
		else
			return (0);
	}
	if ((ope = get_flag(params[0])) >= NB_FLAG_UNARY)
	{
		ft_dprintf(2, "%s: test: %s: %s\n", SH_NAME, params[0], SH_BLT_UNAREXP);
		return (BLT_TEST_ERROR);
	}
	if (ope == TEST_Z)
	{
		if (ft_strlen(params[1]))
			return (1);
		return (0);
	}
	else
		return (get_stat(params[1], ope));
}
