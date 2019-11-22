/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tokens.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 11:18:14 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/15 11:23:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TOKENS_H
# define SH_TOKENS_H

# define NB_PRODUCTIONS	112
# define NB_SYMBOLS 102
# define NB_TERMS	55

typedef enum		e_symbol_id
{
	LEX_TOK_UNKNOWN = 0,
	LEX_TOK_PIPE = '|',
	LEX_TOK_AND = '&',
	LEX_TOK_SEMICOL = ';',
	LEX_TOK_LESS = '<',
	LEX_TOK_GREAT = '>',
	LEX_TOK_OPN_PAR = '(',
	LEX_TOK_CLS_PAR = ')',
	LEX_TOK_LBRACE = '{',
	LEX_TOK_RBRACE = '}',
	LEX_TOK_BANG = '!',
	LEX_TOK_DOLLAR = '$',
	LEX_TOK_BACK_SLASH = '\\',
	LEX_TOK_QUOTE_BACK = '`',
	LEX_TOK_QUOTE_SPL = '\'',
	LEX_TOK_QUOTE_DBL = '"',
	LEX_TOK_SPACE = ' ',
	LEX_TOK_TAB = '\t',
	LEX_TOK_NEWLINE = '\n',
	LEX_TOK_STAR = '*',
	LEX_TOK_QUEST = '?',
	LEX_TOK_HASH = '#',
	LEX_TOK_TILD = '~',
	LEX_TOK_EQUAL = '=',
	LEX_TOK_PERCENT = '%',
	LEX_TOK_AND_IF = '&' + 0xff00 * '&',
	LEX_TOK_OR_IF = '|' + 0xff00 * '|',
	LEX_TOK_DSEMI = ';' + 0xff00 * ';',
	LEX_TOK_DLESS = '<' + 0xff00 * '<',
	LEX_TOK_DGREAT = '>' + 0xff00 * '>',
	LEX_TOK_LESSAND = '<' + 0xff00 * '&',
	LEX_TOK_GREATAND = '>' + 0xff00 * '&',
	LEX_TOK_LESSGREAT = '<' + 0xff00 * '>',
	LEX_TOK_DLESSDASH = '<' + 0xff00 * '<' + 0xff0000 * '-',
	LEX_TOK_CLOBBER = '>' + 0xff00 * '|',
	LEX_TOK_IF,
	LEX_TOK_THEN,
	LEX_TOK_ELSE,
	LEX_TOK_ELIF,
	LEX_TOK_FI,
	LEX_TOK_DO,
	LEX_TOK_DONE,
	LEX_TOK_CASE,
	LEX_TOK_ESAC,
	LEX_TOK_WHILE,
	LEX_TOK_UNTIL,
	LEX_TOK_FOR,
	LEX_TOK_IN,
	LEX_TOK_TOKEN = 130,
	LEX_TOK_WORD,
	LEX_TOK_ASSIGNMENT_WORD,
	LEX_TOK_NAME,
	LEX_TOK_IO_NUMBER,
	END_OF_INPUT,
	EPS,
	PROGRAM,
	COMPLETE_COMMANDS,
	COMPLETE_COMMAND,
	LIST,
	AND_OR,
	PIPELINE,
	PIPE_SEQUENCE,
	COMMAND,
	COMPOUND_COMMAND,
	SUBSHELL,
	COMPOUND_LIST,
	TERM,
	FOR_CLAUSE,
	NAME,
	IN,
	WORDLIST,
	CASE_CLAUSE,
	CASE_LIST_NS,
	CASE_LIST,
	CASE_ITEM_NS,
	CASE_ITEM,
	PATTERN,
	IF_CLAUSE,
	ELSE_PART,
	WHILE_CLAUSE,
	UNTIL_CLAUSE,
	FUNCTION_DEFINITION,
	FUNCTION_BODY,
	FNAME,
	BRACE_GROUP,
	DO_GROUP,
	SIMPLE_COMMAND,
	CMD_NAME,
	CMD_WORD,
	CMD_PREFIX,
	CMD_SUFFIX,
	REDIRECT_LIST,
	IO_REDIRECT,
	IO_FILE,
	FILENAME,
	IO_HERE,
	HERE_END,
	NEWLINE_LIST,
	LINEBREAK,
	SEPARATOR_OP,
	SEPARATOR,
	SEQUENTIAL_SEP
}					t_symbol_id;

#endif
