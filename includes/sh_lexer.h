/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 11:08:27 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/22 11:50:38 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_LEXER_H
# define SH_LEXER_H

# include "libft.h"
# include "sh_tokens.h"

/*
** getpwnam: used in lexer_expansion_process_tilde.c
*/

# include <pwd.h>

/*
** Possible states for the lexer, returned by lexer functions
*/

# define LEX_OK			SUCCESS
# define LEX_ERR		ERROR
# define LEX_FAIL		FAILURE
# define LEX_CONTINUE	FAILURE + ERROR + SUCCESS + CTRL_D + 1
# define LEX_END		FAILURE + ERROR + SUCCESS + CTRL_D + 2

# define LEX_RULES_LEN	10

# define LEX_OPERATORS_CHARS_LEN	8
# define LEX_OPERATORS_CHARS		"|&;<>()\0"

typedef struct s_shell		t_shell;
typedef struct s_ast_node	t_ast_node;
typedef struct s_cfg		t_cfg;
typedef struct s_token		t_token;

typedef enum		e_lex_mode
{
	E_LEX_STANDARD,
	E_LEX_AUTOCOMPLETION,
}					t_lex_mode;

typedef enum		e_token_type
{
	E_TOKEN_TYPE_STANDARD,
	E_TOKEN_TYPE_COMMAND_SUBSTITUTION_PAR,
	E_TOKEN_TYPE_COMMAND_SUBSTITUTION_BACK,
	E_TOKEN_TYPE_PROCESS_SUBSTITUTION_INPUT,
	E_TOKEN_TYPE_PROCESS_SUBSTITUTION_OUTPUT,
	E_TOKEN_TYPE_ARITHMETIC_EXPANSION
}					t_token_type;

typedef struct		s_lexer
{
	char			c;
	char			*input;
	int				tok_start;
	int				tok_len;
	int				current_id;
	char			quoted;
	int				backslash;
	char			expansion;
	int				first_word;
	t_token			*brace;
	t_list			*list;
	t_dy_tab		*env;
	t_dy_tab		*vars;
	t_dy_tab		*alias;
	t_list			*alias_stack;
	int				next_alias_index;
	t_shell			*shell;
	t_lex_mode		mode;
}					t_lexer;

typedef struct		s_token_union
{
	int				ival;
	double			fval;
	char			*str;
}					t_token_union;

struct				s_token
{
	t_symbol_id		id;
	int				index;
	char			*value;
	long			lval;
	char			expansion;
	int				index_start;
	int				index_end;
	int				apply_heredoc_expansion;
	int				give_as_arg;
	t_ast_node		*ast_node;
};

/*
********************************************************************************
*/

/*
** sh_lexer.c
*/
int					sh_lexer_error_ret_value(t_lexer *lexer, int ret);
int					sh_lexer(
	char *input, t_list **tokens, t_shell *shell, t_lex_mode mode);

/*
** sh_lexer_alias.c
*/
int					sh_lexer_alias(t_lexer *lexer, char *value);

/*
** sh_lexer_reserved_words.c
*/
int					sh_lexer_reserved_words(
	t_lexer *lexer, t_token *token);

/*
** sh_lexer_rule_1.c
*/
int					sh_lexer_rule1(t_lexer *lexer);

/*
** sh_lexer_rule_10.c
*/
int					sh_lexer_rule10(t_lexer *lexer);

/*
** sh_lexer_rule_2.c
*/
int					sh_lexer_rule2(t_lexer *lexer);

/*
** sh_lexer_rule_3.c
*/
int					sh_lexer_rule3(t_lexer *lexer);

/*
** sh_lexer_rule_4.c
*/
int					sh_lexer_rule4(t_lexer *lexer);

/*
** sh_lexer_rule_5.c
*/
int					sh_lexer_rule5(t_lexer *lexer);

/*
** sh_lexer_rule_6.c
*/
int					sh_lexer_rule6(t_lexer *lexer);

/*
** sh_lexer_rule_7.c
*/
int					sh_lexer_rule7(t_lexer *lexer);

/*
** sh_lexer_rule_8.c
*/
int					sh_lexer_rule8(t_lexer *lexer);

/*
** sh_lexer_rule_9.c
*/
int					sh_lexer_rule9(t_lexer *lexer);

/*
** sh_lexer_rule_tools.c
*/
int					sh_lexer_is_operator_char(int c);
int					sh_lexer_check_operator(t_lexer *lexer);

/*
** t_lexer.c
*/
int					t_lexer_init(
	t_lexer *lexer, t_lex_mode mode, t_shell *shell, char *input);
void				t_lexer_reset(t_lexer *lexer, int tok_start);
int					t_lexer_add_token(t_lexer *lexer);
void				t_lexer_show(t_lexer *lexer);

/*
** t_token.c
*/
void				t_token_update_id(int id, t_token *token, t_cfg *cfg);
t_token				*t_token_new_ptr(int id, char *value, t_cfg *cfg);
t_token				*t_token_new(int id, char *value, t_cfg *cfg);
void				t_token_free(t_token *token);

/*
** t_token_list.c
*/
t_list				*t_token_node_new(int id, char *value, t_cfg *cfg);
void				t_token_free_list(t_list **head);
void				sh_free_token_lst(void *t, size_t dummy);
t_token				*sh_get_token_by_index(
	t_list *tokens, int index, t_list **prev);

/*
** t_token_show.c
*/
void				t_token_show(t_token *token);
void				t_token_show_id(int i);

#endif
