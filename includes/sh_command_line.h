/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_command_line.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:20:10 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/25 01:09:09 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_COMMAND_LINE_H
# define SH_COMMAND_LINE_H

# include "libft.h"

# define CWD_LEN			1000

# define PROMPT				""
# define BACKSLASH_PROMPT	""
# define QUOTE_PROMPT		"quote"
# define DQUOTE_PROMPT		"dquote"
# define PIPE_PROMPT		"pipe"
# define PROCSUBST_PROMPT	"procsubst"
# define CMDSUBST_PROMPT	"cmdsubst"
# define VARIABLE_PROMPT	"braceparam"

# define COMMAND_PROMPT	"(vi"
# define COUNT_PROMPT	"(arg:"
# define REPLACE_PROMPT	"(replace)"
# define VISUAL_PROMPT	"(visual)"
# define HEREDOC_PROMPT	"heredoc"
# define PROMPT_SUFFIX	">"
# define READ_BUFF_SIZE	6

# define SUCCESS_RSRCH		"failing bck-i-search: "
# define UNSUCCESS_RSRCH	"bck-i-search: "

# define ELIPTIC_COMMAND_LINE	"<...>"

typedef char *(*t_heredoc_func)(const char *);
typedef struct s_entry		t_entry;
typedef struct s_command_line	t_command_line;

typedef enum		e_edit_style
{
	E_EDIT_STYLE_READLINE,
	E_EDIT_STYLE_VIM,
}					t_edit_style;

typedef enum		e_mode
{
	E_MODE_INSERT,
	E_MODE_VISUAL,
	E_MODE_COMMAND,
	E_MODE_REPLACE
}					t_mode;

typedef enum		e_cl_context
{
	E_CONTEXT_STANDARD,
	E_CONTEXT_HEREDOC,
	E_CONTEXT_DQUOTE,
	E_CONTEXT_QUOTE,
	E_CONTEXT_PRCSUBST_IN,
	E_CONTEXT_PRCSUBST_OUT,
	E_CONTEXT_CMDSUBST,
	E_CONTEXT_VARIABLE,
	E_CONTEXT_PIPE,
	E_CONTEXT_BACKSLASH,
}					t_cl_context;

typedef struct		s_searcher
{
	int				active;
	t_dlist			*head;
	t_dy_str		*dy_str;
	int				match_index;
	int				unsuccessful;
}					t_searcher;

typedef struct		s_key_buffer
{
	unsigned char	buff[READ_BUFF_SIZE];
	int				progress;
	int				last_char_input;
	int				persistent;
}					t_key_buffer;

typedef struct		s_ft_command
{
	char			c;
	int				(*motion)(t_command_line *command_line, char c);
	int				locked;
}					t_ft_command;

typedef struct		s_command_count
{
	int				active;
	int				tmp_value;
	int				value;
}					t_command_count;

typedef struct		s_save
{
	int				current_index;
	char			*str;
}					t_save;

/*
** dy_str			: content of the command_line
** heredoc_eof		: current eof of the heredoc
** prompt			: current prompt of the command_line
** nb_chars			: numbers of UTF8 characters in the dy_str
** current_index	: where to insert characters in the command line
** scrolled_lines	: number of lines scrolled by the terminal
**
** mode				: insert, command, or visual
** context			: standard, heredoc, quotes, double, quotes, backslashes..
**
** clipboard		: what got yanked or deleted in visual mode
** pinned_index		: where the visual mode got initiated
**
** interrupted		: if the command got interrupted by a ctrl D or ctrl C
** to_append_str	: what to append to the string in the case of \\ in heredocs
** fd				: fd to print input (open("/fd/tty"));
** key_buffer		: read characters
** count			: vim arguments
** last_ft_command	: last f, F, t, or T command executed by the shell
** edit_line		: dup from the command_line to retrieve from history
*/
struct				s_command_line
{
	t_shell			*shell;
	t_auto_complete	autocompletion;
	t_searcher		searcher;
	t_dy_str		*dy_str;
	char			*heredoc_eof;
	char			*prompt;
	int				nb_chars;
	int				current_index;
	int				scrolled_lines;
	int				interrupted;
	char			*clipboard;
	int				pinned_index;
	t_mode			mode;
	t_cl_context	context;
	t_edit_style	edit_style;
	int				prev_prompt_len;
	char			*to_append_str;
	int				fd;
	t_key_buffer	buffer;
	t_command_count	count;
	t_command_count	motion_count;
	t_command_count	*current_count;
	t_ft_command	last_ft_command;
	char			*edit_line;
	t_list			*saves_stack;
	int				edit_counter;
	int				mark_index;
};

typedef struct		s_xy
{
	int				x;
	int				y;
}					t_xy;

typedef struct		s_utf8_copier
{
	int				len;
	int				i;
	int				j;
	int				nb_chars;
	int				min;
	int				max;
	int				to_add;
}					t_utf8_copier;

typedef struct		s_glob
{
	struct termios	term_init;
	struct termios	term;
	t_command_line	command_line;
	t_cfg			*cfg;
	int				cursor;
	struct winsize	winsize;
	int				verbose;
}					t_glob;

t_glob				g_glob;

/*
********************************************************************************
*/

/*
** arrows.c
*/
int					process_down(
	t_shell *shell, t_command_line *command_line);
int					process_up(
	t_shell *shell, t_command_line *command_line);
int					process_left(
	t_shell *shell, t_command_line *command_line);
int					process_right(
	t_shell *shell, t_command_line *command_line);

/*
** command_count.c
*/
int					add_digit_and_update(
	t_command_line *command_line, char c);

/*
** command_line.c
*/
void				flush_command_line(t_command_line *command_line);
int					process_substitute_command(
	t_command_line *command_line,
	char *str,
	t_word word,
	int print_choices);
int					substitute_current_index(
	t_command_line *command_line, t_file *file);
int					command_line_nb_rows(t_command_line *command_line);

/*
** copy_command_line.c
*/
void				process_termcaps_through_copy(
	t_command_line *command_line,
	t_utf8_copier *c,
	char *str,
	char *capability);
void				process_termcaps_through_utf8_copy(
	char *str, t_command_line *command_line, t_utf8_copier *c);
void				process_copy_utf8_char(
	char *str,
	t_command_line *command_line,
	int index,
	t_utf8_copier *c);
void				copy_last_part_of_command_line(
	t_command_line *command_line,
	t_utf8_copier *c,
	int index,
	char *str);

/*
** copy_paste_delete.c
*/
int					command_line_copy_all(t_command_line *command_line);
int					copy_selection_to_clipboard(
	t_command_line *command_line);
int					paste_current_index(
	t_command_line *command_line, char *to_paste);
int					delete_command_line_selection(
	t_command_line *command_line);

/*
** cursor_motion.c
*/
void				go_right(int right);
void				go_up_left(int up);
int					go_up_to_prompt(int width, int cursor);

/*
** cursor_tools.c
*/
int					get_true_cursor_pos_prev_prompt(int cursor);
int					get_true_cursor_pos(int cursor);
void				replace_cursor_on_index(void);
void				replace_cursor_after_render(void);

/*
** edit_command.c
*/
void				ring_bell(void);
void				process_edit_command_left(
	t_command_line *command_line);
void				process_edit_command_right(
	t_command_line *command_line);

/*
** eof_percent.c
*/
void				print_eof_delimiter(void);
int					sh_add_eof(int interrupted);

/*
** free_command_line.c
*/
void				sh_free_command_line(t_command_line *command_line);

/*
** get_char_len.c
*/
int					get_char_len_unprotected(
	int index, unsigned char *entry);
int					get_char_len2(
	int index, int len, unsigned char *entry);
int					get_char_len(int index, unsigned char *entry);

/*
** get_command.c
*/
int					sh_add_to_dy_str(
	t_dy_str *dy_str,
	unsigned char buffer[READ_BUFF_SIZE],
	int nb_bytes);
int					sh_add_to_command(
	t_command_line *command_line,
	unsigned char buffer[READ_BUFF_SIZE],
	int nb_bytes);
int					reset_command_line(
	t_shell *shell, t_command_line *command_line);
int					sh_get_command(
	t_shell *shell, t_command_line *command_line);

/*
** get_down_from_command.c
*/
int					get_down_from_command(t_command_line *command_line);

/*
** heredoc.c
*/
int					process_heredoc_new_line(
	char **res,
	char *tmp,
	t_shell *shell,
	t_command_line *command_line);
int					process_heredoc_through_command(
	char **res,
	t_shell *shell,
	t_heredoc heredoc_data,
	t_command_line *command_line);
void				init_heredoc_command_line(
	t_shell *shell, t_command_line *command_line, char *stop);
char				*heredoc_handle_ctrl_d(
	t_shell *shell, char *stop, char **res, int *ret);
char				*heredoc(t_shell *shell, t_heredoc heredoc, int *ret);

/*
** heredoc_tools.c
*/
int					refine_heredoc(char *str, int apply_expansion);
int					heredoc_ret(
	t_shell *shell, t_command_line *command_line, int ret);
char				*heredoc_ret_str(
	t_shell *shell, t_command_line *command_line, char *str);
int					append_to_str(char **str, char *to_append);

/*
** home_end.c
*/
int					process_end(t_command_line *command_line);
int					process_start(t_command_line *command_line);

/*
** is_printable_utf8.c
*/
int					is_utf8_len_header(
	unsigned char first_byte, int length);
int					is_utf8_next_byte(unsigned char next_byte);
int					is_utf8_len_3(unsigned char *buffer);
int					is_utf8_len_4(unsigned char *buffer);
int					is_printable_utf8(unsigned char *buffer, int nb_bytes);

/*
** keys.c
*/
int					process_escape_sequence(
	t_shell *shell,
	t_command_line *command_line,
	t_key_buffer *buffer);
int					process_shift(
	t_key_buffer *buffer, t_command_line *command_line);
int					process_keys(
	t_key_buffer *buffer,
	t_shell *shell,
	t_command_line *command_line);
int					process_get_keys(
	t_key_buffer *buffer,
	t_shell *shell,
	t_command_line *command_line);
int					get_keys(t_shell *shell, t_command_line *cl);

/*
** keys_ctrl.c
*/
int					process_ctrl_c(
	t_shell *shell, t_command_line *command_line);
int					process_ctrl_d(
	t_shell *shell, t_command_line *command_line);

/*
** keys_debug.c
*/
void				sh_print_buffer(t_key_buffer buffer);

/*
** keys_flush.c
*/
void				flush_keys(t_key_buffer *buffer);
int					flush_keys_ret(t_key_buffer *buffer, int ret);
int					should_flush_buffer(
	t_key_buffer buffer, t_command_line *command_line);

/*
** keys_insert.c
*/
int					process_enter(t_command_line *command_line);
int					process_key_insert_printable_utf8(
	t_key_buffer *buffer,
	t_shell *shell,
	t_command_line *command_line);
int					insert_keys(
	t_key_buffer *buffer,
	t_shell *shell,
	t_command_line *command_line);
int					process_keys_insert(
	t_key_buffer *buffer,
	t_shell *shell,
	t_command_line *command_line);

/*
** keys_insert_tools.c
*/
int					process_enter_no_autocompletion(
	t_command_line *command_line);
void				process_cancel_autocompletion(
	t_command_line *command_line);
void				cancel_autocompletion(
	t_key_buffer *buffer, t_command_line *command_line);

/*
** keys_others.c
*/
int					replace_command_line(
	t_key_buffer *buffer, t_command_line *command_line);
int					process_keys_others(
	t_key_buffer *buffer,
	t_shell *shell,
	t_command_line *command_line);

/*
** keys_readline.c
*/
int					process_keys_readline(
	t_key_buffer *buffer,
	t_shell *shell,
	t_command_line *command_line);

/*
** keys_ret.c
*/
int					process_process_keys_ret(
	t_key_buffer *buffer,
	t_shell *shell,
	t_command_line *command_line);
int					process_keys_ret(
	t_key_buffer *buffer,
	t_shell *shell,
	t_command_line *command_line);

/*
** keys_tools.c
*/
int					await_stream(int fd);

/*
** pre_post_render.c
*/
int					print_after_command_line(
	t_command_line *command_line, int print_choices);
void				check_selection(t_command_line *command_line);
int					print_pre_command_line(
	t_command_line *command_line, int *ret);

/*
** print_command_line.c
*/
void				process_print_command_line(
	t_command_line *command_line, int empty_space);
void				print_command_line(t_command_line *command_line);

/*
** render_command_line.c
*/
int					get_command_line_prefix_len(
	t_command_line *command_line);
int					render_command_line(
	t_command_line *command_line, int cursor_inc, int print_choices);

/*
** render_research.c
*/
int					get_research_nb_lines(t_command_line *command_line);
int					render_research(t_command_line *command_line);

/*
** research_history.c
*/
int					process_find_in_history(
	t_command_line *command_line, char *to_search_in, char *found);
int					progress_process_research_history(
	t_command_line *command_line, t_shell *shell);
int					update_research_history(
	t_command_line *command_line, t_shell *shell, int reset);
int					process_research_history(
	t_command_line *command_line, t_shell *shell);

/*
** restore_save.c
*/
int					process_restore_save(
	t_command_line *command_line, t_save *save, int *ret);
int					sh_restore_save(t_command_line *command_line);
int					sh_restore_all_save(t_command_line *command_line);

/*
** save_command_line.c
*/
int					sh_save_command_line(t_command_line *command_line);
int					sh_process_edit_counter(
	t_command_line *command_line, int inc);
int					sh_reset_saves(t_command_line *command_line);

/*
** saves.c
*/
t_list				**get_current_saves_stack(
	t_command_line *command_line, t_entry **entry);
int					sh_init_entry_saves(t_entry *entry);

/*
** screen_tools.c
*/
int					putchar_int(int i);
int					process_clear(t_command_line *command_line);

/*
** scroll_command_line.c
*/
int					get_command_line_starting_index2(int scrolled_lines);
int					get_command_line_starting_index(
	t_command_line *command_line);
int					should_elipse_end(
	t_command_line *command_line, int scrolled_lines);
int					get_scroll_to_add(
	t_command_line *command_line,
	int target_screen_line,
	int research_nb_lines);
int					sh_scroll_command_line(
	t_command_line *command_line, int cursor, int cursor_inc);

/*
** selection.c
*/
void				populate_min_max_selection(
	t_command_line *command_line, int *min, int *max);
void				render_command_visual(t_command_line *command_line);

/*
** sh_delete_command.c
*/
void				process_delete_searcher(
	t_command_line *command_line, t_shell *shell);
void				process_process_delete(t_command_line *command_line);
void				process_delete(
	t_command_line *command_line, t_shell *shell);
void				process_suppr(t_command_line *command_line);

/*
** sh_get_cursor_position.c
*/
int					process_read_cursor_position(
	char answer[4096], size_t *answer_len, int fd);
int					sh_get_cursor_position(int *x, int *y);

/*
** sh_process_history.c
*/
int					switch_command_line(
	t_command_line *command_line, char *str, int start);
int					switch_command_line_index(
	t_command_line *command_line, char *str, int index);
int					process_history_down(
	t_shell *shell,
	t_command_line *command_line,
	int count,
	int start);
int					reached_history_end(t_shell *shell);
int					process_history_up(
	t_shell *shell,
	t_command_line *command_line,
	int count,
	int start);

/*
** sh_process_quoted.c
*/
int					sh_process_process_quoted(
	int old_context, t_lexer *lexer);
int					sh_process_quoted(t_lexer *lexer);

/*
** sh_process_shift_horizontal.c
*/
int					process_process_shift_right(
	t_command_line *c_line, t_word *word, int *index);
int					process_shift_right(t_command_line *c_line);
int					process_process_shift_left(
	t_command_line *command_line, t_word *word, int *index);
int					process_shift_left(t_command_line *command_line);

/*
** sh_process_shift_vertical.c
*/
int					process_shift_up(t_command_line *command_line);
int					process_shift_down(t_command_line *command_line);

/*
** sh_update_command_line.c
*/
void				update_command_line_index(
	t_command_line *command_line, int index);
void				update_command_line(
	t_command_line *command_line, int start);

/*
** t_save.c
*/
t_save				*t_save_new(char *str, int index);
void				t_save_free(t_save *save);
void				t_save_free_list(void *s, size_t dummy);

/*
** update_prompt.c
*/
int					update_prompt_context(
	t_shell *shell, t_command_line *command_line, char **new_prompt);
int					fill_prompt_command_mode(
	char **new_prompt, t_command_line *command_line);
int					update_prompt_mode(
	t_command_line *command_line, char **new_prompt);
int					update_prompt(
	t_shell *shell, t_command_line *command_line);
int					update_prompt_from_quote(
	t_shell *shell,
	t_command_line *command_line,
	char quote,
	int backslash);

/*
** update_prompt_cwd.c
*/
int					update_prompt_from_absolute_path(
	char *cwd, char **new_prompt);
int					update_prompt_cwd_bonus_tilde(
	t_shell *shell, char **new_prompt, char *cwd, int *returned);
int					update_prompt_cwd(t_shell *shell, char **new_prompt);

/*
** update_prompt_keys.c
*/
int					update_prompt_cwd_home(char **new_prompt);
int					process_escape(
	t_shell *shell,
	t_command_line *command_line,
	t_key_buffer *buffer);
int					process_v(
	t_shell *shell,
	t_command_line *command_line,
	t_key_buffer *buffer);

/*
** update_prompt_tools.c
*/
int					end_with_char(char *str, char c);
int					get_file_in_dir(char *filename, char *dirname);
int					get_path_from_absolute_path(char *str, char **path);
int					get_path_and_file_from_str(
	char *str, char **path, char **file);

/*
** utf8_tools.c
*/
int					ft_strlen_utf8(char *str);
int					ft_strnlen_utf8(char *str, int n);
int					get_left_w_char_index_dy_str(
	t_dy_str *dy_str, int index);
int					get_left_w_char_index(t_command_line *command_line);
int					get_right_w_char_index(t_command_line *command_line);

/*
** xy.c
*/
t_xy				get_position(int cursor);
int					xy_is_equal(t_xy xy1, t_xy xy2);

int					sh_init_command_line(
	t_shell *shell, t_command_line *command_line);
int					get_research_nb_lines_n(
	t_command_line *command_line, int n);
#endif
