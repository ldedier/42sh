/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_grammar.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 12:43:07 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/02 23:17:52 by jmartel          ###   ########.fr       */
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

typedef struct		s_symbol
{
	t_list			*productions;
	int				id;
	char			first_sets[NB_TERMS];
	char			follow_sets[NB_TERMS];
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
	t_symbol		start_symbol;
	t_symbol		symbols[NB_SYMBOLS];
	t_production	productions[NB_PRODUCTIONS];
}					t_cfg;

typedef struct		s_grammar_holder
{
	char			*debug;
	char			replacing;
	char			relevant;
	int				(*init_prod)(t_cfg *, t_symbol *);
	int				(*traverse)(t_ast_node *this, t_context *context);
}					t_grammar_holder;

t_grammar_holder	g_grammar[NB_SYMBOLS];

/*
********************************************************************************
*/

/*
** first_sets.c
*/
int					sh_add_to_first_sets_by_prod(
	t_symbol *symbol, t_production *production, int *changes);
int					sh_add_to_first_sets(t_symbol *symbol);
int					sh_process_first_sets(t_cfg *cfg);
void				sh_init_process_first_sets(t_symbol *symbol);
int					sh_compute_first_sets(t_cfg *cfg);

/*
** debug.c
*/
void				sh_print_symbol(t_symbol *symbol);
void				sh_print_token(t_token *token, t_cfg *cfg);
void				sh_print_token_list(t_list *list, t_cfg *cfg);

/*
** init_cfg.c
*/
int					sh_add_prod(
	t_symbol *symbol, t_cfg *cfg, int nb_symbols, ...);
int					init_start_symbol(t_cfg *cfg, t_symbol *symbol);
void				init_symbol(t_symbol *symbol, int index);
int					init_context_free_grammar(t_cfg *cfg);

/*
** first_sets_tools.c
*/
int					has_eps_prod(t_symbol *symbol);

#endif
