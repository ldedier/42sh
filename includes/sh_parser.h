/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 12:31:41 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 11:04:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARSER_H
# define SH_PARSER_H

# include <stdarg.h>
# include "libft.h"
# include "sh_tokens.h"
# include "sh_grammar.h"
# include "sh_exec.h"

# define KNOWN_ITERATIONS 2

typedef struct s_ast_node	t_ast_node;
typedef struct s_exec		t_exec;
typedef struct s_shell		t_shell;
typedef struct s_stack_item	t_stack_item;

typedef struct		s_state
{
	t_list			*transitions;
	t_list			*items;
	t_list			*last_item_ptr;
	t_list			*items_by_productions[NB_PRODUCTIONS];
	int				index;
	int				parsed;
}					t_state;

typedef struct		s_transition
{
	t_symbol		*symbol;
	t_state			*state;
}					t_transition;

typedef struct		s_item
{
	t_production	*production;
	t_list			*progress;
	t_symbol		*lookahead;
	char			parsed;
}					t_item;

typedef enum		e_action_enum
{
	E_ACTION_ERROR,
	E_ACTION_ACCEPT,
	E_ACTION_SHIFT,
	E_ACTION_REDUCE
}					t_action_enum;

typedef union		u_action_union
{
	t_state			*state;
	t_production	*production;
}					t_action_union;

typedef struct		s_action
{
	t_action_enum	action_enum;
	t_action_union	action_union;
}					t_action;

typedef struct		s_ast_builder
{
	t_ast_node		**cst_node_ptr;
	t_ast_node		**ast_node_ptr;
	t_ast_node		*cst_node;
	t_ast_node		*ast_node;
	t_symbol		*symbol;
}					t_ast_builder;

struct				s_ast_node
{
	t_token			*token;
	t_symbol		*symbol;
	t_list			*children;
	t_ast_node		*relative;
	t_ast_node		*parent;
	t_ast_builder	*builder;
};

typedef enum		e_stack_enum
{
	E_STACK_AST_BUILDER,
	E_STACK_STATE_INDEX
}					t_stack_enum;

typedef union		u_stack_union
{
	t_state			*state;
	t_ast_builder	*ast_builder;
}					t_stack_union;

struct				s_stack_item
{
	t_stack_union	stack_union;
	t_stack_enum	stack_enum;
	char			transfered_ast_builder;
};

typedef struct		s_lr_parser
{
	t_list			*states;
	t_list			*last_state_ptr;
	t_hash_table	*states_by_items;
	t_action		**lr_tables;
	t_cfg			cfg;
	t_list			*stack;
	t_ast_node		**tmp_ast_root;
	t_ast_node		**tmp_cst_root;
	t_list			**tmp_tokens;
	t_list			**tmp_ast_builder_list;
	t_ast_node		**tmp_replacing_ast_node;
	t_symbol		*tmp_item;
	int				nb_states;
	int				index;

}					t_lr_parser;

/*
********************************************************************************
*/

/*
** ast_node_tools.c
*/
t_ast_node			*sh_new_ast_node(
	t_symbol_id id, char *value, t_cfg *cfg);
t_ast_node			*sh_add_to_ast_node(
	t_ast_node *node, t_symbol_id id, char *value, t_cfg *cfg);

/*
** compute_closure.c
*/
int					sh_add_closure_from_symbol_index(
	int i, int *changes, t_state *state, t_lr_parser *parser);
int					sh_add_to_closure(
	t_state *state,
	t_symbol *new_item,
	char *first_sets,
	t_lr_parser *parser);
int					sh_process_compute_closure_item(
	t_item *item, t_state *state, t_lr_parser *parser);
int					sh_process_compute_closure(
	t_state *state, t_lr_parser *parser);
int					sh_compute_closure(
	t_state *state, t_lr_parser *parser);

/*
** compute_closure_tools.c
*/
int					sh_is_in_state_item(
	t_production *production, t_state *state, t_symbol *lookahead);
t_item				*sh_new_item(
	t_production *production, t_symbol *lookahead);
int					sh_process_add_to_closure(
	t_production *production,
	t_state *state,
	t_symbol *lookahead,
	t_lr_parser *parser);
t_symbol			*sh_get_next_non_terminal(
	t_item *item, t_list **w_ptr);
void				sh_compute_first_sets_str_append(
	char *first_sets, t_cfg *cfg, t_list *w, t_symbol *append);

/*
** compute_first_state.c
*/
t_state				*sh_compute_first_state(t_lr_parser *parser);

/*
** compute_lr_automata.c
*/
int					sh_compute_state(t_state *state, t_lr_parser *parser);
int					sh_compute_states(t_lr_parser *parser);
int					sh_compute_lr_automata(t_lr_parser *parser);

/*
** compute_lr_tables.c
*/
t_action			**sh_create_tables(t_lr_parser *parser);
void				sh_fill_reduce(
	t_state *state, t_item *item, t_lr_parser *parser);
void				sh_fill_tables_by_transition(
	t_state *state, t_transition *transition, t_lr_parser *parser);
void				sh_fill_tables_by_state(
	t_state *state, t_lr_parser *parser);
int					sh_compute_lr_tables(t_lr_parser *parser);

/*
** compute_transitions.c
*/
int					sh_add_to_state_check(
	t_state *state, t_item *item, int *changes, t_lr_parser *parser);
int					sh_add_transition_item(
	t_item *item, t_state *state, t_lr_parser *parser, int *changes);
int					sh_compute_transitions(
	t_state *state, t_lr_parser *parser);

/*
** compute_transitions_allocate.c
*/
t_transition		*sh_new_transition(
	t_state *to, t_symbol *symbol);
t_item				*sh_new_item_advance(t_item *item);
t_state				*sh_new_parser_state_from_item(
	t_item *item, t_lr_parser *parser);

/*
** compute_transitions_tools.c
*/
int					sh_is_eligible_for_transition(
	t_state *state, t_item *item);
t_state				*sh_get_state_by_symbol(
	t_item *item, t_lr_parser *parser);
t_state				*sh_get_state_by_transition(
	t_state *state, t_symbol *symbol);
int					sh_add_transition(
	t_state *from, t_state *to, t_symbol *symbol);
int					sh_is_in_state_progress_item(
	t_state *state, t_item *item);

/*
** field_splitting_tools.c
*/
t_ast_node			*sh_add_word_to_ast(
	t_ast_node *previous_word, char *value, t_cfg *cfg);
void				sh_delete_node_from_parent(t_ast_node *node);

/*
** free_node.c
*/
void				sh_free_ast_node(t_ast_node **node, int node_to_free);
void				sh_free_ast_builder(t_ast_builder *ast_builder);

/*
** free_parser.c
*/
void				t_symbol_free(t_symbol *symbol);
void				sh_free_cfg(t_cfg *cfg);
void				sh_free_parser(t_lr_parser *parser);

/*
** free_parser_tools.c
*/
void				sh_free_lr_automata(t_lr_parser *parser);
void				sh_free_production(void *p, size_t dummy);

/*
** free_stack_item.c
*/
void				sh_free_stack_item_light(t_stack_item *stack_item);
void				sh_free_stack_item(t_stack_item *stack_item);
void				sh_free_stack_item_lst(void *si, size_t dummy);
void				sh_free_stack_item_lst_light(void *si, size_t dummy);

/*
** init_parsing.c
*/
int					sh_init_parsing(
	t_lr_parser *parser, t_cfg_initializer *cfgi);
int					sh_init_parsing_posix(t_lr_parser *parser);
int					sh_init_parsing_arithmetic(t_lr_parser *parser);

/*
** lr_parse.c
*/
t_stack_item		*new_stack_item(
	t_ast_builder *ast_builder, t_state *state);
int					process_lr_parser_ret(
	t_lr_parser *parser,
	t_action action,
	t_ast_node **ast_root,
	t_ast_node **cst_root);
int					process_lr_parse(
	t_lr_parser *parser,
	t_list **tokens,
	t_ast_node **ast_root,
	t_ast_node **cst_root);
int					sh_lr_parse(
	t_lr_parser *parser,
	t_list **tokens,
	t_ast_node **ast_root,
	t_ast_node **cst_root);

/*
** parser.c
*/
int					sh_is_term(t_symbol *symbol, t_cfg *cfg);
void				sh_populate_token(
	t_token *token, t_symbol_id id, int val);
int					sh_parse_token_list(
	t_lr_parser *parser,
	t_list **tokens,
	t_ast_node **ast_root,
	t_ast_node **cst_root);
int					sh_parser(
	t_shell *shell, t_lr_parser *parser, t_exec *res);

/*
** print_ast.c
*/
char				*sh_color_depth(int i);
void				sh_print_ast_child(
	int depth, int *j, t_cfg *cfg, t_ast_node *child);
void				sh_print_ast(t_ast_node *node, t_cfg *cfg, int depth);
void				sh_print_ast_root(t_ast_node *node, t_cfg *cfg);

/*
** print_lr_table.c
*/
void				sh_print_lr_table(t_lr_parser *parser);

/*
** print_parser.c
*/
void				sh_print_symbol_list(t_list *symbols, t_cfg *cfg);
void				sh_print_automata(t_lr_parser *parser, int depth);
void				sh_print_cfg(t_cfg *cfg);
void				sh_print_parser(t_lr_parser *parser, int depth);

/*
** print_parser_stack.c
*/
void				sh_print_ast_builder(
	t_ast_builder *ast_builder, t_cfg *cfg);
void				sh_print_stack_item(
	t_stack_item *stack_item, t_cfg *cfg);
void				sh_print_parser_state(
	t_lr_parser *parser, t_list *tokens);

/*
** print_production.c
*/
void				sh_print_production(
	t_production *production, t_cfg *cfg);
void				print_non_terminal_production(
	t_symbol *symbol, t_cfg *cfg);
void				print_non_terminals_productions(t_cfg *cfg);

/*
** print_sets.c
*/
void				sh_process_print_set(t_cfg *cfg, char *sets);
void				sh_print_first_set(t_cfg *cfg, t_symbol *symbol);
void				sh_print_follow_set(t_cfg *cfg, t_symbol *symbol);
void				print_follow_sets(t_cfg *cfg);
void				print_first_sets(t_cfg *cfg);

/*
** print_state.c
*/
void				sh_print_item(t_item *item, t_cfg *cfg);
void				sh_print_transition(
	t_transition *transition, t_cfg *cfg, int depth);
void				print_state_transitions(
	t_state *state, int depth, t_cfg *cfg);
void				sh_print_state(t_state *state, int depth, t_cfg *cfg);

/*
** productions/sh_prod_and_or.c
*/
int					sh_init_prod_and_or(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_brace_group.c
*/
int					sh_init_prod_brace_group(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_case_clause.c
*/
int					sh_init_prod_case_clause(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_case_item.c
*/
int					sh_init_prod_case_item(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_case_item_ns.c
*/
int					sh_init_prod_case_item_ns(
	t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_case_list.c
*/
int					sh_init_prod_case_list(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_case_list_ns.c
*/
int					sh_init_prod_case_list_ns(
	t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_cmd_name.c
*/
int					sh_init_prod_cmd_name(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_cmd_prefix.c
*/
int					sh_init_prod_cmd_prefix(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_cmd_suffix.c
*/
int					sh_init_prod_cmd_suffix(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_cmd_word.c
*/
int					sh_init_prod_cmd_word(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_command.c
*/
int					sh_init_prod_command(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_complete_command.c
*/
int					sh_init_prod_complete_command(
	t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_complete_commands.c
*/
int					sh_init_prod_complete_commands(
	t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_compound_command.c
*/
int					sh_init_prod_compound_command(
	t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_compound_list.c
*/
int					sh_init_prod_compound_list(
	t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_do_group.c
*/
int					sh_init_prod_do_group(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_else_part.c
*/
int					sh_init_prod_else_part(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_filename.c
*/
int					sh_init_prod_filename(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_fname.c
*/
int					sh_init_prod_fname(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_for_clause.c
*/
int					sh_init_prod_for_clause(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_function_body.c
*/
int					sh_init_prod_function_body(
	t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_function_definition.c
*/
int					sh_init_prod_function_definition(
	t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_here_end.c
*/
int					sh_init_prod_here_end(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_if_clause.c
*/
int					sh_init_prod_if_clause(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_in.c
*/
int					sh_init_prod_in(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_io_file.c
*/
int					sh_init_prod_io_file(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_io_here.c
*/
int					sh_init_prod_io_here(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_io_redirect.c
*/
int					sh_init_prod_io_redirect(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_linebreak.c
*/
int					sh_init_prod_linebreak(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_list.c
*/
int					sh_init_prod_list(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_name.c
*/
int					sh_init_prod_name(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_newline_list.c
*/
int					sh_init_prod_newline_list(
	t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_pattern.c
*/
int					sh_init_prod_pattern(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_pipe_sequence.c
*/
int					sh_init_prod_pipe_sequence(
	t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_pipeline.c
*/
int					sh_init_prod_pipeline(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_program.c
*/
int					sh_init_prod_program(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_redirect_list.c
*/
int					sh_init_prod_redirect_list(
	t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_separator.c
*/
int					sh_init_prod_separator(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_separator_op.c
*/
int					sh_init_prod_separator_op(
	t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_sequential_sep.c
*/
int					sh_init_prod_sequential_sep(
	t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_simple_command.c
*/
int					sh_init_prod_simple_command(
	t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_subshell.c
*/
int					sh_init_prod_subshell(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_term.c
*/
int					sh_init_prod_term(t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_until_clause.c
*/
int					sh_init_prod_until_clause(
	t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_while_clause.c
*/
int					sh_init_prod_while_clause(
	t_cfg *cfg, t_symbol *symbol);

/*
** productions/sh_prod_wordlist.c
*/
int					sh_init_prod_wordlist(t_cfg *cfg, t_symbol *symbol);

/*
** reduce.c
*/
int					sh_process_reduce_add_to_ast(
	t_list *ast_builder_list,
	t_ast_builder *ast_builder,
	t_production *production,
	t_lr_parser *parser);
int					sh_process_reduce(
	t_production *production,
	t_lr_parser *parser,
	t_ast_node **ast_root,
	t_ast_node **cst_root);

/*
** reduce_pop.c
*/
int					sh_process_reduce_pop(
	t_production *production,
	t_lr_parser *parser,
	t_list **ast_builder_list,
	t_ast_node **replacing_ast_node);

/*
** reduce_tools.c
*/
void				sh_init_ast_node(
	t_ast_node *node,
	t_token *token,
	t_symbol *symbol,
	t_ast_node *relative);
void				sh_init_ast_nodes(
	t_ast_builder *ast_builder, t_token *token, t_symbol *symbol);
t_ast_builder		*sh_new_ast_builder(
	t_token *token, t_symbol *symbol);
int					sh_is_replacing(
	t_ast_builder *ast_builder, t_cfg *cfg);

/*
** shift.c
*/
int					sh_process_shift_adds_stack_item(
	t_lr_parser *parser,
	t_stack_item *stack_item_ast_builder,
	t_stack_item *stack_item_state);
int					sh_process_shift_adds(
	t_lr_parser *parser, t_ast_builder *ast_builder, t_state *state);
int					sh_process_shift(
	t_list **tokens, t_state *state, t_lr_parser *parser);

/*
** state.c
*/
unsigned long		hash_item_next(void *i);
unsigned long		hash_item(void *i);
int					sh_add_item_to_state(
	t_lr_parser *parser, t_state *state, t_item *item);
t_state				*sh_new_state(t_cfg *cfg);
void				sh_free_state(t_state *state, t_cfg *cfg);

/*
** transitive_first_sets.c
*/
void				sh_process_transitive_first_set(
	t_symbol *symbol, int index, int *changes);
void				sh_process_transitive_first_sets(
	t_symbol *symbol,
	t_symbol *prod_symbol,
	int *changes,
	t_cfg *cfg);
void				sh_process_transitive_first_set_2(
	char *first_sets, int index);
void				sh_process_transitive_first_sets_2(
	char *first_sets, t_symbol *prod_symbol, t_cfg *cfg);

#endif
