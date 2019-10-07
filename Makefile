# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 23:08:04 by ldedier           #+#    #+#              #
#    Updated: 2019/10/07 13:46:15 by jdugoudr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 42sh

CC		= gcc -g3

OS		= $(shell uname -s)

PWD = \"$(shell pwd)\"
ECHO = echo
MKDIR = mkdir

DEBUG ?= 0

SRCDIR   = srcs
OBJDIR   = objs/
BINDIR   = .
INCLUDESDIR = includes
LIBFTDIR = libft
PRINTFDIR = ft_printf

VPATH		= $(INCLUDESDIR) \
			  $(SRCDIR)/builtin \
			  $(SRCDIR)/command_line \
			  $(SRCDIR)/command_line/autocomplete \
			  $(SRCDIR)/command_line/shortcuts \
			  $(SRCDIR)/common \
			  $(SRCDIR)/exec \
			  $(SRCDIR)/expansions \
			  $(SRCDIR)/grammar \
			  $(SRCDIR)/lexer \
			  $(SRCDIR)/parser \
			  $(SRCDIR)/parser/productions \
			  $(SRCDIR)/perror \
			  $(SRCDIR)/traverse \
			  $(SRCDIR)/traverse_tools \
			  $(SRCDIR)/redirection \
			  $(SRCDIR)/vars


SPEED = -j1
LIBFT = $(LIBFTDIR)/libft.a

################################################################
########					GRAMMAR						########
################################################################
SRCS			 =	debug.c first_sets.c grammar.c init_cfg.c \
					first_sets_tools.c

################################################################
########					TRAVERSE					########
################################################################
SRCS			+=	sh_traverse.c sh_traverse_default.c \
					sh_traverse_semicol.c sh_traverse_pipe_line.c \
					sh_traverse_assignment_word.c \
					sh_traverse_simple_command.c \
					sh_traverse_io_file.c \
					sh_traverse_cmd_name.c sh_traverse_cmd_word.c \
					sh_traverse_cmd_suffix.c sh_traverse_cmd_prefix.c \
					sh_traverse_io_redirect.c sh_traverse_io_here.c \
					sh_traverse_io_here_canonical.c \
					sh_traverse_and_or.c sh_traverse_list.c \
					sh_traverse_command.c sh_traverse_subshell.c

################################################################
########				COMMAND_LINE					########
################################################################
SRCS			+=	keys.c cursor_motion.c edit_command.c \
					is_printable_utf8.c get_command.c \
					utf8_tools.c render_command_line.c \
					arrows.c home_end.c command_line.c \
					xy.c copy_paste_delete.c update_prompt.c \
					update_prompt_tools.c keys_insert.c \
					keys_others.c keys_ctrl.c cursor_tools.c \
					selection.c sh_process_history.c \
					heredoc.c research_history.c \
					render_research.c heredoc_tools.c \
					free_command_line.c sh_delete_command.c \
					sh_process_shift_vertical.c \
					sh_process_shift_horizontal.c \
					update_prompt_keys.c sh_process_quoted.c \
					sh_get_cursor_position.c eof_percent.c \
					update_prompt_cwd.c keys_insert_tools.c keys_flush.c \
					keys_debug.c screen_tools.c get_char_len.c \
					saves.c keys_readline.c
#sh_clipboard.c sh_command_line_tools.c
#					sh_clipboard_tools.c

################################################################
########				TRAVERSE_TOOLS					########
################################################################
SRCS			+=	sh_traverse_tools_browse.c \
					sh_traverse_tools_reset.c \
					sh_traverse_tools_debug.c \
					sh_traverse_tools_io_file.c \
					sh_traverse_tools_io_here_expansion.c \
					sh_traverse_tools_simple_command.c \
					sh_traverse_tools_simple_command_check_perm.c \
					sh_traverse_tools_get_heredoc.c \
					sh_traverse_tools_io_here_redirection.c \
					sh_get_separator.c

################################################################
########					COMMON						########
################################################################
SRCS			+=	main.c index.c init.c shell_tools.c \
					free_all.c init_term.c signals.c \
					set_signals.c canonical_mode.c history.c home.c \
					init_tabs.c non_canonical_mode.c hash_binaries.c \
					check_term.c signal_tools.c execute_command.c \
					t_entry.c sh_split_path.c

################################################################
########					PARSER						########
################################################################
SRCS			+=	parser.c print_ast.c compute_lr_automata.c \
					compute_lr_tables.c lr_parse.c compute_first_state.c \
					state.c compute_closure.c compute_transitions.c \
					init_parsing.c reduce.c reduce_tools.c free_parser.c \
					transitive_first_sets.c \
					free_node.c  field_splitting_tools.c\
					shift.c free_parser_tools.c \
					reduce_pop.c ast_node_tools.c parser_debug.c

################################################################
########					LEXER						########
################################################################
SRCS			 +=	sh_lexer.c \
					sh_lexer_rule_1.c \
					sh_lexer_rule_2.c \
					sh_lexer_rule_3.c \
					sh_lexer_rule_4.c \
					sh_lexer_rule_5.c \
					sh_lexer_rule_6.c \
					sh_lexer_rule_7.c \
					sh_lexer_rule_8.c \
					sh_lexer_rule_9.c \
					sh_lexer_rule_10.c \
					sh_lexer_reserved_words.c \
					sh_lexer_rule_tools.c t_lexer.c t_token.c \
					t_token_show.c t_token_list.c

################################################################
########					PRODUCTIONS					########
################################################################
SRCS			+=	sh_prod_and_or.c sh_prod_brace_group.c \
					sh_prod_case_clause.c sh_prod_case_item.c \
					sh_prod_case_item_ns.c sh_prod_case_list.c \
					sh_prod_case_list_ns.c sh_prod_cmd_name.c \
					sh_prod_cmd_prefix.c sh_prod_cmd_suffix.c \
					sh_prod_cmd_word.c sh_prod_command.c \
					sh_prod_complete_command.c sh_prod_compound_command.c \
					sh_prod_compound_list.c sh_prod_do_group.c \
					sh_prod_else_part.c sh_prod_filename.c \
					sh_prod_fname.c sh_prod_for_clause.c \
					sh_prod_function_body.c sh_prod_function_definition.c \
					sh_prod_here_end.c sh_prod_if_clause.c sh_prod_in.c \
					sh_prod_io_file.c sh_prod_io_here.c \
					sh_prod_io_redirect.c sh_prod_linebreak.c \
					sh_prod_list.c sh_prod_name.c sh_prod_newline_list.c \
					sh_prod_pattern.c sh_prod_pipe_sequence.c \
					sh_prod_pipeline.c sh_prod_program.c \
					sh_prod_redirect_list.c sh_prod_separator.c \
					sh_prod_separator_op.c sh_prod_sequential_sep.c \
					sh_prod_simple_command.c sh_prod_subshell.c \
					sh_prod_term.c sh_prod_until_clause.c \
					sh_prod_while_clause.c sh_prod_wordlist.c \
					sh_prod_complete_commands.c

################################################################
########					AUTOCOMPLETE				########
################################################################
SRCS			+=	add_choices_from_dir.c auto_completion.c \
					populate_choices.c populate_word_by_index.c \
					preprocess_choice_add.c arrow_tools.c \
					render_choices.c add_choices_builtins.c \
					left_arrow.c right_arrow.c arrows_vertical.c \
					fill_buffer.c render_choices_tools.c file_tables.c \
					fill_buffer_from_tables.c add_file_tools.c \
					auto_completion_tools.c escape.c \
					add_choices_from_expansions.c

################################################################
########					SHORTCUTS					########
################################################################
SRCS			+=	vshortcuts.c \
					sh_vshortcut_hashtag.c \
					sh_vs_motion_space.c \
					sh_vshortcut_v.c \
					sh_vshortcut_j.c \
					sh_vshortcut_k.c \
					sh_vs_motion_l.c \
					sh_vs_motion_h.c \
					sh_vs_motion_w.c \
					sh_vs_motion_w_maj.c \
					sh_vs_motion_e.c \
					sh_vs_motion_e_maj.c \
					sh_vs_motion_b.c \
					sh_vs_motion_b_maj.c \
					sh_vs_motion_caret.c \
					sh_vs_motion_dollar.c \
					sh_vs_motion_0.c \
					sh_vs_motion_pipe.c \
					sh_vs_motion_f.c \
					sh_vs_motion_f_maj.c \
					sh_vs_motion_t.c \
					sh_vs_motion_t_maj.c \
					sh_vs_motion_semicol.c \
					sh_vs_motion_comma.c \
					sh_vshortcut_a.c \
					sh_vshortcut_a_maj.c \
					sh_vshortcut_i.c \
					sh_vshortcut_i_maj.c \
					sh_vshortcut_r.c \
					sh_vshortcut_r_maj.c \
					sh_vshortcut_c.c \
					sh_vshortcut_c_maj.c \
					sh_vshortcut_s_maj.c \
					sh_vshortcut_x.c \
					sh_vshortcut_x_maj.c \
					sh_vshortcut_d.c \
					sh_vshortcut_d_maj.c \
					sh_vshortcut_y.c \
					sh_vshortcut_y_maj.c \
					sh_vshortcut_p.c \
					sh_vshortcut_p_maj.c \
					sh_vshortcut_u.c \
					sh_vshortcut_u_maj.c \
					sh_vim_options.c \
					alt_b.c \
					alt_f.c \
					alt_d.c \
					alt_t.c \
					ctrl_k.c \
					ctrl_u.c \
					ctrl_w.c \
					ctrl_t.c \
					ctrl_y.c \
					ctrl_x_x.c


################################################################
########						VARS					########
################################################################
SRCS			+=	sh_vars_tools_1.c sh_vars_tools_2.c \
					sh_verbose.c sh_verbose_check.c sh_env_tools.c \
					sh_env.c sh_env_save.c

################################################################
########						EXEC					########
################################################################
SRCS			+=	sh_execute.c \
					sh_execute_binary.c \
					sh_execute_builtin.c \
					sh_execute_pipe.c \
					sh_execute_prefix_postfix.c \
					t_context.c sh_debug.c \
					sh_execute_redirection.c

################################################################
########					REDIRECTION					########
################################################################
SRCS			+=	sh_add_redirection.c \
					sh_reset_redirection.c \
					sh_check_open_fd.c

################################################################
########						BUILTIN					########
################################################################
SRCS			+=	sh_builtin.c sh_builtin_pwd.c \
					sh_builtin_$(ECHO).c sh_builtin_exit.c \
					sh_builtin_cd.c sh_builtin_cd_pre_rules.c \
					sh_builtin_cd_post_rules.c \
					sh_builtin_cd_last_rules.c \
					sh_builtin_type.c sh_builtin_type_search_path.c \
					sh_builtin_type_search.c\
					sh_builtin_verbose.c \
					sh_builtin_set.c sh_builtin_unset.c \
					sh_builtin_export.c sh_builtin_export_show.c \
					sh_builtin_hash.c sh_builtin_hash_tools.c \
					sh_builtin_bonus.c sh_builtin_parser.c \
					sh_builtin_test.c sh_builtin_test_unary.c \
					sh_builtin_test_binary.c \
					sh_builtin_fc.c \
					sh_builtin_fc_l_synopsis.c \
					sh_builtin_fc_s_synopsis.c \
					sh_builtin_fc_default_synopsis.c \
					sh_builtin_fc_parse_operands.c \
					sh_builtin_fc_get_entry.c

################################################################
########						EXPANSION				########
################################################################
SRCS			 +=	sh_expansions.c \
					sh_expansions_parameter.c \
					sh_expansions_parameter_process.c \
					sh_expansions_parameter_tools.c \
					sh_expansions_tilde.c \
					sh_expansions_variable.c t_expansion.c \
					sh_expansions_process.c sh_expansions_replace.c \
					sh_expansions_field_splitting.c \
					sh_expansions_quote_removal.c \
					sh_expansions_scan.c \
					sh_expansions_history.c \
					t_quote.c

################################################################
########					PERROR						########
################################################################
SRCS			 +=	sh_perror.c \
					sh_perror2.c \

################################################################
########					INCLUDES					########
################################################################
INCLUDES			=	sh_21.h \
					sh_lexer.h \
					sh_tokens.h \
					sh_parser.h \
					sh_grammar.h \
				  	sh_command_line.h \
					sh_autocompletion.h \
					sh_expansions.h \
					sh_history.h \
					sh_exec.h\
					sh_builtin.h \
					sh_traverse.h \
					sh_traverse_tools.h \
					sh_expansions.h \
					sh_perror.h \
					sh_shortcuts.h \
					sh_redirection.h

OBJECTS			=	$(addprefix $(OBJDIR), $(SRCS:.c=.o))
INC 			=	-I $(INCLUDESDIR) -I $(LIBFTDIR) -I $(LIBFTDIR)/$(PRINTFDIR)

EOC = \033[0m
ifeq ($(OS),Linux)
	CFLAGS = -DPATH=$(PWD) $(INC)
	OK_COLOR = \033[1;32m
	FLAGS_COLOR = \033[1;34m
	#COMP_COLOR =
else
	CFLAGS = -DPATH=$(PWD) $(INC) -Wall -Werror -Wextra
	OK_COLOR = \x1b[32;01m
	#COMP_COLOR = \x1b[34;01m
	FLAGS_COLOR = \x1b[34;01m
#	COMP_COLOR =
endif

LFLAGS =	-L $(LIBFTDIR) -lft -ltermcap
#CFLAGS += --analyze

ifeq ($(DEBUG), 1)
	CFLAGS += -fsanitize=address
	CC += -g3
	SPEED = -j8
else
	SPEED = -j8
endif

all:
	@$(MAKE) -C $(LIBFTDIR) $(SPEED)
	@$(ECHO) "$(FLAGS_COLOR)Compiling with flags $(CFLAGS) $(EOC)"
	@$(MAKE) $(BINDIR)/$(NAME) $(SPEED)

debug:
	@$(MAKE) all DEBUG=1

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

$(BINDIR)/$(NAME): $(LIBFT) $(OBJDIR) $(OBJECTS)
	@$(CC) -o $@ $(OBJECTS) $(CFLAGS) $(LFLAGS)
	@$(ECHO) "$(OK_COLOR)$(NAME) linked with success !$(EOC)"

$(OBJDIR):
	@$(MKDIR) $@

$(OBJDIR)%.o: $(SRC_DIR)%.c $(INCLUDES)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@$(ECHO) "${COMP_COLOR}$< ${EOC}"

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	@$(RM) $(OBJECTS)
	@$(RM) -r $(OBJDIR) && $(ECHO) "${OK_COLOR}Successfully cleaned $(NAME) objects files ${EOC}"

fclean: clean
	@$(MAKE) fclean -C $(LIBFTDIR)
	@$(RM) $(BINDIR)/$(NAME)  && $(ECHO) "${OK_COLOR}Successfully cleaned $(NAME) ${EOC}"

re: fclean all

rere:
	@$(RM) $(OBJECTS)
	@$(RM) -r $(OBJDIR)
	@$(RM) $(BINDIR)/$(NAME)
	@$(MAKE) all

os:
	@$(ECHO) $(OS)

.PHONY: all clean fclean re debug
