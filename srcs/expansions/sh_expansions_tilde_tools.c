/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_tilde_tools.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 21:05:08 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/16 21:40:06 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

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
	struct passwd	*passwd;
	char			*buf;

	if (BONUS_TILDE_EXP)
	{
		buf = ft_strndup(exp->original + 1, ft_strlen(exp->original) - 1);
		if (!buf)
			return (sh_perror(SH_ERR1_MALLOC, "expansion_process_tilde (3)"));
		if ((passwd = getpwnam(buf)))
			exp->res = ft_dy_str_new_str(passwd->pw_dir);
		else
			exp->res = ft_dy_str_new_str(exp->original);
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
	char	*buffer;

	if (!exp->original[1] || ft_iswhite(exp->original[1])
			|| exp->original[1] == '/' || exp->original[1] == ':')
	{
		if (!(home = sh_vars_get_value(context->env, NULL, "HOME")))
			return (sh_perror_err(SH_ERR1_ENV_NOT_SET, "HOME"));
		if (!(buffer = ft_strrep_pattern_free(
						exp->original, home, "~", 0)))
			return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_tilde (2)"));
		if (!(exp->res = ft_dy_str_new_ptr(
			buffer, ft_strlen(buffer), ft_strlen(buffer) + 1)))
			return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_tilde (1)"));
		return (SUCCESS);
	}
	return (sh_expansions_tilde_process_bonus(context, exp));
}

static void	tilde_assignment_init(
	int *index, char *quoted, int *process, char *original)
{
	*index = ft_strchr(original, '=') - original;
	*quoted = 0;
	*process = 1;
}

static int	tilde_assignment_quotes(char *original, int *index, char *quoted)
{
	if (original[*index] == '\\' && original[*index + 1])
		(*index) += 1;
	else if (*quoted && original[*index] == *quoted)
		*quoted = 0;
	else if (original[*index] == '\'' || original[*index] == '\"')
		*quoted = original[*index];
	else
		return (0);
	return (1);
}

int			sh_expansions_tilde_assignment(
	char **input, t_context *context, t_dy_tab *quotes)
{
	int		index;
	char	*original;
	int		ret;
	char	quoted;
	int		process;

	original = *input;
	tilde_assignment_init(&index, &quoted, &process, original);
	while (original[index])
	{
		if (tilde_assignment_quotes(original, &index, &quoted))
			;
		else if (!quoted && original[index] == '~' && process)
		{
			if ((ret = sh_expansions_tilde(input, context, quotes, &index)))
				return (ret);
			original = *input;
			index--;
			process = 0;
		}
		else if (!quoted && original[index] == ':')
			process = 1;
		index++;
	}
	return (SUCCESS);
}
