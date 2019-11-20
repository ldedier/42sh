/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_glob_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 07:30:48 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/20 10:38:05 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** check_for_final_slash:
**	If str finish with a '/' character, it add a REG_FINAL_SLASH t_regexp,
**	at the begining of last pattern list of regexp_tab.
**	In verbose mode it show the modified last regexp_list.
**
**	Returned Values:
**		SUCCESS
**		FAILURE : malloc error
*/

// static int	check_for_final_slash(char *str, t_list **regexp_tab, int i)
// {
// 	t_regexp	*regexp;
// 	t_list		*lst;

// 	if (str[ft_strlen(str) - 1] != '/')
// 		return (SUCCESS);
// 	if (!(regexp = malloc(sizeof(*regexp))))
// 		return (sh_perror(SH_ERR1_MALLOC, "check_for_final_slash (1)"));
// 	if (!(lst = ft_lstnew(regexp, sizeof(*regexp))))
// 	{
// 		free(regexp);
// 		return (sh_perror(SH_ERR1_MALLOC, "check_for_final_slash (2)"));
// 	}
// 	regexp->type = REG_FINAL_SLASH;
// 	regexp->len = 0;
// 	regexp->value = NULL;
// 	lst->content = regexp;
// 	lst->next = regexp_tab[i];
// 	regexp_tab[i] = lst;
// 	if (sh_verbose_globbing())
// 		t_regexp_show_list(regexp_tab[i]);
// 	return (SUCCESS);
// }

int			t_glob_lexer_add_str(t_glob_lexer *lexer)
{
	t_regexp	*regexp;
	char		*value;
	t_list		**regexp_list;

	if (!lexer->tok_len)
		return (SUCCESS);
	if (!(value = ft_strndup(lexer->input + lexer->tok_start, lexer->tok_len)))
		return (FAILURE);
	regexp_list = &((t_list**)lexer->regexp_tab->tbl)[lexer->regexp_tab_index];
	if (!(regexp = t_regexp_new_push(regexp_list)))
	{
		free(value);
		return (FAILURE);
	}
	regexp->type = REG_STR;
	regexp->value = value;
	regexp->len = ft_strlen(value);
	lexer->tok_start += regexp->len;
	lexer->tok_len = 0;
	if (sh_verbose_globbing())
		ft_dprintf(2, "\t\tdelimited new str : (%s)\n", regexp->value);
	return (SUCCESS);
}

static int	t_glob_lexer_init(t_glob_lexer *lexer, char *input,
	t_dy_tab **regexp_tab, t_dy_tab *quotes)
{
	int		len;

	ft_bzero(lexer, sizeof(*lexer));
		len = 0;
	while ((ft_strsep(&input, "/")))
		len++;
	if (!(*regexp_tab = ft_dy_tab_new(len + 1)))
		return (sh_perror(SH_ERR1_MALLOC, "t_glob_lexer_init (1)"));
	if (ft_dy_tab_add_ptr(*regexp_tab, NULL))
		return (sh_perror(SH_ERR1_MALLOC, "t_glob_lexer_init (2)"));
	lexer->regexp_tab = *regexp_tab;
	lexer->input = input;
	lexer->quotes = quotes;
	lexer->c = input[0];
	return (SUCCESS);
}

static int	sh_glob_lexer_run_rules(t_glob_lexer *lexer)
{
	int				ret;
	int				i;
	static int		(*rules[6]) (t_glob_lexer *) = {
		&sh_glob_lexer_rule_1, &sh_glob_lexer_rule_2, &sh_glob_lexer_rule_3,
		&sh_glob_lexer_rule_4, &sh_glob_lexer_rule_5, &sh_glob_lexer_rule_6 };

	i = 0;
	if (sh_verbose_globbing())
		ft_dprintf(2, CYAN"glob lexer in progress on :%.2c\n"EOC, lexer->c);
	ft_dprintf(2, "start : %d || len : %d\n", lexer->tok_start, lexer->tok_len);
	while ((ret = rules[i](lexer)) == LEX_CONTINUE && i < 6)
		i++;
	if (sh_verbose_globbing())
		ft_dprintf(2, COLOR_GREEN"\trule %2d applied\n"COLOR_END, i + 1);
	lexer->c = lexer->input[lexer->tok_start + lexer->tok_len];
	return (ret);
}

int			sh_glob_lexer(char *str, t_dy_tab **regexp_tab, t_dy_tab *quotes)
{
	t_glob_lexer	lexer;
	int				ret;

	if (t_glob_lexer_init(&lexer, str, regexp_tab, quotes))
		return (FAILURE);
	ret = LEX_OK;
	while (ret == LEX_OK)	
		ret = sh_glob_lexer_run_rules(&lexer);
	if (ret != LEX_END)
	{
		t_regexp_free_tab(regexp_tab);
		return (ret);
	}
	// free lexer ?
	return (SUCCESS);
	// return (check_for_final_slash(lexer.input, (t_list**)(*regexp_tab)->tbl, lexer.regexp_tab_index));
}
