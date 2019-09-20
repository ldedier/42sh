/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_command_line.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:20:10 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/20 10:27:41 by ldedier          ###   ########.fr       */
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

# define COMMAND_PROMPT	"(vi"
# define COUNT_PROMPT	"(arg:"
# define VISUAL_PROMPT	"(visual)"
# define HEREDOC_PROMPT	"heredoc"
# define PROMPT_SUFFIX	"> "
# define READ_BUFF_SIZE	6

# define SUCCESS_RSRCH		"failing bck-i-search: "
# define UNSUCCESS_RSRCH	"bck-i-search: "

# define ELIPTIC_COMMAND_LINE	"<...>"

typedef char *(*t_heredoc_func)(const char *);

typedef enum		e_mode
{
	E_MODE_INSERT,
	E_MODE_VISUAL,
	E_MODE_COMMAND
}					t_mode;

typedef enum		e_cl_context
{
	E_CONTEXT_STANDARD,
	E_CONTEXT_HEREDOC,
	E_CONTEXT_DQUOTE,
	E_CONTEXT_QUOTE,
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
** last_ft_command	: last f, F , t, or T command executed by the shell
** edit_line		: dup from the command_line to retrieve from history
**
*/
typedef struct		s_command_line
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
	t_mode			mode;
	int				interrupted;
	char			*clipboard;
	int				pinned_index;
	t_cl_context	context;
	int				prev_prompt_len;
	char			*to_append_str;
	int				fd;
	t_key_buffer	buffer;
	t_command_count	count;
	t_ft_command	last_ft_command;
	char			*edit_line;
}					t_command_line;

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
** home_end.c
*/
int					process_end(t_command_line *command_line);
int					process_start(t_command_line *command_line);

/*
** free_command_line.c
*/
void				sh_free_command_line(t_command_line *command_line);

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
** is_printable_utf8.c
*/
int					is_utf8_len_header(
	unsigned char first_byte, int length);
int					is_utf8_next_byte(unsigned char next_byte);
int					is_utf8_len_3(unsigned char *buffer);
int					is_utf8_len_4(unsigned char *buffer);
int					is_printable_utf8(unsigned char *buffer, int nb_bytes);

/*
** update_prompt_cwd.c
*/
int					update_prompt_from_absolute_path(
	char *cwd, char **new_prompt);
int					update_prompt_cwd_bonus_tilde(
	t_shell *shell, char **new_prompt, char *cwd, int *returned);
int					update_prompt_cwd(t_shell *shell, char **new_prompt);

/*
** get_char_len.c
*/
int					get_char_len2(
	int index, int len, unsigned char *entry);
int					get_char_len(int index, unsigned char *entry);

/*
** keys_ctrl.c
*/
int					process_ctrl_c(
	t_shell *shell, t_command_line *command_line);
int					process_ctrl_d(
	t_shell *shell, t_command_line *command_line);

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
** render_research.c
*/
int					get_research_nb_lines(t_command_line *command_line);
int					render_research(t_command_line *command_line);

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
** render_command_line.c
*/
void				render_command_researched(
	t_command_line *command_line);
int					print_after_command_line(
	t_command_line *command_line, int print_choices);
int					get_command_line_starting_index2(int scrolled_lines);
int					get_command_line_starting_index(
	t_command_line *command_line);
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
void				process_print_command_line(
	t_command_line *command_line, int empty_space);
void				print_command_line(t_command_line *command_line);
int					get_command_line_prefix_len(
	t_command_line *command_line);
int					should_elipse_end(
	t_command_line *command_line, int scrolled_lines);
int					sh_scroll_command_line(
	t_command_line *command_line, int cursor, int cursor_inc);
void				check_selection(t_command_line *command_line);
int					render_command_line(
	t_command_line *command_line, int cursor_inc, int print_choices);

/*
** sh_process_quoted.c
*/
int					sh_process_process_quoted(
	int old_context, t_lexer *lexer);
int					sh_process_quoted(t_lexer *lexer);

/*
** sh_process_history.c
*/
int					process_history_down(
	t_shell *shell,
	t_command_line *command_line,
	int count,
	int replace_cursor);
int					process_history_up(
	t_shell *shell,
	t_command_line *command_line,
	int count,
	int replace_cursor);

/*
** xy.c
*/
t_xy				get_position(int cursor);
int					xy_is_equal(t_xy xy1, t_xy xy2);

/*
** sh_get_cursor_position.c
*/
int					process_read_cursor_position(
	char answer[4096], size_t *answer_len, int fd);
int					sh_get_cursor_position(int *x, int *y);

/*
** keys_insert.c
*/
int					process_enter(t_command_line *command_line);
int					process_process_keys_ret(
	t_key_buffer *buffer,
	t_shell *shell,
	t_command_line *command_line);
int					process_keys_ret(
	t_key_buffer *buffer,
	t_shell *shell,
	t_command_line *command_line);
int					process_key_insert_printable_utf8(
	t_key_buffer *buffer,
	t_shell *shell,
	t_command_line *command_line);
int					process_keys_insert(
	t_key_buffer *buffer,
	t_shell *shell,
	t_command_line *command_line);

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
** keys.c
*/
int					process_escape_sequence(
	t_shell *shell,
	t_command_line *command_line,
	t_key_buffer *buffer);
int					process_shift(
	t_key_buffer *buffer, t_command_line *command_line);
int					await_stream(int fd);
int					process_keys(
	t_key_buffer *buffer,
	t_shell *shell,
	t_command_line *command_line);
int					process_get_keys(
	t_key_buffer *buffer,
	t_shell *shell,
	t_command_line *command_line);
int					get_keys(t_shell *shell, t_command_line *command_line);

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
** cursor_motion.c
*/
void				go_right(int right);
void				go_up_left(int up);
int					go_up_to_prompt(int width, int cursor);

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
** update_prompt_keys.c
*/
int					update_prompt_cwd_home(char **new_prompt);
int					process_escape(
	t_shell *shell,
	t_command_line *command_line,
	t_key_buffer *buffer);
int					process_i(
	t_shell *shell,
	t_command_line *command_line,
	t_key_buffer *buffer);
int					process_v(
	t_shell *shell,
	t_command_line *command_line,
	t_key_buffer *buffer);

/*
** eof_percent.c
*/
void				print_eof_delimiter(void);
int					sh_add_eof(int interrupted);

/*
** cursor_tools.c
*/
int					get_true_cursor_pos_prev_prompt(int cursor);
int					get_true_cursor_pos(int cursor);
int					get_down_from_command(t_command_line *command_line);
void				replace_cursor_on_index(void);
void				replace_cursor_after_render(void);

/*
** keys_others.c
*/
int					process_keys_others(
	t_key_buffer *buffer,
	t_shell *shell,
	t_command_line *command_line);

/*
** screen_tools.c
*/
int					putchar_int(int i);
int					process_clear(t_command_line *command_line);

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
** update_prompt_tools.c
*/
int					end_with_char(char *str, char c);
int					get_file_in_dir(char *filename, char *dirname);
int					get_path_from_absolute_path(char *str, char **path);
int					get_path_and_file_from_str(
	char *str, char **path, char **file);

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
** keys_insert_tools.c
*/
int					process_enter_no_autocompletion(
	t_command_line *command_line);
void				process_cancel_autocompletion(
	t_command_line *command_line);
void				cancel_autocompletion(
	t_key_buffer *buffer, t_command_line *command_line);

/*
** sh_process_shift_vertical.c
*/
int					process_shift_up(t_command_line *command_line);
int					process_shift_down(t_command_line *command_line);

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
** heredoc_tools.c
*/
int					refine_heredoc(char *str, int apply_expansion);
int					heredoc_ret(
	t_shell *shell, t_command_line *command_line, int ret);
char				*heredoc_ret_str(
	t_shell *shell, t_command_line *command_line, char *str);
int					append_to_str(char **str, char *to_append);

/*
** update_prompt.c
*/
int					update_prompt_context(
	t_shell *shell, t_command_line *command_line, char **new_prompt);
int					fill_prompt_command_mode(
	char **new_prompt, t_command_line *command_line);
int					update_prompt(
	t_shell *shell, t_command_line *command_line);
int					update_prompt_from_quote(
	t_shell *shell,
	t_command_line *command_line,
	char quote,
	int backslash);

/*
** selection.c
*/
void				populate_min_max_selection(
	t_command_line *command_line, int *min, int *max);
void				render_command_visual(t_command_line *command_line);

/*
** edit_command.c
*/
void				ring_bell(void);
void				process_edit_command_left(
	t_command_line *command_line);
void				process_edit_command_right(
	t_command_line *command_line);

#endif
