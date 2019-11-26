/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_autocompletion.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:59:37 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/20 02:25:20 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_AUTOCOMPLETION_H
# define SH_AUTOCOMPLETION_H

# include "libft.h"

# define AC_PADDING		2

# define DIR_COLOR		BOLD RED

typedef struct s_shell			t_shell;
typedef struct s_command_line	t_command_line;
typedef struct s_ast_node		t_ast_node;

/*
** str:					word content
** start_index:			index of word in the whole string
** word_index:			index of word in the whole string
** len:					len of the word
** index_byte_offset:	index of cursor in the word
** index_char_offset:	nb of chars before the cursor in the word (utf8)
*/
typedef struct		s_word
{
	int				word_index;
	char			*str;
	char			*to_compare;
	int				start_index;
	int				prev_word_index;
	int				len;
	int				utf8_len;
	int				index_byte_offset;
	int				index_char_offset;
	t_token			*token;
}					t_word;

typedef struct		s_file
{
	char			*fullname;
	char			*name;
	char			unstatable;
	struct stat		st;
	int				x;
	int				y;
}					t_file;

typedef struct		s_auto_complete
{
	t_dlist			*head;
	t_dlist			*choices;
	int				choices_common_len;
	char			active;
	int				nb_cols;
	int				nb_lines;
	int				scrolled_lines;
}					t_auto_complete;

typedef struct		s_exec
{
	t_word			word;
	t_list			*tokens;
	t_ast_node		*ast_root;
	t_ast_node		*cst_root;
}					t_exec;

typedef struct		s_choice_filler
{
	char			*transformed_path;
	char			*path;
	char			*suffix;
	t_word			*word;
	int				types;
}					t_choice_filler;

/*
********************************************************************************
*/

/*
** add_choices_builtins.c
*/
int					process_add_choices_from_name(
	t_shell *shell, t_command_line *command_line, char *name);
int					add_choices_builtins(t_shell *shell, t_word *word);

/*
** add_choices_from_dir.c
*/
int					process_add_choices_from_choice_filler(
	t_shell *shell,
	t_command_line *cl,
	char *entry,
	t_choice_filler *c);
int					close_dir_ret(DIR *dir, int ret);
int					add_choices_from_dir(
	t_shell *shell, t_choice_filler *c);

/*
** add_choices_from_expansions.c
*/
int					populate_keys_from_dy_tab(
	t_dy_tab *dtab,
	t_command_line *command_line,
	t_shell *shell,
	t_choice_filler *c);
int					process_fill_choice_filler_expansion(
	t_choice_filler *c, int *last_dollar_index, int exp_braced);
int					fill_choice_filler_expansion(
	t_choice_filler *c, int *last_dollar_index);
int					populate_choices_from_expansions(
	t_command_line *command_line, t_shell *shell, t_word *word);

/*
** add_choices_from_expansions_tools.c
*/
int					sh_match_key(
	char *entry, char *to_compare, int *equal_index);
int					get_end_index(char *str, int index);
int					free_turn_choice_filler(t_choice_filler *c, int ret);

/*
** add_choices_tools.c
*/
void				add_node_next_to_node(t_dlist **node, t_dlist *to_add);
int					free_file_ret(t_file *file, int ret);
int					sh_pass_filters(t_file *file, int types);
char				*get_fullname(t_choice_filler *c, char *entry);

/*
** add_file_tools.c
*/
void				copy_str_to_res(
	char *res, char *str, int *i, int to_add);
int					ft_isprint_only_utf8(char *str);
char				*ft_str_to_ascii_dup(char *str);
int					populate_file(
	t_file *file, char *name, char **path, t_shell *shell);
t_file				*new_file(
	t_shell *shell, char *name, char *fullname);

/*
** arrow_tools.c
*/
void				process_autocompletion_switch(
	t_command_line *command_line, t_file *prev_file, t_file *file);
int					substitute_command_str_from_str(
	t_command_line *command_line, char *from, char *str);
int					substitute_command_str(
	t_shell *shell, t_command_line *command_line, char *str);

/*
** arrows_vertical.c
*/
int					process_autocompletion_down(
	t_shell *shell, t_command_line *command_line);
int					process_autocompletion_up(
	t_command_line *command_line);

/*
** auto_completion.c
*/
int					process_advanced_completion(
	t_command_line *command_line, t_word word);
int					process_completion_expand(
	t_command_line *command_line, char *str, t_word word);
int					process_completion(
	t_command_line *command_line, t_word word);
int					process_tab(
	t_shell *shell, t_command_line *command_line);

/*
** auto_completion_tools.c
*/
char				*get_completion_str_file(t_file *file);
char				*get_completion_str(t_command_line *command_line);

/*
** debug_word.c
*/
void				print_word(t_word *word);

/*
** escape.c
*/
int					sh_should_escape(char c);
int					sh_escaped_len(char *str);
void				ft_strcat_escaped(char *dest, char *src);
char				*ft_strdup_escaped(char *str);
char				*ft_strjoin_escaped(char *s1, char *s2);

/*
** exec_tools.c
*/
int					sh_free_turn_exec_autocompletion(
	t_exec *exec, int ret);
int					sh_free_turn_exec(t_exec *exec, int ret);
void				init_exec(t_exec *exec);
void				init_exec_autocompletion(t_exec *exec);

/*
** file_tables.c
*/
void				fill_file_tables(
	t_command_line *command_line, t_file ***tbl);
int					init_file_tables(
	t_command_line *command_line, t_file ****res);
t_file				***update_file_tables(t_command_line *command_line);
void				free_tbl(t_file ***tbl, int width);

/*
** fill_buffer.c
*/
void				fill_buffer_padding(char **print_buffer);
void				process_fill_buffer_folder_suffix(
	int is_current, char **print_buffer, int *i);
void				process_fill_buffer_from_file(
	t_file *file, int is_current, char **print_buffer, int *i);
void				fill_buffer_from_file(
	t_command_line *command_line,
	char **print_buffer,
	t_file *file,
	int max_len);

/*
** fill_buffer_from_tables.c
*/
void				fill_buffer_from_tables(
	t_command_line *command_line,
	char *print_buffer,
	t_file ***tbl,
	int max_len);
void				fill_buffer_partial_from_tables(
	t_command_line *command_line,
	char *print_buffer,
	t_file ***tbl,
	int max_len);

/*
** left_arrow.c
*/
int					process_update_autocompletion_head_left(
	t_command_line *command_line,
	t_file *file_iter,
	t_file *file,
	t_dlist *ptr);
void				update_autocompletion_head_left(
	t_command_line *command_line);
int					process_autocompletion_left(
	t_command_line *command_line);

/*
** populate_choices.c
*/
int					add_choices_path(
	t_shell *shell, t_word *word, char *path_str);
int					populate_choices_from_binaries(
	t_shell *shell, t_word *word);
int					populate_choices_from_folder(
	t_shell *shell, t_word *word, int types);
int					populate_choices_from_word(
	t_command_line *cl, t_shell *shell, t_word *word);

/*
** populate_word_by_index.c
*/
int					populate_word_from_lexer_no_token(
	t_list **tokens, t_list **prev, t_word *word);
int					populate_word_from_token(t_word *word, int index);
int					populate_word_from_created_token(
	t_word *word, int index);
int					populate_word_from_lexer(
	t_list **tokens, int index, t_word *word);
int					populate_parsed_word_by_index(
	t_shell *shell, char *command, int index, t_exec *exec);

/*
** populate_word_by_index_no_parsing.c
*/
int					get_word_len(char *s, int index);
int					process_populate_empty_word(t_word *word);
int					process_populate_word_by_index(
	t_word *word, int nb_words, int parse_w, int index);
void				increment_word(
	int i, int index, t_word *word, char *str);
int					populate_word_by_index(
	char *s, int index, t_word *word);

/*
** preprocess_choice_add.c
*/
int					str_cmp_len(char *str1, char *str2);
void				process_dlst_iter(t_dlist **ptr, int *first);
int					process_preprocess_choice_add(
	t_command_line *command_line,
	char *entry,
	int *to_ret,
	t_dlist ***to_add);
int					ft_preprocess_choice_add(
	t_command_line *command_line, char *entry, t_dlist ***to_add);

/*
** render_choices.c
*/
int					render_choices(
	t_command_line *command_line, int *to_go_up);

/*
** render_choices_tools.c
*/
int					sh_get_file_len(t_file *file);
int					sh_get_max_file_len(t_dlist *dlist);
int					ft_round(float a);
int					lines_rendered_from_file(t_file *file);
int					command_line_visible_lines(
	t_command_line *command_line);

/*
** right_arrow.c
*/
int					process_update_autocompletion_head_right(
	t_command_line *command_line,
	t_file *file_iter,
	t_file *file,
	t_dlist *ptr);
void				update_autocompletion_head_right(
	t_command_line *command_line);
int					process_autocompletion_right(
	t_command_line *command_line);

#endif
