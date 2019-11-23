/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_tilde.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 13:56:29 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/23 15:12:57 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_expansions_tilde_detect:
**	Function used to detect valid tilde expansion.
**
** return :
**		-1 : String given is invalid
**		<0 : Lenght of the valid expansion detecteda
*/

int			sh_expansions_tilde_detect(char *start)
{
	int		i;

	i = 0;
	if (start[i] != '~')
		return (-1);
	while (start[i]
		&& !(ft_iswhite(start[i]) || start[i] == '/' || start[i] == ':'
		|| start[i] == '\\' || start[i] == '\'' || start[i] == '\"'))
		i++;
	return (i);
}

/*
** sh_expansions_init_tilde:
**	Try to fill type, expansion, original and process fields of a t_expansion
**	structure for tilde expansion.
**
**	Return Value:
**		FAILURE : malloc error
**		ERROR : expansion is invalid
**		SUCCESS : successfully filled expansion
*/

static int	sh_expansions_init_tilde(char *original, t_expansion *exp)
{
	char	*start;
	int		i;

	ft_bzero(exp, sizeof(t_expansion));
	start = original;
	if (start[0] != '~')
		return (ERROR);
	if ((i = sh_expansions_tilde_detect(start)) == -1)
		return (ERROR);
	if (!(exp->original = ft_strndup(start, i)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_exp_variable_detect_name (1)"));
	exp->expansion = NULL;
	exp->type = EXP_TILDE;
	exp->process = &sh_expansions_tilde_process;
	return (SUCCESS);
}

/*
** sh_expansions_tilde_replace:
**	Used to add quotes around the result in the new input, only if result
**	is different of the original input.
**	Thanks to that, tilde epansion result is not subject to field splitting.
**	Moreover, it update index value, using the result lenght.
**
**	Returned Values:
**		SUCCESS
**		FAILURE : malloc error
*/

static int	sh_expansions_tilde_replace(
	char **input, t_dy_tab *quotes, int *index, t_expansion *exp)
{
	int		ret;

	if (!ft_strequ(exp->res->str, exp->original))
	{
		if (ft_dy_str_add_index(exp->res, '\'', ft_strlen(exp->res->str)))
			return (FAILURE);
		if (ft_dy_str_add_index(exp->res, '\'', 0))
			return (FAILURE);
	}
	ret = sh_expansions_replace(exp, input, *index, (t_quote**)quotes->tbl);
	if (ret)
		return (ret);
	(*index) += ft_strlen(exp->res->str);
	return (SUCCESS);
}

/*
** sh_expansions_tilde:
**	Look for valid tilde prefix in *input, startint at *index.
**	If any was found, a t_expansion structure is filled (init_tilde).
**	This structure is used to determine the result (tilde_process).
**	The result is finally replacing the original expansion in *input.
**
**	Return Value:
**		FAILURE : malloc error
**		ERROR : expansion is invalid
**		SUCCESS : successfully filled expansion
*/

int			sh_expansions_tilde(
	char **input, t_context *context, t_dy_tab *quotes, int *index)
{
	t_expansion	exp;
	int			ret;
	char		*original;

	original = *input;
	if (!ft_strpbrk(original + *index, "~"))
		return (SUCCESS);
	if (sh_expansions_init_tilde(original + *index, &exp) != SUCCESS)
	{
		t_expansion_free_content(&exp);
		return (ERROR);
	}
	if (sh_verbose_expansion())
		ft_dprintf(2, "tilde expansion detected\n");
	if (sh_verbose_expansion())
		t_expansion_show(&exp);
	ret = sh_expansions_tilde_process(context, &exp);
	if (!ret)
		ret = sh_expansions_tilde_replace(input, quotes, index, &exp);
	t_expansion_free_content(&exp);
	return (ret);
}
