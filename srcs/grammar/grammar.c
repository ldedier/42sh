/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:19:01 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/29 16:06:22 by jdugoudr         ###   ########.fr       */
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
	{"UNKNOWN", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"|", 0, 1, NULL, &sh_traverse_default, &jobs_string_pipe},
	{"&", 0, 1, NULL, &sh_traverse_default, &jobs_string_and},
	{";", 0, 1, NULL, &sh_traverse_default, &jobs_string_semicol},
	// {";", 0, 1, NULL, &sh_traverse_semicol},
	{"<", 0, 1, NULL, &sh_traverse_default, &jobs_string_less},
	{">", 0, 1, NULL, &sh_traverse_default, &jobs_string_great},
	{"(", 0, 1, NULL, &sh_traverse_default, &jobs_string_opn_par},
	{")", 0, 1, NULL, &sh_traverse_default, &jobs_string_cls_par},
	{"{", 0, 1, NULL, &sh_traverse_default, &jobs_string_lbrace},
	{"}", 0, 1, NULL, &sh_traverse_default, &jobs_string_rbrace},
	{"!", 0, 1, NULL, &sh_traverse_default, &jobs_string_bang},
	{"$", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"\\", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"`", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"'", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"\"", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"TERM_SPACE", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"TERM_TAB", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"TERM_NEW_LINE", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"*", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"?", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"#", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"~", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"=", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"%", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"&&", 0, 1, NULL, &sh_traverse_default, &jobs_string_and_if},
	{"||", 0, 1, NULL, &sh_traverse_default, &jobs_string_or_if},
	{";;", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"<<", 0, 1, NULL, &sh_traverse_default, &jobs_string_dless},
	{">>", 0, 1, NULL, &sh_traverse_default, &jobs_string_dgreat},
	{"<&", 0, 1, NULL, &sh_traverse_default, &jobs_string_less_and},
	{">&", 0, 1, NULL, &sh_traverse_default, &jobs_string_great_and},
	{"<>", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"<<-", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{">|", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"if", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"then", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"else", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"elif", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"fi", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"do", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"done", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"case", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"esac", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"while", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"until", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"for", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"in", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"TERM_TOKEN", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"TERM_WORD", 0, 1, NULL, &sh_traverse_default, &jobs_string_word},
	{"TERM_ASSIGNMENT_WORD", 0, 1, NULL, &sh_traverse_assignment_word, &jobs_string_word},
	{"TERM_NAME", 0, 1, NULL, &sh_traverse_default, &jobs_string_word},
	{"TERM_IO_NUMBER", 0, 1, NULL, &sh_traverse_default, &jobs_string_word},
	{"_EOI_", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"ε", 0, 1, NULL, &sh_traverse_default, &jobs_string_default},
	{"PROGRAM", 0, 1, &sh_init_prod_program, &sh_traverse_default, &jobs_string_default},
	{"COMPLETE_COMMANDS", 0, 1, &sh_init_prod_complete_commands,
		&sh_traverse_default, &jobs_string_default},
	{"COMPLETE_COMMAND", 0, 1, &sh_init_prod_complete_command,
		&sh_traverse_default, &jobs_string_default},
	/*{"LIST", 1, 1, &sh_init_prod_list, &sh_traverse_list},*/
	{"LIST", 1, 1, &sh_init_prod_list, &sh_traverse_default, &jobs_string_default},
	/*{"AND_OR", 1, 1, &sh_init_prod_and_or, &sh_traverse_and_or},*/
	{"AND_OR", 1, 1, &sh_init_prod_and_or, &sh_traverse_default, &jobs_string_default},
	{"PIPELINE", 0, 1, &sh_init_prod_pipeline, &sh_traverse_default, &jobs_string_default},
	{"PIPE_SEQUENCE", 1, 1, &sh_init_prod_pipe_sequence,
		&sh_traverse_default, &jobs_string_default},
		// &sh_traverse_pipeline},
	{"COMMAND", 0, 1, &sh_init_prod_command, &sh_traverse_default, &jobs_string_default},
	{"COMPOUND_COMMAND", 0, 1, &sh_init_prod_compound_command,
		&sh_traverse_default, &jobs_string_default},
	{"SUBSHELL", 0, 1, &sh_init_prod_subshell, &sh_traverse_default, &jobs_string_default},
	{"COMPOUND_LIST", 0, 1, &sh_init_prod_compound_list, &sh_traverse_default, &jobs_string_default},
	{"TERM", 1, 1, &sh_init_prod_term, &sh_traverse_default, &jobs_string_default},
	{"FOR_CLAUSE", 0, 1, &sh_init_prod_for_clause, &sh_traverse_default, &jobs_string_default},
	{"NAME", 0, 1, &sh_init_prod_name, &sh_traverse_default, &jobs_string_word},
	{"IN", 0, 1, &sh_init_prod_in, &sh_traverse_default, &jobs_string_default},
	{"WORDLIST", 0, 1, &sh_init_prod_wordlist, &sh_traverse_default, &jobs_string_default},
	{"CASE_CLAUSE", 0, 1, &sh_init_prod_case_clause, &sh_traverse_default, &jobs_string_default},
	{"CASE_LIST_NS", 0, 1, &sh_init_prod_case_list_ns, &sh_traverse_default, &jobs_string_default},
	{"CASE_LIST", 0, 1, &sh_init_prod_case_list, &sh_traverse_default, &jobs_string_default},
	{"CASE_ITEM_NS", 0, 1, &sh_init_prod_case_item_ns, &sh_traverse_default, &jobs_string_default},
	{"CASE_ITEM", 0, 1, &sh_init_prod_case_item, &sh_traverse_default, &jobs_string_default},
	{"PATTERN", 0, 1, &sh_init_prod_pattern, &sh_traverse_default, &jobs_string_default},
	{"IF_CLAUSE", 0, 1, &sh_init_prod_if_clause, &sh_traverse_default, &jobs_string_default},
	{"ELSE_PART", 0, 1, &sh_init_prod_else_part, &sh_traverse_default, &jobs_string_default},
	{"WHILE_CLAUSE", 0, 1, &sh_init_prod_while_clause, &sh_traverse_default, &jobs_string_default},
	{"UNTIL_CLAUSE", 0, 1, &sh_init_prod_until_clause, &sh_traverse_default, &jobs_string_default},
	{"FUNCTION_DEFINITION", 0, 1, &sh_init_prod_function_definition,
		&sh_traverse_default, &jobs_string_default},
	{"FUNCTION_BODY", 0, 1, &sh_init_prod_function_body, &sh_traverse_default, &jobs_string_default},
	{"FNAME", 0, 1, &sh_init_prod_fname, &sh_traverse_default, &jobs_string_default},
	{"BRACE_GROUP", 0, 1, &sh_init_prod_brace_group, &sh_traverse_default, &jobs_string_default},
	{"DO_GROUP", 0, 1, &sh_init_prod_do_group, &sh_traverse_default, &jobs_string_default},
	{"SIMPLE_COMMAND", 0, 1, &sh_init_prod_simple_command,
		&sh_traverse_default, &jobs_string_default},
		// &sh_traverse_simple_command},
	{"CMD_NAME", 0, 1, &sh_init_prod_cmd_name, &sh_traverse_cmd_name, &jobs_string_word},
	{"CMD_WORD", 0, 1, &sh_init_prod_cmd_word, &sh_traverse_cmd_word, &jobs_string_word},
	{"CMD_PREFIX", 0, 1, &sh_init_prod_cmd_prefix, &sh_traverse_cmd_prefix, &jobs_string_default},
	{"CMD_SUFFIX", 1, 1, &sh_init_prod_cmd_suffix, &sh_traverse_cmd_suffix, &jobs_string_default},
	{"REDIRECT_LIST", 0, 1, &sh_init_prod_redirect_list, &sh_traverse_default, &jobs_string_default},
	{"IO_REDIRECT", 0, 1, &sh_init_prod_io_redirect, &sh_traverse_io_redirect, &jobs_string_default},
	{"IO_FILE", 0, 1, &sh_init_prod_io_file, &sh_traverse_io_file, &jobs_string_default},
	{"FILENAME", 0, 1, &sh_init_prod_filename, &sh_traverse_default, &jobs_string_default},
	{"IO_HERE", 0, 1, &sh_init_prod_io_here, &sh_traverse_io_here, &jobs_string_default},
	{"HERE_END", 0, 1, &sh_init_prod_here_end, &sh_traverse_default, &jobs_string_default},
	{"NEWLINE_LIST", 0, 1, &sh_init_prod_newline_list, &sh_traverse_default, &jobs_string_default},
	{"LINEBREAK", 0, 0, &sh_init_prod_linebreak, &sh_traverse_default, &jobs_string_default},
	{"SEPARATOR_OP", 0, 1, &sh_init_prod_separator_op, &sh_traverse_default, &jobs_string_default},
	{"SEPARATOR", 0, 1, &sh_init_prod_separator, &sh_traverse_default, &jobs_string_default},
	{"SEQUENTIAL_SEP", 0, 1, &sh_init_prod_sequential_sep, &sh_traverse_default, &jobs_string_default}
};
