/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_parameter_str_removal.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:03:31 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/22 08:49:24 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	sh_expansions_parameter_hash_process(
	t_expansion *exp, char *param, char *word)
{
	char	*end;

	if (!param)
		exp->res = ft_dy_str_new_str("");
	else if (!word || !*word)
		exp->res = ft_dy_str_new_str(param);
	else
	{
		end = ft_strnstr(param, word, ft_strlen(word));
		if (!end)
			exp->res = ft_dy_str_new_str(param);
		else
			exp->res = ft_dy_str_new_str(param + ft_strlen(word));
	}
}

int			sh_expansions_parameter_hash(
	t_context *context, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;
	int		ret;

	param = sh_expansions_parameter_get_param(context, exp);
	word = NULL;
	if ((ret = sh_expansions_parameter_get_word(context, exp, format, &word)))
		return (ret);
	if (sh_globbing_substring_removal_get_word(param, &word, exp, format))
		return (FAILURE);
	if (sh_verbose_expansion())
		ft_dprintf(2, "param : %s <> word : %s (%s)\n", param, word, format);
	sh_expansions_parameter_hash_process(exp, param, word);
	if (word)
		ft_strdel(&word);
	if (!exp->res)
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_parameter_hash"));
	return (SUCCESS);
}

static void	sh_expansions_parameter_percent_process(
	t_expansion *exp, char *param, char *word)
{
	char	*end;
	char	save;

	if (!param)
		exp->res = ft_dy_str_new_str("");
	else if (!word || !*word)
		exp->res = ft_dy_str_new_str(param);
	else
	{
		end = ft_strrnstr(param, word, ft_strlen(word));
		if (!end)
			exp->res = ft_dy_str_new_str(param);
		else
		{
			save = *end;
			*end = 0;
			exp->res = ft_dy_str_new_str(param);
			*end = save;
		}
	}
}

int			sh_expansions_parameter_percent(
	t_context *context, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;
	int		ret;

	param = sh_expansions_parameter_get_param(context, exp);
	word = NULL;
	if ((ret = sh_expansions_parameter_get_word(context, exp, format, &word)))
		return (ret);
	if (sh_globbing_substring_removal_get_word(param, &word, exp, format))
		return (FAILURE);
	if (sh_verbose_expansion())
		ft_dprintf(2, "param : %s <> word : %s (%s)\n", param, word, format);
	sh_expansions_parameter_percent_process(exp, param, word);
	if (word)
		ft_strdel(&word);
	if (!exp->res)
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_parameter_hash"));
	return (SUCCESS);
}
