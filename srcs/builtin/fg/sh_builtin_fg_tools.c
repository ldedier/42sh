/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_fg_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 19:42:33 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/19 18:29:24 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			parse_fg_spec(char *str, int j_lst[], int *it)
{
	int		num;

	if (*it >= MAX_JOBS)
		return (sh_perror_err("fg", "maxim number of jobs exceeded"));
	if (str[1] == '\0' || str[1] == '+' || str[1] == '%')
	{
		j_lst[*it] = 0;
		(*it)++;
		return (SUCCESS);
	}
	if (str[1] == '-')
	{
		j_lst[*it] = -1;
		(*it)++;
		return (SUCCESS);
	}
	if (!ft_isdigit(str[1]))
		return (sh_perror2_err(str, "fg", "invalid job description"));
	num = ft_atoi(str + 1);
	j_lst[*it] = num;
	(*it)++;
	return (SUCCESS);
}

int			parse_fg_args(char **argv, int job_lst[])
{
	int		i;
	int		it;

	i = 1;
	it = 0;
	while (argv[i] != NULL)
	{
		if (argv[i][0] != '%')
			return (sh_perror2_err(argv[i], "fg", "invalid job description"));
		if (parse_fg_spec(argv[i], job_lst, &it) != SUCCESS)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

t_job		*fg_get_job_by_spec(int num)
{
	char	*msg;
	t_job	*j;

	if (num == 0)
	{
		if ((j = job_get_by_sign('+')) == NULL)
			sh_perror_err("fg", "no current job");
	}
	else if (num == -1)
	{
		if ((j = job_get_by_sign('-')) == NULL)
			sh_perror_err("fg", "no previous job");
	}
	else
	{
		if ((j = job_get_by_num(num)) == NULL)
		{
			msg = ft_strjoin_free("%", ft_itoa(num), 2);
			sh_perror2(msg, "fg", "no such job");
			free(msg);
		}
	}
	return (j);
}
