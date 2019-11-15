/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:41:27 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/15 05:47:20 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_perror(const char *error, const char *suffix)
{
	if (isatty(2))
	{
		if (suffix)
			ft_dprintf(2, "%s%s: %s: %s%s\n", SH_ERR_COLOR,
				SH_NAME, error, suffix, COLOR_END);
		else
			ft_dprintf(2, "%s%s: %s%s\n", SH_ERR_COLOR,
				SH_NAME, error, COLOR_END);
	}
	else
	{
		if (suffix)
			ft_dprintf(2, "%s: %s: %s\n", SH_NAME, error, suffix);
		else
			ft_dprintf(2, "%s: %s\n", SH_NAME, error);
	}
	return (FAILURE);
}

int		sh_perror_err(const char *error, const char *suffix)
{
	sh_perror(error, suffix);
	return (ERROR);
}

void	*sh_perrorn(const char *error, const char *suffix)
{
	sh_perror(error, suffix);
	return (NULL);
}

int		sh_perror_unexpected_eof(t_lexer *lexer)
{
	char	c;

	if (lexer->quoted == '\'' || lexer->quoted == '"')
		c = lexer->quoted;
	else if (lexer->quoted == '>' || lexer->quoted == '<' || lexer->quoted == '(')
		c = ')';
	else if (lexer->quoted == '{')
		c = '}';
	else if (lexer->quoted == '`')
		c = '`';
	else
		c = '\0';
	if (isatty(2))
		ft_putstr(SH_ERR_COLOR);
	if (c)
		ft_dprintf(2,
		"%s: unexpected EOF while looking for matching `%c'\n", SH_NAME, c);
	else
		ft_dprintf(2, "%s: unexpected end of file\n", SH_NAME);
	if (isatty(2))
		ft_putstr(EOC);
	return (FAILURE);
}
