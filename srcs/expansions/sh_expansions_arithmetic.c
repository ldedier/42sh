/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_arithmetic.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:08:09 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/26 08:46:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	arithmetic_detect_return_value(char *start, int i)
{
	if (!start[i])
		return (-1);
	return (i + 2);
}

int			sh_expansions_arithmetic_detect(char *str)
{
	int			i;
	int			quoted;
	int			parenthesis;

	if (str[0] != '$' || str[1] != '(' || str[2] != '(')
		return (-1);
	quoted = 0;
	parenthesis = 0;
	i = 2;
	while (str[++i])
	{
		if (str[i] == '\\' && str[i + 1])
			i += 1;
		else if (!quoted && (str[i] == '\'' || str[i] == '"'))
			quoted = str[i];
		else if (quoted && str[i] == quoted)
			quoted = 0;
		else if (!quoted && str[i] == '(')
			parenthesis += 1;
		else if (!quoted && !parenthesis && str[i] == ')' && str[i + 1] == ')')
			break ;
		else if (!quoted && str[i] == ')')
			parenthesis -= 1;
	}
	return (arithmetic_detect_return_value(str, i));
}

int			sh_expansions_arithmetic_fill(t_expansion *exp, char *start)
{
	int		i;

	if ((i = sh_expansions_arithmetic_detect(start)) == -1)
		return (ERROR);
	if (!(exp->original = ft_strndup(start, i)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_arithmetic_fill (1)"));
	if (!(exp->expansion = ft_strndup(start + 3, i - 3 - 2)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_arithmetic_fill (2)"));
	exp->type = EXP_ARITH;
	exp->process = &sh_expansions_arithmetic_process;
	return (SUCCESS);
}

static int	arithmetic_process_ret_value(t_expansion *exp, long ret)
{
	char	*buffer;

	if (!(buffer = ft_ltoa(ret, 10)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_arithmetic_process"));
	if (!(exp->res = ft_dy_str_new_ptr(buffer, 1, 1)))
	{
		free(buffer);
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_arithmetic_process"));
	}
	return (SUCCESS);
}

int			sh_expansions_arithmetic_process(t_context *context,
				t_expansion *exp)
{
	long		ret;
	t_dy_tab	*quotes;

	if (!(quotes = ft_dy_tab_new(1)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_arithmetic_process"));
	ret = sh_expansions_scan(&(exp->expansion), 0, context, quotes);
	ft_dy_tab_del_ptr(quotes);
	if (sh_verbose_expansion())
		ft_dprintf(2, "arithmetic expansion : %s\n", exp->expansion);
	if (ret)
		return (ret);
	ret = sh_execute_arithmetic(context, exp->expansion);
	if (context->arithmetic_error)
	{
		if (context->arithmetic_error == FAILURE)
			return (FAILURE);
		sh_env_update_ret_value(context->shell, 1);
		return (STOP_CMD_LINE);
	}
	return (arithmetic_process_ret_value(exp, ret));
}
