# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 23:08:04 by ldedier           #+#    #+#              #
#    Updated: 2019/08/20 14:57:28 by ldedier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 42sh

CC		= gcc -g3

OS		= $(shell uname -s)

PWD = \"$(shell pwd)\"

DEBUG ?= 0

SRCDIR   = srcs
OBJDIR   = objs
BINDIR   = .
INCLUDESDIR = includes
LIBFTDIR = libft
PRINTFDIR = ft_printf

COMMON_DIR	= common
GRAM_DIR	= grammar
COMMANDLINE_DIR = command_line
PROD_DIR   = productions
LEXER_DIR	= lexer
PARSER_DIR	= parser
TRAV_DIR	= traverse
TRAVT_DIR	= traverse_tools
VARS_DIR	= vars
AUTO_DIR	= autocomplete
EXEC_DIR	= exec
BUILT_DIR	= builtin
EXP_DIR		= expansions
PERROR_DIR	= perror

SPEED = -j1
LIBFT = $(LIBFTDIR)/libft.a

OK_COLOR = \x1b[32;01m
#COMP_COLOR = \x1b[34;01m
FLAGS_COLOR = \x1b[34;01m
COMP_COLOR =
EOC = \033[0m

GRAM_SRCS_NO_PREFIX =	debug.c \
						first_sets.c \
						grammar.c \
						init_cfg.c \
						first_sets_tools.c

TRAV_SRCS_NO_PREFIX =	sh_traverse.c \
						sh_traverse_default.c \
						sh_traverse_semicol.c \
						sh_traverse_pipe_sequence.c \
						sh_traverse_pipe_sequence_execute.c \
						sh_traverse_assigment_word.c \
						sh_traverse_simple_command.c \
						sh_traverse_simple_command_tools.c \
						sh_traverse_simple_command_check_perm.c \
						sh_traverse_cmd_name.c \
						sh_traverse_cmd_word.c \
						sh_traverse_cmd_suffix.c \
						sh_traverse_io_redirect.c \
						sh_traverse_io_here.c \
						sh_traverse_io_here_canonical.c \
						sh_traverse_io_file.c \
						sh_traverse_io_file_tools.c \
						sh_traverse_and_or.c \
						sh_traverse_list.c

COMMANDLINE_SRCS_NO_PREFIX = keys.c \
						cursor_motion.c edit_command.c is_printable_utf8.c \
						get_command.c utf8_tools.c \
						render_command_line.c arrows.c home_end.c \
						command_line.c xy.c \
						copy_paste_delete.c update_prompt.c update_prompt_tools.c\
						keys_insert.c keys_others.c keys_ctrl.c \
						cursor_tools.c selection.c sh_process_historic.c \
						heredoc.c research_historic.c render_research.c \
						heredoc_tools.c free_command_line.c \
						sh_delete_command.c sh_process_shift_vertical.c \
						sh_process_shift_horizontal.c update_prompt_keys.c \
						sh_process_quoted.c \
						sh_get_cursor_position.c eof_percent.c \
						update_prompt_cwd.c keys_insert_tools.c keys_flush.c \
						keys_debug.c screen_tools.c get_char_len.c

TRAVT_SRCS_NO_PREFIX	= sh_traverse_tools_browse.c \
						sh_traverse_tools_reset.c \
						sh_traverse_tools_debug.c

COMMON_SRCS_NO_PREFIX	= main.c index.c init.c \
						shell_tools.c free_all.c init_term.c signals.c \
						set_signals.c canonical_mode.c \
						historic.c home.c init_tabs.c non_canonical_mode.c \
						hash_binaries.c check_term.c signal_tools.c

PARSER_SRCS_NO_PREFIX =	parser.c \
						print_ast.c \
						compute_lr_automata.c compute_lr_tables.c \
						lr_parse.c compute_first_state.c state.c \
						compute_closure.c compute_transitions.c \
						init_parsing.c reduce.c reduce_tools.c \
						free_parser.c transitive_first_sets.c \
						transition_tools.c \
						closure_tools.c free_node.c free_parser_tools.c \
						fill_lr_tables.c shift.c compute_closure_tools.c \
						reduce_pop.c ast_node_tools.c

LEXER_SRCS_NO_PREFIX =	sh_lexer.c \
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
						sh_lexer_rule_tools.c \
						t_lexer.c t_token.c t_token_show.c \
						t_token_list.c

PROD_SRCS_NO_PREFIX =	sh_prod_and_or.c sh_prod_brace_group.c \
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

AUTO_SRCS_NO_PREFIX	=	add_choices_from_dir.c auto_completion.c \
						populate_choices.c populate_word_by_index.c \
						preprocess_choice_add.c arrow_tools.c \
						render_choices.c add_choices_builtins.c \
						left_arrow.c right_arrow.c arrows_vertical.c \
						fill_buffer.c render_choices_tools.c file_tables.c \
						fill_buffer_from_tables.c add_file_tools.c \
						auto_completion_tools.c escape.c

VARS_SRCS_NO_PREFIX	=	sh_vars_tools_1.c sh_vars_tools_2.c \
						sh_verbose.c sh_verbose_check.c sh_env_tools.c \
						sh_env.c

EXEC_SRCS_NO_PREFIX	=	sh_execute.c \
						sh_execute_pipes.c \
						sh_execute_pipe_sequence.c \
						sh_execute_tools.c \
						sh_exec_builtin.c \
						sh_execute_prefix_postfix.c \
						t_context.c \
						sh_redirections.c\
						sh_debug.c

BUILT_SRCS_NO_PREFIX=	sh_builtin.c \
						sh_builtin_pwd.c \
						sh_builtin_echo.c \
						sh_builtin_exit.c \
						sh_builtin_cd.c sh_builtin_cd_pre_rules.c sh_builtin_cd_post_rules.c sh_builtin_cd_last_rules.c \
						sh_builtin_where.c \
						sh_builtin_type.c \
						sh_builtin_type_path.c \
						sh_builtin_verbose.c \
						sh_builtin_set.c \
						sh_builtin_hash.c \
						sh_builtin_set.c \
						sh_builtin_setenv.c \
						sh_builtin_unsetenv.c \
						sh_builtin_env.c sh_builtin_env_process.c sh_builtin_env_parser.c\
						sh_builtin_hash_tools.c \
						sh_builtin_bonus.c \
						sh_builtin_parser.c

EXP_SRCS_NO_PREFIX =	sh_expansions.c sh_expansions_scan.c\
						sh_expansions_parameter.c \
						sh_expansions_parameter_process.c \
						sh_expansions_parameter_tools.c \
						sh_expansions_tilde.c sh_expansions_tilde_process.c\
						sh_expansions_variable.c \
						t_expansion.c

PERROR_SRCS_NO_PREFIX =	sh_perror.c \
						sh_perror2.c \
						sh_perror_fd.c

INCLUDES_NO_PREFIX	=	sh_21.h sh_lexer.h sh_tokens.h sh_parser.h sh_grammar.h \
					  	sh_command_line.h sh_autocompletion.h sh_exec.h\
						sh_builtin.h sh_expansions.h sh_perror.h

COMMON_SOURCES = $(addprefix $(SRCDIR)/$(COMMON_DIR)/, $(COMMON_SRCS_NO_PREFIX))
GRAM_SOURCES = $(addprefix $(SRCDIR)/$(GRAM_DIR)/, $(GRAM_SRCS_NO_PREFIX))
LEXER_SOURCES = $(addprefix $(SRCDIR)/$(LEXER_DIR)/, $(LEXER_SRCS_NO_PREFIX))
PARSER_SOURCES = $(addprefix $(SRCDIR)/$(PARSER_DIR)/, $(PARSER_SRCS_NO_PREFIX))
PROD_SOURCES = $(addprefix $(SRCDIR)/$(PARSER_DIR)/$(PROD_DIR)/, $(PROD_SRCS_NO_PREFIX))
COMMANDLINE_SOURCES = $(addprefix $(SRCDIR)/$(COMMANDLINE_DIR)/, $(COMMANDLINE_SRCS_NO_PREFIX))
AUTO_SOURCES = $(addprefix $(SRCDIR)/$(COMMANDLINE_DIR)/$(AUTO_DIR)/, $(AUTO_SRCS_NO_PREFIX))
TRAV_SOURCES = $(addprefix $(SRCDIR)/$(TRAV_DIR)/, $(TRAV_SRCS_NO_PREFIX))
TRAVT_SOURCES = $(addprefix $(SRCDIR)/$(TRAVT_DIR)/, $(TRAVT_SRCS_NO_PREFIX))
VARS_SOURCES = $(addprefix $(SRCDIR)/$(VARS_DIR)/, $(VARS_SRCS_NO_PREFIX))
EXEC_SOURCES = $(addprefix $(SRCDIR)/$(EXEC_DIR)/, $(EXEC_SRCS_NO_PREFIX))
BUILT_SOURCES = $(addprefix $(SRCDIR)/$(BUILT_DIR)/, $(BUILT_SRCS_NO_PREFIX))
EXP_SOURCES = $(addprefix $(SRCDIR)/$(EXP_DIR)/, $(EXP_SRCS_NO_PREFIX))
PERROR_SOURCES = $(addprefix $(SRCDIR)/$(PERROR_DIR)/, $(PERROR_SRCS_NO_PREFIX))

COMMON_OBJECTS = $(addprefix $(OBJDIR)/$(COMMON_DIR)/, $(COMMON_SRCS_NO_PREFIX:%.c=%.o))
GRAM_OBJECTS = $(addprefix $(OBJDIR)/$(GRAM_DIR)/, $(GRAM_SRCS_NO_PREFIX:%.c=%.o))
LEXER_OBJECTS = $(addprefix $(OBJDIR)/$(LEXER_DIR)/, $(LEXER_SRCS_NO_PREFIX:%.c=%.o))
PARSER_OBJECTS = $(addprefix $(OBJDIR)/$(PARSER_DIR)/, $(PARSER_SRCS_NO_PREFIX:%.c=%.o))
PROD_OBJECTS = $(addprefix $(OBJDIR)/$(PARSER_DIR)/$(PROD_DIR)/, $(PROD_SRCS_NO_PREFIX:%.c=%.o))
TRAV_OBJECTS = $(addprefix $(OBJDIR)/$(TRAV_DIR)/, $(TRAV_SRCS_NO_PREFIX:%.c=%.o))
TRAVT_OBJECTS = $(addprefix $(OBJDIR)/$(TRAVT_DIR)/, $(TRAVT_SRCS_NO_PREFIX:%.c=%.o))
VARS_OBJECTS = $(addprefix $(OBJDIR)/$(VARS_DIR)/, $(VARS_SRCS_NO_PREFIX:%.c=%.o))
EXEC_OBJECTS = $(addprefix $(OBJDIR)/$(EXEC_DIR)/, $(EXEC_SRCS_NO_PREFIX:%.c=%.o))
BUILT_OBJECTS = $(addprefix $(OBJDIR)/$(BUILT_DIR)/, $(BUILT_SRCS_NO_PREFIX:%.c=%.o))
AUTO_OBJECTS = $(addprefix $(OBJDIR)/$(COMMANDLINE_DIR)/$(AUTO_DIR)/, $(AUTO_SRCS_NO_PREFIX:%.c=%.o))
COMMANDLINE_OBJECTS = $(addprefix $(OBJDIR)/$(COMMANDLINE_DIR)/, $(COMMANDLINE_SRCS_NO_PREFIX:%.c=%.o))
EXP_OBJECTS = $(addprefix $(OBJDIR)/$(EXP_DIR)/, $(EXP_SRCS_NO_PREFIX:%.c=%.o))
PERROR_OBJECTS = $(addprefix $(OBJDIR)/$(PERROR_DIR)/, $(PERROR_SRCS_NO_PREFIX:%.c=%.o))

INCLUDES = $(addprefix $(INCLUDESDIR)/, $(INCLUDES_NO_PREFIX))

OBJECTS = $(COMMON_OBJECTS)
OBJECTS += $(PROD_OBJECTS)
OBJECTS += $(GRAM_OBJECTS)
OBJECTS += $(LEXER_OBJECTS)
OBJECTS += $(PARSER_OBJECTS)
OBJECTS += $(TRAV_OBJECTS)
OBJECTS += $(TRAVT_OBJECTS)
OBJECTS += $(AUTO_OBJECTS)
OBJECTS += $(VARS_OBJECTS)
OBJECTS += $(EXEC_OBJECTS)
OBJECTS += $(BUILT_OBJECTS)
OBJECTS += $(COMMANDLINE_OBJECTS)
OBJECTS += $(EXP_OBJECTS)
OBJECTS += $(PERROR_OBJECTS)

INC =	-I $(INCLUDESDIR) -I $(LIBFTDIR) -I $(LIBFTDIR)/$(PRINTFDIR)

ifeq ($(OS),Linux)
	CFLAGS = -DPATH=$(PWD) $(INC)
else
	CFLAGS = -DPATH=$(PWD) $(INC) -Wall -Werror -Wextra
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
	@make -C $(LIBFTDIR) $(SPEED)
	@echo "$(FLAGS_COLOR)Compiling with flags $(CFLAGS) $(EOC)"
	@make $(BINDIR)/$(NAME) $(SPEED)

debug:
	@make all DEBUG=1

$(LIBFT):
	@make -C $(LIBFTDIR)

$(BINDIR)/$(NAME): $(OBJECTS) $(LIBFT)
	@$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)
	@echo "$(OK_COLOR)$(NAME) linked with success !$(EOC)"

$(OBJDIR)/$(COMMON_DIR)/%.o : $(SRCDIR)/$(COMMON_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(COMMON_DIR)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "${COMP_COLOR}$< ${EOC}"

$(OBJDIR)/$(GRAM_DIR)/%.o : $(SRCDIR)/$(GRAM_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(GRAM_DIR)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "${COMP_COLOR}$< ${EOC}"

$(OBJDIR)/$(PARSER_DIR)/$(PROD_DIR)/%.o : $(SRCDIR)/$(PARSER_DIR)/$(PROD_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(PARSER_DIR)/$(PROD_DIR)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "${COMP_COLOR}$< ${EOC}"

$(OBJDIR)/$(COMMANDLINE_DIR)/$(AUTO_DIR)/%.o : $(SRCDIR)/$(COMMANDLINE_DIR)/$(AUTO_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(COMMANDLINE_DIR)/$(AUTO_DIR)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "${COMP_COLOR}$< ${EOC}"

$(OBJDIR)/$(COMMANDLINE_DIR)/%.o : $(SRCDIR)/$(COMMANDLINE_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(COMMANDLINE_DIR)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "${COMP_COLOR}$< ${EOC}"

$(OBJDIR)/$(LEXER_DIR)/%.o : $(SRCDIR)/$(LEXER_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(LEXER_DIR)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "${COMP_COLOR}$< ${EOC}"

$(OBJDIR)/$(TRAV_DIR)/%.o : $(SRCDIR)/$(TRAV_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(TRAV_DIR)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "${COMP_COLOR}$< ${EOC}"

$(OBJDIR)/$(TRAVT_DIR)/%.o : $(SRCDIR)/$(TRAVT_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(TRAVT_DIR)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "${COMP_COLOR}$< ${EOC}"

$(OBJDIR)/$(PARSER_DIR)/%.o : $(SRCDIR)/$(PARSER_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(PARSER_DIR)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "${COMP_COLOR}$< ${EOC}"

$(OBJDIR)/$(VARS_DIR)/%.o : $(SRCDIR)/$(VARS_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(VARS_DIR)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "${COMP_COLOR}$< ${EOC}"

$(OBJDIR)/$(EXEC_DIR)/%.o : $(SRCDIR)/$(EXEC_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(EXEC_DIR)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "${COMP_COLOR}$< ${EOC}"

$(OBJDIR)/$(BUILT_DIR)/%.o : $(SRCDIR)/$(BUILT_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(BUILT_DIR)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "${COMP_COLOR}$< ${EOC}"

$(OBJDIR)/$(EXP_DIR)/%.o : $(SRCDIR)/$(EXP_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(EXP_DIR)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "${COMP_COLOR}$< ${EOC}"

$(OBJDIR)/$(PERROR_DIR)/%.o : $(SRCDIR)/$(PERROR_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(PERROR_DIR)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "${COMP_COLOR}$< ${EOC}"

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "${COMP_COLOR}$< ${EOC}"

clean:
	@make clean -C $(LIBFTDIR)
	@rm -f $(OBJECTS)
	@rm -rf $(OBJDIR) && echo "${OK_COLOR}Successfully cleaned $(NAME) objects files ${EOC}"

fclean:
	@make fclean -C $(LIBFTDIR)
	@rm -f $(OBJECTS)
	@rm -rf $(OBJDIR) && echo "${OK_COLOR}Successfully cleaned $(NAME) objects files ${EOC}"
	@rm -f $(BINDIR)/$(NAME)  && echo "${OK_COLOR}Successfully cleaned $(NAME) ${EOC}"

re: fclean all

rere:
	@rm -f $(OBJECTS)
	@rm -rf $(OBJDIR)
	@rm -f $(BINDIR)/$(NAME)
	make all

os:
	@echo $(OS)

.PHONY: all clean fclean re
