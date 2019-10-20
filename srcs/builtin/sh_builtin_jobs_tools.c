/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_jobs_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:04:13 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/20 05:41:55 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"
#include "sh_builtin.h"
#include "string.h"

#define	JOBS_P	1
#define	JOBS_L	2

static int		parse_jobs_option(char *str, int *arg_end, int *res)
{
	int		i;

	// ft_dprintf(g_term_fd, "Parsing : %s\n", str);
	if (*arg_end)
		return (sh_perror_err("jobs: job not found", str));
	if (ft_strequ(str, "--") || ft_strequ(str, "-"))
	{
		*arg_end = 1;
		return (SUCCESS);
	}
	i = 0;
	while (str[++i])
	{
		if (str[i] == 'p')
			*res |= JOBS_P;
		else if (str[i] == 'l')
			*res |= JOBS_L;
		else
		{
			ft_dprintf(2, "%s: %s: -%c\n","jobs",SH_ERR2_INVALID_OPT, str[i]);
			ft_dprintf(2, "jobs: usage: jobs [-lp] [jobspec..]\n");
			return (ERROR);
		}
	}
	// ft_dprintf(g_term_fd, "opt: %d\n", *res);
	return (SUCCESS);
}

static int		parse_jobs_spec(char *str, int *arg_end, int j_lst[], int *it)
{
	int		num;

	*arg_end = 1;
	if (str[1] == '\0')
		return(sh_perror_err("jobs: no such job", str));
	num = ft_atoi(str + 1);
	// ft_dprintf(g_term_fd, "Atoi: %d\n", num);
	j_lst[*it] = num;
	(*it)++;
	return (SUCCESS);
}

int		parse_jobs_args(char **argv, int j_lst[], int *opt)
{
	int	i;
	int	it;
	int	arg_end;

	i = 0;
	it = 0;
	arg_end = 0;
	while (argv[++i])
	{
		if (argv[i][0] == '-')
		{
			if (parse_jobs_option(argv[i], &arg_end, opt) != SUCCESS)
				return (ERROR);
		}
		else if (argv[i][0] == '%')
		{
			if (parse_jobs_spec(argv[i], &arg_end, j_lst, &it) != SUCCESS)
				return (ERROR);
		}
		else
			return(sh_perror_err("jobs: no such job", argv[i]));
	}
	return (SUCCESS);
}

