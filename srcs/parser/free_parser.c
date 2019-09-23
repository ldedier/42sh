/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:19:31 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/22 11:30:29 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
void	sh_free_parser_trees(t_lr_parser *parser)
{
	sh_free_ast_node(&parser->ast_root, 1);
	sh_free_ast_node(&parser->cst_root, 1);
}
*/

void	sh_free_cfg(t_cfg *cfg)
{
	int i;

	i = 0;
	while (i < NB_SYMBOLS)
	{
		ft_lstdel(&cfg->symbols[i].productions, sh_free_production);
		i++;
	}
	ft_lstdel(&cfg->start_symbol.productions, sh_free_production);
}

/*
void	sh_clear_parser(t_lr_parser *parser)
{
	//sh_free_parser_trees(parser);
	ft_lstdel(&parser->stack, sh_free_stack_item_lst);
	//ft_lstdel(&parser->tokens, sh_free_token_lst);
}
*/
void	sh_free_parser(t_lr_parser *parser)
{
	int i;

//	sh_clear_parser(parser);
	sh_free_lr_automata(parser);
	ft_hash_table_del_ptr(parser->states_by_items);
	if (parser->lr_tables && parser->nb_states != -1)
	{
		i = 0;
		while (i < parser->nb_states)
		{
			free(parser->lr_tables[i]);
			i++;
		}
		free(parser->lr_tables);
	}
	sh_free_cfg(&parser->cfg);
}
