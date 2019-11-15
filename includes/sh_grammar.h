/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_grammar.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 12:43:07 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/29 14:07:42 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_GRAMMAR_H
# define SH_GRAMMAR_H

# include <stdarg.h>
# include "libft.h"
# include "sh_tokens.h"
# include "sh_lexer.h"

# define DEBUG_BUFFER	50

typedef struct s_ast_node	t_ast_node;
typedef struct s_context	t_context;
typedef struct s_shell		t_shell;
typedef struct s_grammar_holder		t_grammar_holder;

typedef struct		s_symbol
{
	t_list			*productions;
	int				id;
	char			*first_sets; //nb_terms
	char			*follow_sets; //nb_terms
	char			debug[DEBUG_BUFFER];
	char			relevant;
	char			replacing;
}					t_symbol;

typedef struct		s_production
{
	int				index;
	t_symbol		*from;
	t_list			*symbols;
}					t_production;

typedef struct		s_cfg
{
	t_symbol			start_symbol;
	t_symbol			*symbols; //nb_symbols
	t_production		*productions; //nb_productions
	int					nb_symbols;
	int					nb_productions;
	int					nb_terms;
	int					nb_noterms;
	t_grammar_holder	*grammar_holder;
}					t_cfg;

typedef struct			s_cfg_initializer
{
	int					nb_symbols;
	int					nb_productions;
	int					nb_terms;
	t_grammar_holder	*grammar_holder;
}						t_cfg_initializer;

typedef struct		s_grammar_holder
{
	char			*debug;
	char			replacing;
	char			relevant;
	int				(*init_prod)(t_cfg *, t_symbol *);
	int				(*traverse)(t_ast_node *this, t_context *context);
	int 			(*get_job_string)(t_ast_node *node, char **str);
}					t_grammar_holder;

t_grammar_holder	g_grammar[NB_SYMBOLS];

/*
********************************************************************************
*/

/*
** debug.c
*/
void				sh_print_symbol(t_symbol *symbol, t_cfg *cfg);
void				sh_print_token(t_token *token, t_cfg *cfg);
void				sh_print_token_list(t_list *list, t_cfg *cfg);

/*
** first_sets.c
*/
int					sh_add_to_first_sets_by_prod(
	t_symbol *symbol,
	t_production *production,
	int *changes,
	t_cfg *cfg);
int					sh_add_to_first_sets(t_symbol *symbol, t_cfg *cfg);
int					sh_process_first_sets(t_cfg *cfg);
void				sh_init_process_first_sets(
	t_symbol *symbol, t_cfg *cfg);
int					sh_compute_first_sets(t_cfg *cfg);

/*
** first_sets_tools.c
*/
int					has_eps_prod(t_symbol *symbol);

/*
** init_cfg.c
*/
int					sh_add_prod(
	t_symbol *symbol, t_cfg *cfg, int nb_symbols, ...);
int					init_start_symbol(t_cfg *cfg, t_symbol *symbol);
int					init_symbol(t_symbol *symbol, t_cfg *cfg, int index);
int					init_context_free_grammar(
	t_cfg *cfg, t_cfg_initializer *cfgi);

#endif
