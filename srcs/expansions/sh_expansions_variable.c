/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_variable.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 13:38:26 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/21 13:28:14 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_expansions_variable_detect_special:
**		Used to detect special variables : as $? or $$.
**	This function is directly linked to
**	sh_expansions_parameter_detect_special_var,
**	You need to modify them together, cause they detect the same special vars,
**	not using the same method.
**
**	Returned Values:
**		1 : True
**		0 : False
*/

static int	sh_expansions_variable_detect_special(char *name)
{
	if (!name || !*name)
		return (0);
	if (ft_strnstr(name, "$$", 2))
		return (1);
	if (*name == '$')
		name++;
	if (*name == '?' || *name == '$' || *name == '#')
		return (1);
	return (0);
}

/*
** sh_expansions_variable_valid_name:
**	Check if an assignment is a valid POSIX name variable name is correct
**	In the shell command language, a word consisting solely of underscores,
**	digits, and alphabetics from the portable character set.
**	The first character of a name is not a digit.
**	Loop finish when it met any '=' sign.
**	(Used to detect valid assignment in lexer)
**
**	return Value : True or False
*/

int			sh_expansions_variable_valid_name(char *name)
{
	int		i;

	if (!ft_isalpha(*name) && !(*name == '_'))
		return (0);
	i = 0;
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/*
** sh_expansions_variable_detect:
**	Function used to detect valid variable expansion as $var.
**	Special parameters : $, #, ? are considered as good.
**	Else any valid variable name is considered as good,
**	(it can be preceded by a '$').
**
** return :
**		-1 : String given is invalid
**		>0 : Lenght of the valid expansion detecteda
*/

int			sh_expansions_variable_detect(char *start)
{
	int		i;

	i = 0;
	if (sh_expansions_variable_detect_special(start))
		return (2);
	if (start[0] == '$' && start[1] == '\0')
		return (0);
	if (start[0] == '$' && start[1] == '"' && start[2] == '\0')
		return (0);
	if (start[1] == '\\')
		return (0);
	if (*start == '$')
		i++;
	if (start[1] == '\'' && start[2] != '\'')
		return (1);
	if (start[1] == '"' && start[2] != '"')
		return (1);
	if (!(ft_isalpha(start[i]) || start[i] == '_'))
		return (-1);
	i++;
	while (start[i] && (ft_isalnum(start[i]) || start[i] == '_'))
		i++;
	return (i);
}

static int	sh_expansions_fill_invalid_vars(t_expansion *exp, char *start)
{
	char	*value;
	int		index;

	index = 1;
	while (start[index])
	{
		if (start[index] == '$' || start[index] == '\\'
			|| start[index] == '\'' || start[index] == '\"')
			break ;
		index++;
	}
	value = ft_strndup(start, index);
	if (!value)
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_fill_invalid_vars"));
	exp->type = EXP_VAR;
	exp->original = value;
	exp->expansion = value;
	exp->expansion = NULL;
	exp->process = &sh_expansions_variable_process;
	return (SUCCESS);
}

/*
** sh_expansions_variable_fill:
**	Try to fill type, expansion, original and process fields of a t_expansion
**	structure.
**	Conditon `if (i == 0)` is here to handle case of a solo $.
**	This is linked to the function sh_expansions_process and
**	sh_expansions_variable_detect.
**
**	Return Value:
**		FAILURE : malloc error
**		ERROR : expansion is invalid
**		SUCCESS : successfully filled expansion
*/

int			sh_expansions_variable_fill(t_expansion *exp, char *start)
{
	int		i;

	if ((i = sh_expansions_variable_detect(start)) == -1)
		return (sh_expansions_fill_invalid_vars(exp, start));
	if (i == 0)
	{
		exp->type = EXP_VAR;
		return (ERROR);
	}
	if (!(exp->original = ft_strndup(start, i)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_exp_variable_detect_name (1)"));
	if (!(exp->expansion = ft_strndup(start + 1, i - 1)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_exp_init_detect_pattern (2)"));
	exp->type = EXP_VAR;
	exp->process = &sh_expansions_variable_process;
	return (SUCCESS);
}
