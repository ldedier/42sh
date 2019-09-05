/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_autocompletion.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:59:37 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/03 00:01:48 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_AUTOCOMPLETION_H
# define SH_AUTOCOMPLETION_H

# include "libft.h"

# define AC_PADDING		2

# define DIR_COLOR		BOLD RED

typedef struct s_shell			t_shell;
typedef struct s_command_line	t_command_line;

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
	char			*str;
	char			*to_compare;
	int				start_index;
	int				word_index;
	int				prev_word_index;
	int				len;
	int				utf8_len;
	int				index_byte_offset;
	int				index_char_offset;
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

/*
********************************************************************************
*/

/*
** add_choices_from_dir.c
*/
void				add_node_next_to_node(t_dlist **node, t_dlist *to_add);
int					process_add_choices_from_dir(
	t_shell *shell,
	t_command_line *command_line,
	struct dirent *entry,
	char *prefix);
int					add_choices_from_dir(
	t_shell *shell, t_word *word, char *dirname, char *prefix);

/*
** auto_completion_tools.c
*/
char				*get_completion_str_file(t_file *file);
char				*get_completion_str(t_command_line *command_line);

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
** populate_word_by_index.c
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
** add_choices_builtins.c
*/
int					process_add_choices_from_name(
	t_shell *shell, t_command_line *command_line, char *name);
int					add_choices_builtins(t_shell *shell, t_word *word);

/*
** populate_choices.c
*/
int					add_choices_path(
	t_shell *shell, t_word *word, char *path_str);
int					populate_choices_from_binaries(
	t_shell *shell, t_word *word);
int					populate_choices_from_folder(
	t_shell *shell, t_word *word);
int					populate_choices_from_word(
	t_command_line *command_line, t_shell *shell, t_word *word);

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
** render_choices_tools.c
*/
int					sh_get_file_len(t_file *file);
int					sh_get_max_file_len(t_dlist *dlist);
int					ft_round(float a);
int					lines_rendered_from_file(t_file *file);
int					command_line_visible_lines(
	t_command_line *command_line);

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
** render_choices.c
*/
char				*new_print_buffer(void);
int					sh_should_render_choices(
	t_command_line *command_line, int nb_visible_lines);
void				update_dimensions(
	t_command_line *command_line, int max_len);
void				update_back_nb_cols(t_command_line *command_line);
int					render_choices(t_command_line *command_line);

/*
** arrows_vertical.c
*/
int					process_autocompletion_down(
	t_command_line *command_line);
int					process_autocompletion_up(
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

/*
** arrow_tools.c
*/
void				process_autocompletion_switch(
	t_command_line *command_line, t_file *prev_file, t_file *file);
int					substitute_command_str_from_str(
	t_command_line *command_line, char *from, char *str);
int					substitute_command_str(
	t_command_line *command_line, char *str);

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

#endif
