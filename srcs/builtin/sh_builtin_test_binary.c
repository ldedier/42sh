/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_test_binary.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 16:21:46 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/08/07 15:40:45 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include <limits.h>

static intmax_t	ft_a_to_intmax(char *str, int *ret)
{
	uintmax_t	i;
	int			sym;

	i = 0;
	sym = 1;
	*ret = 0;
	while (*str == ' ' || *str == '\n' || *str == '\v'
			|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		sym = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
	{
		i = 10 * i + *str - '0';
		if ((sym > 0 && i > (uintmax_t)LONG_MAX)
				|| (sym < 0 && i > (uintmax_t)LONG_MAX + 1))
			break ;
		str++;
	}
	if (*str != '\0')
		*ret = 1;
	return (sym * i);
}

static int		check_params(char **params, intmax_t *nb1, intmax_t *nb2)
{
	int	ret;

	*nb1 = ft_a_to_intmax(params[0], &ret);
	if (ret)
	{
		ft_dprintf(2, "%s: test: %s: %s\n", SH_NAME, params[0], SH_BLT_INTEGER);
		return (BLT_TEST_ERROR);
	}
	*nb2 = ft_a_to_intmax(params[2], &ret);
	if (ret)
	{
		ft_dprintf(2, "%s: test: %s: %s\n", SH_NAME, params[2], SH_BLT_INTEGER);
		return (BLT_TEST_ERROR);
	}
	return (0);
}

static int		do_integer_binary(char **params, int ope)
{
	int			ret;
	intmax_t	nb1;
	intmax_t	nb2;

	ret = 0;
	if (check_params(params, &nb1, &nb2))
		return (BLT_TEST_ERROR);
	else if (ope == TEST_EQ)
		ret = (nb1 == nb2) ? 0 : 1;
	else if (ope == TEST_NE)
		ret = (nb1 != nb2) ? 0 : 1;
	else if (ope == TEST_GT)
		ret = (nb1 > nb2) ? 0 : 1;
	else if (ope == TEST_GE)
		ret = (nb1 >= nb2) ? 0 : 1;
	else if (ope == TEST_LT)
		ret = (nb1 < nb2) ? 0 : 1;
	else if (ope == TEST_LE)
		ret = (nb1 <= nb2) ? 0 : 1;
	return (ret);
}

int				sh_builtin_test_binary(char **params, int ope)
{
	int			ret;

	if (ope == TEST_EQU)
		ret = ft_strcmp(params[0], params[2]) == 0 ? 0 : 1;
	else if (ope == TEST_NOEQU)
		ret = ft_strcmp(params[0], params[2]) != 0 ? 0 : 1;
	else
		ret = do_integer_binary(params, ope);
	return (ret);
}
