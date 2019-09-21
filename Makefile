# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 23:08:04 by ldedier           #+#    #+#              #
#    Updated: 2019/09/22 01:34:48 by mdaoud           ###   ########.fr        #
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
			  $(SRCDIR)/common \
			  $(SRCDIR)/exec \
			  $(SRCDIR)/expansions \
			  $(SRCDIR)/grammar \
			  $(SRCDIR)/job_control \
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
					sh_traverse_semicol.c sh_traverse_pipe_sequence.c \
					sh_traverse_assignment_word.c \
					sh_traverse_simple_command.c \
					sh_traverse_io_file.c \
					sh_traverse_cmd_name.c sh_traverse_cmd_word.c \
					sh_traverse_cmd_suffix.c sh_traverse_cmd_prefix.c \
					sh_traverse_io_redirect.c sh_traverse_io_here.c \
					sh_traverse_io_here_canonical.c \
					sh_traverse_and_or.c sh_traverse_list.c \
					sh_traverse_command.c

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
					selection.c sh_process_historic.c \
					heredoc.c research_historic.c \
					render_research.c heredoc_tools.c \
					free_command_line.c sh_delete_command.c \
					sh_process_shift_vertical.c \
					sh_process_shift_horizontal.c \
					update_prompt_keys.c sh_process_quoted.c \
					sh_get_cursor_position.c eof_percent.c \
					update_prompt_cwd.c keys_insert_tools.c keys_flush.c \
					keys_debug.c screen_tools.c get_char_len.c

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
					sh_traverse_tools_io_here_redirection.c

################################################################
########					COMMON						########
################################################################
SRCS			+=	main.c index.c init.c shell_tools.c \
					free_all.c init_term.c signals.c \
					set_signals.c canonical_mode.c historic.c home.c \
					init_tabs.c non_canonical_mode.c hash_binaries.c \
					check_term.c signal_tools.c

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
					sh_builtin_type.c sh_builtin_type_search_path.c sh_builtin_type_search.c\
					sh_builtin_verbose.c \
					sh_builtin_hash.c sh_builtin_set.c sh_builtin_unset.c \
					sh_builtin_export.c sh_builtin_hash_tools.c \
					sh_builtin_bonus.c sh_builtin_parser.c \
					sh_builtin_test.c sh_builtin_test_unary.c \
					sh_builtin_test_binary.c sh_builtin_jobs.c \
					sh_builtin_fg.c sh_builtin_bg.c

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
					sh_expansions_scan.c

################################################################
########					PERROR						########
################################################################
SRCS			 +=	sh_perror.c \
					sh_perror2.c \
					sh_perror_fd.c

################################################################
########				JOB_CONTROL						########
################################################################
SRCS			+=	jobs_init.c \
					jobs_add.c \
					jobs_print.c \
					process_add.c \
					str_tab_duplicate.c \
					str_tab_print.c \
					set_child_pgid.c \
					job_wait.c \
					job_put_in_bg.c \
					job_put_in_fg.c \
					job_is_completed.c \
					job_is_stopped.c \
					job_check_changes.c \
					job_free.c \
					job_print_status.c \
					job_notify.c \
					get_active_job.c

################################################################
########					INCLUDES					########
################################################################
INCLUDES		=	sh_21.h \
					sh_job_control.h \
					sh_lexer.h \
					sh_tokens.h \
					sh_parser.h \
					sh_grammar.h \
				  	sh_command_line.h \
					sh_autocompletion.h \
					sh_exec.h\
					sh_builtin.h \
					sh_traverse.h \
					sh_traverse_tools.h \
					sh_expansions.h \
					sh_perror.h

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
