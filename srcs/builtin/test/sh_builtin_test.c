/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 10:07:10 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/13 05:17:30 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	get_flag(char *str)
{
	char	*flags[NB_FLAG_BINARY];
	int		i;

	i = 0;
	flags[0] = "=";
	flags[1] = "!=";
	flags[2] = "-eq";
	flags[3] = "-ne";
	flags[4] = "-gt";
	flags[5] = "-ge";
	flags[6] = "-lt";
	flags[7] = "-le";
	while (i < NB_FLAG_BINARY && ft_strcmp(str, flags[i]))
		i++;
	return (i);
}

static int	two_params(char **params)
{
	if (ft_strcmp(params[0], "!") == 0)
		return (sh_builtin_test_unary(params + 1, 1) ^ 1);
	return (sh_builtin_test_unary(params, 2));
}

static int	three_params(char **params)
{
	int	ope;
	int	ret;

	if ((ope = get_flag(params[1])) < NB_FLAG_BINARY)
		return (sh_builtin_test_binary(params, ope));
	else if (ft_strcmp(params[0], "!") == 0)
	{
		if ((ret = sh_builtin_test_unary(params + 1, 2)) > 1)
			return (ret);
		return (ret ^ 1);
	}
	else if (ft_strcmp(params[0], "(") == 0 && ft_strcmp(params[2], ")") == 0)
		return (sh_builtin_test_unary(params + 1, 1));
	ft_dprintf(2, "%s: test: %s: %s\n", SH_NAME, params[1], SH_BLT_BINAREXP);
	return (BLT_TEST_ERROR);
}

static int	four_params(char **params)
{
	int	ret;

	if (ft_strcmp(params[0], "!") == 0)
	{
		if ((ret = three_params(params + 1)) > 1)
			return (ret);
		return (ret ^ 1);
	}
	else if (ft_strcmp(params[0], "(") == 0 && ft_strcmp(params[3], ")") == 0)
		return (two_params(params + 1));
	ft_dprintf(2, "%s: test: %s\n", SH_NAME, SH_BLT_NOTWELLFORM);
	return (BLT_TEST_ERROR);
}

int			sh_builtin_test(t_context *context)
{
	int	i;
	int	ret;

	i = 0;
	while (context->params->tbl[i])
		i++;
	i--;
	if (i > 4)
	{
		ft_dprintf(2, "%s: test: %s\n", SH_NAME, SH_ERR1_TOO_MANY_ARGS);
		ret = BLT_TEST_ERROR;
	}
	else if (i == 0)
		return (1);
	else if (i == 1)
		ret = sh_builtin_test_unary((char **)context->params->tbl + 1, 1);
	else if (i == 2)
		ret = two_params((char **)context->params->tbl + 1);
	else if (i == 3)
		ret = three_params((char **)context->params->tbl + 1);
	else
		ret = four_params((char **)context->params->tbl + 1);
	return (ret);
}
