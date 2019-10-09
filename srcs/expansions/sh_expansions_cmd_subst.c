/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_cmd_subst.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:29:58 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/09 15:33:09 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_expansions_cmd_subst_detect_backquotes(char *start)
{
    int     i;
    int     quoted;
    int     back_quote;

	i = 0;
	if (start[0] != '`')
        return (-1);
	quoted = 0;
    back_quote = 1;
    i++;
    while (start[i] && back_quote > 0)
    {
        if (start[i] == '\\' && start[i + 1])
            i += 1;
        else if (!quoted && (start[i] == '\'' || start[i] == '"'))
            quoted = start[i];
        else if (quoted && start[i] == quoted)
            quoted = 0;
        else if (!quoted && start[i] == '`')
            back_quote--;
        i++;
    }
    if (!start[i] && back_quote > 0)
        return (-1);
    return (i - 1);
}

int			sh_expansions_cmd_subst_detect_dollar(char *start)
{
    int     i;
    int     quoted;
    int     parenthesis;

	i = 0;
	quoted = 0;
    if (!(start = ft_strchr(start, '(')))
        return (-1);
    parenthesis = 1;
    i++;
    while (start[i] && parenthesis > 0)
    {
        if (start[i] == '\\' && start[i + 1])
            i += 1;
        else if (!quoted && (start[i] == '\'' || start[i] == '"'))
            quoted = start[i];
        else if (quoted && start[i] == quoted)
            quoted = 0;
        else if (!quoted && start[i] == '(')
            parenthesis++;
        else if (!quoted && start[i] == ')')
            parenthesis--;
		else
        i++;
    }
    if (!start[i] && parenthesis > 0)
        return (-1);
    return (i + 1);
}

int			sh_expansions_cmd_subst_fill(t_expansion *exp, char *start)
{
    int     i;
	int		pattern_len;

	i = -1;
	if (start[0] == '`')
	{
		i = sh_expansions_cmd_subst_detect_backquotes(start);
		pattern_len = 1;
	}
	else if (start[0] == '$' && start[1] == '(')
	{
		i = sh_expansions_cmd_subst_detect_dollar(start);
		pattern_len = 2;
	}
	if (i == -1)
		return (ERROR);
    if (!(exp->original = ft_strndup(start, i + 1)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_cmd_subst_fill (1)"));
	if (!(exp->expansion = ft_strndup(start + pattern_len, i - pattern_len)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_cmd_subst_fill (2)"));
	exp->type = EXP_CMD_SUBST;
	exp->process = &sh_expansions_cmd_subst_process;
	return (SUCCESS);

}

int			sh_expansions_cmd_subst_process(t_context *context,
				t_expansion *exp)
{
	// insert your code here
	// need to fill exp->res field (!! it is ft_dy_str)
	// This res will later replace the exp->original string in the token value
	(void)context;
	(void)exp;
	ft_dprintf(2, "command substitution detected : \n\t");
	t_expansion_show(exp);
	exp->res = ft_dy_str_new_str(""); // protect
	return (SUCCESS);
}
