/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_tilde.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 13:56:29 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/05 01:48:48 by jmartel          ###   ########.fr       */
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
		&& !(ft_iswhite(start[i]) || start[i] == '/' || start[i] == ':'))
		i++;
	return (i);
}

/*
** sh_expansions_tilde_process_bonus:
**	Bonus function to treat tilde expansion, replacing ~user/ by it's
**	home absolute path
**
**	return SUCESS or FAILURE
*/

static int	sh_expansions_tilde_process_bonus(
		t_context *context, t_expansion *exp)
{
	char			*buf;
	struct passwd	*passwd;

	if (BONUS_TILDE_EXP)
	{
		buf = ft_strndup(exp->original + 1, ft_strlen(exp->original) - 1);
		if (!buf)
			return (sh_perror(SH_ERR1_MALLOC, "expansion_process_tilde (3)"));
		if (!(passwd = getpwnam(buf)))
			exp->res = ft_dy_str_new_str(exp->original);
		else
			exp->res = ft_dy_str_new_str(passwd->pw_dir);
		free(buf);
	}
	else
		exp->res = ft_dy_str_new_str(exp->original);
	if (!(exp->res))
		return (sh_perror(SH_ERR1_MALLOC, "expansion_process_tilde (4)"));
	return (SUCCESS);
	(void)context;
}

/*
** sh_expansions_tilde_process:
**	Function called to fill the expansion's res field using informations given
**	in the t_expansion structure.
**	First condition treat ~/ or ~ format. Else bonus function is called
**	to treat  ~user/ format.
**
**	return Value:
**		FAILURE : malloc error
**		SUCCESS : Successfullly filled exp->res
*/

int			sh_expansions_tilde_process(t_context *context, t_expansion *exp)
{
	char	*home;

	if (!exp->original[1] || ft_iswhite(exp->original[1])
			|| exp->original[1] == '/' || exp->original[1] == ':')
	{
		if (!(home = sh_vars_get_value(context->env, NULL, "HOME")))
			return (sh_perror_err(SH_ERR1_ENV_NOT_SET, "HOME"));
		if (!(exp->res = (t_dy_str *)malloc(sizeof(t_dy_str))))
			return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_tilde (1)"));
		if (!(exp->res->str = ft_strrep_pattern_free(
						exp->original, home, "~", 0)))
			return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_tilde (2)"));
		return (SUCCESS);
	}
	return (sh_expansions_tilde_process_bonus(context, exp));
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
	if (!(start = ft_strpbrk(original, "~")))
		return (ERROR);
	if (start[0] != '~')
		return (ERROR);
	if ((i = sh_expansions_tilde_detect(start)) == -1)
		return (ERROR);
	if (!(exp->original = ft_strndup(start, i)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_exp_variable_detect_name (1)"));
	exp->expansion = NULL;
	exp->type = EXP_VAR;
	exp->process = &sh_expansions_tilde_process;
	return (SUCCESS);
}

/*
** sh_expansions_tilde:
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
		ret = sh_expansions_replace(&exp, input, *index, (t_quote**)quotes->tbl);
	(*index) += ft_strlen(exp.res->str);
	t_expansion_free_content(&exp);
	return (ret);
}

int			sh_expansions_tilde_assignment(
	char **input, t_context *context, t_dy_tab *quotes)
{
	int		index;
	char	*original;
	int		ret;

	original = *input;
	if (!(index = ft_strchr(original, '=') - original))
		return (ERROR);
	if (original[index] == '=' && original[index + 1] == '~')
	{
		index++;
		if ((ret = sh_expansions_tilde(input, context, quotes, &index)))
			return (ret);
		original = *input;
	}
	while (original[index])
	{
		if (original[index] == ':' && original[index + 1] == '~')
		{
			index++;
			if ((ret = sh_expansions_tilde(input, context, quotes, &index)))
				return (ret);
			index--;
			original = *input;
		}
		index++;
	}
	return (SUCCESS);
}
