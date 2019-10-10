/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_proc_subst_out.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:29:58 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/10 03:14:58 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_expansions_proc_subst_out_detect(char *start)
{
    int     i;
    int     quoted;
    int     parenthesis;

	i = 0;
	if (start[0] != '<' && start[1] == '(')
        return (-1);
	quoted = 0;
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
        else if (!quoted && start[i] == ')')
            parenthesis--;
        i++;
    }
    if (!start[i] && parenthesis > 0)
        return (-1);
    return (i);
}

int			sh_expansions_proc_subst_out_fill(t_expansion *exp, char *start)
{
    int     i;

	i = sh_expansions_proc_subst_out_detect(start);
	if (i == -1)
		return (ERROR);
    if (!(exp->original = ft_strndup(start, i + 1)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_proc_subst_out_fill (1)"));
	if (!(exp->expansion = ft_strndup(start + 2, i - 3)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_proc_subst_out_fill (2)"));
	exp->type = EXP_PROC_SUBST_OUT;
	exp->process = &sh_expansions_proc_subst_out_process;
	return (SUCCESS);

}

int			sh_expansions_proc_subst_out_process(t_context *context,
				t_expansion *exp)
{
	// insert your code here
	// need to fill exp->res field (!! it is ft_dy_str)
	// This res will later replace the exp->original string in the token value
	(void)context;
	(void)exp;
	ft_dprintf(2, "proc out substitution detected : \n\t");
	t_expansion_show(exp);
	if (!(exp->res = ft_dy_str_new_str(exp->original)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_cmd_subs_process"));
	return (SUCCESS);
}
