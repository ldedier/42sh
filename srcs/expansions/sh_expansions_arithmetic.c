/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_arithmetic.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 21:55:20 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/19 08:20:30 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_expansions_arithmetic_detect(char *start)
{
    int     i;
    int     quoted;
	int		parenthesis;

	quoted = 0;
	if (start[0] != '$' || start[1] != '(' || start[2] != '(')
        return (-1);
    i = 3;
	parenthesis = 0;
    while (start[i])
    {
        if (start[i] == '\\' && start[i + 1])
            i += 1;
        else if (!quoted && (start[i] == '\'' || start[i] == '"'))
            quoted = start[i];
        else if (quoted && start[i] == quoted)
            quoted = 0;
		else if (!quoted && start[i] == '(')
			parenthesis += 1;
        else if (!quoted && !parenthesis && start[i] == ')' && start[i + 1] == ')')
            break ;
		else if (!quoted && start[i] == ')')
			parenthesis -= 1;
        i++;
    }
    if (!start[i])
        return (-1);
    return (i + 2);
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

int			sh_expansions_arithmetic_process(t_context *context,
				t_expansion *exp)
{
	long	ret;
	char	*buffer;

	if (!(exp->res = ft_dy_str_new_str(exp->expansion)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_arithmetic_process"));
	ret = sh_execute_arithmetic(context, exp->expansion);
	if (context->arithmetic_error)
	{
		if (context->arithmetic_error == FAILURE)
			return (FAILURE);
		sh_env_update_ret_value(context->shell, 1);
		return (STOP_CMD_LINE);
	}
	if (!(buffer = ft_ltoa(ret, 10)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_arithmetic_process"));
	if (!(exp->res = ft_dy_str_new_ptr(buffer, 1, 1)))
	{
		free(buffer);
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_arithmetic_process"));
	}
	return (SUCCESS);
}
