/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:19:01 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/20 09:52:03 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** describes posix grammar symbols
**
** 1: debug string
** 2: ability to replace the parent node in the ast
** 3: relevance in the grammar
** 4: productions init function
** 5: traverse function
*/

t_grammar_holder g_grammar[NB_SYMBOLS] = {
	{"UNKNOWN", 0, 1, NULL, &sh_traverse_default},
	{"|", 0, 1, NULL, &sh_traverse_default},
	{"&", 0, 1, NULL, &sh_traverse_default},
	{";", 0, 1, NULL, &sh_traverse_semicol},
	{"<", 0, 1, NULL, &sh_traverse_default},
	{">", 0, 1, NULL, &sh_traverse_default},
	{"(", 0, 1, NULL, &sh_traverse_default},
	{")", 0, 1, NULL, &sh_traverse_default},
	{"{", 0, 1, NULL, &sh_traverse_default},
	{"}", 0, 1, NULL, &sh_traverse_default},
	{"!", 0, 1, NULL, &sh_traverse_default},
	{"$", 0, 1, NULL, &sh_traverse_default},
	{"\\", 0, 1, NULL, &sh_traverse_default},
	{"`", 0, 1, NULL, &sh_traverse_default},
	{"'", 0, 1, NULL, &sh_traverse_default},
	{"\"", 0, 1, NULL, &sh_traverse_default},
	{"TERM_SPACE", 0, 1, NULL, &sh_traverse_default},
	{"TERM_TAB", 0, 1, NULL, &sh_traverse_default},
	{"TERM_NEW_LINE", 0, 1, NULL, &sh_traverse_default},
	{"*", 0, 1, NULL, &sh_traverse_default},
	{"?", 0, 1, NULL, &sh_traverse_default},
	{"#", 0, 1, NULL, &sh_traverse_default},
	{"~", 0, 1, NULL, &sh_traverse_default},
	{"=", 0, 1, NULL, &sh_traverse_default},
	{"%", 0, 1, NULL, &sh_traverse_default},
	{"&&", 0, 1, NULL, &sh_traverse_default},
	{"||", 0, 1, NULL, &sh_traverse_default},
	{";;", 0, 1, NULL, &sh_traverse_default},
	{"<<", 0, 1, NULL, &sh_traverse_default},
	{">>", 0, 1, NULL, &sh_traverse_default},
	{"<&", 0, 1, NULL, &sh_traverse_default},
	{">&", 0, 1, NULL, &sh_traverse_default},
	{"<>", 0, 1, NULL, &sh_traverse_default},
	{"<<-", 0, 1, NULL, &sh_traverse_default},
	{">|", 0, 1, NULL, &sh_traverse_default},
	{"if", 0, 1, NULL, &sh_traverse_default},
	{"then", 0, 1, NULL, &sh_traverse_default},
	{"else", 0, 1, NULL, &sh_traverse_default},
	{"elif", 0, 1, NULL, &sh_traverse_default},
	{"fi", 0, 1, NULL, &sh_traverse_default},
	{"do", 0, 1, NULL, &sh_traverse_default},
	{"done", 0, 1, NULL, &sh_traverse_default},
	{"case", 0, 1, NULL, &sh_traverse_default},
	{"esac", 0, 1, NULL, &sh_traverse_default},
	{"while", 0, 1, NULL, &sh_traverse_default},
	{"until", 0, 1, NULL, &sh_traverse_default},
	{"for", 0, 1, NULL, &sh_traverse_default},
	{"in", 0, 1, NULL, &sh_traverse_default},
	{"TERM_TOKEN", 0, 1, NULL, &sh_traverse_default},
	{"TERM_WORD", 0, 1, NULL, &sh_traverse_default},
	{"TERM_ASSIGNMENT_WORD", 0, 1, NULL, &sh_traverse_assignment_word},
	{"TERM_NAME", 0, 1, NULL, &sh_traverse_default},
	{"TERM_IO_NUMBER", 0, 1, NULL, &sh_traverse_default},
	{"_EOI_", 0, 1, NULL, &sh_traverse_default},
	{"ε", 0, 1, NULL, &sh_traverse_default},
	{"PROGRAM", 0, 1, &sh_init_prod_program, &sh_traverse_default},
	{"COMPLETE_COMMANDS", 0, 1, &sh_init_prod_complete_commands,
		&sh_traverse_default},
	{"COMPLETE_COMMAND", 0, 1, &sh_init_prod_complete_command,
		&sh_traverse_default},
	{"LIST", 1, 1, &sh_init_prod_list, &sh_traverse_list},
	{"AND_OR", 1, 1, &sh_init_prod_and_or, &sh_traverse_and_or},
	{"PIPELINE", 0, 1, &sh_init_prod_pipeline, &sh_traverse_default},
	{"PIPE_SEQUENCE", 1, 1, &sh_init_prod_pipe_sequence,
		&sh_traverse_pipe_sequence},
	{"COMMAND", 0, 1, &sh_init_prod_command, &sh_traverse_default},
	{"COMPOUND_COMMAND", 0, 1, &sh_init_prod_compound_command,
		&sh_traverse_default},
	{"SUBSHELL", 0, 1, &sh_init_prod_subshell, &sh_traverse_default},
	{"COMPOUND_LIST", 0, 1, &sh_init_prod_compound_list, &sh_traverse_default},
	{"TERM", 0, 1, &sh_init_prod_term, &sh_traverse_default},
	{"FOR_CLAUSE", 0, 1, &sh_init_prod_for_clause, &sh_traverse_default},
	{"NAME", 0, 1, &sh_init_prod_name, &sh_traverse_default},
	{"IN", 0, 1, &sh_init_prod_in, &sh_traverse_default},
	{"WORDLIST", 0, 1, &sh_init_prod_wordlist, &sh_traverse_default},
	{"CASE_CLAUSE", 0, 1, &sh_init_prod_case_clause, &sh_traverse_default},
	{"CASE_LIST_NS", 0, 1, &sh_init_prod_case_list_ns, &sh_traverse_default},
	{"CASE_LIST", 0, 1, &sh_init_prod_case_list, &sh_traverse_default},
	{"CASE_ITEM_NS", 0, 1, &sh_init_prod_case_item_ns, &sh_traverse_default},
	{"CASE_ITEM", 0, 1, &sh_init_prod_case_item, &sh_traverse_default},
	{"PATTERN", 0, 1, &sh_init_prod_pattern, &sh_traverse_default},
	{"IF_CLAUSE", 0, 1, &sh_init_prod_if_clause, &sh_traverse_default},
	{"ELSE_PART", 0, 1, &sh_init_prod_else_part, &sh_traverse_default},
	{"WHILE_CLAUSE", 0, 1, &sh_init_prod_while_clause, &sh_traverse_default},
	{"UNTIL_CLAUSE", 0, 1, &sh_init_prod_until_clause, &sh_traverse_default},
	{"FUNCTION_DEFINITION", 0, 1, &sh_init_prod_function_definition,
		&sh_traverse_default},
	{"FUNCTION_BODY", 0, 1, &sh_init_prod_function_body, &sh_traverse_default},
	{"FNAME", 0, 1, &sh_init_prod_fname, &sh_traverse_default},
	{"BRACE_GROUP", 0, 1, &sh_init_prod_brace_group, &sh_traverse_default},
	{"DO_GROUP", 0, 1, &sh_init_prod_do_group, &sh_traverse_default},
	{"SIMPLE_COMMAND", 0, 1, &sh_init_prod_simple_command,
		&sh_traverse_simple_command},
	{"CMD_NAME", 0, 1, &sh_init_prod_cmd_name, &sh_traverse_cmd_name},
	{"CMD_WORD", 0, 1, &sh_init_prod_cmd_word, &sh_traverse_cmd_word},
	{"CMD_PREFIX", 0, 1, &sh_init_prod_cmd_prefix, &sh_traverse_default},
	{"CMD_SUFFIX", 1, 1, &sh_init_prod_cmd_suffix, &sh_traverse_cmd_suffix},
	{"REDIRECT_LIST", 0, 1, &sh_init_prod_redirect_list, &sh_traverse_default},
	{"IO_REDIRECT", 0, 1, &sh_init_prod_io_redirect, &sh_traverse_io_redirect},
	{"IO_FILE", 0, 1, &sh_init_prod_io_file, &sh_traverse_io_file},
	{"FILENAME", 0, 1, &sh_init_prod_filename, &sh_traverse_default},
	{"IO_HERE", 0, 1, &sh_init_prod_io_here, &sh_traverse_io_here},
	{"HERE_END", 0, 1, &sh_init_prod_here_end, &sh_traverse_default},
	{"NEWLINE_LIST", 0, 1, &sh_init_prod_newline_list, &sh_traverse_default},
	{"LINEBREAK", 0, 0, &sh_init_prod_linebreak, &sh_traverse_default},
	{"SEPARATOR_OP", 0, 1, &sh_init_prod_separator_op, &sh_traverse_default},
	{"SEPARATOR", 0, 1, &sh_init_prod_separator, &sh_traverse_default},
	{"SEQUENTIAL_SEP", 0, 1, &sh_init_prod_sequential_sep, &sh_traverse_default}
};
