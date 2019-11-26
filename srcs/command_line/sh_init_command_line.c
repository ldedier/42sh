/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_command_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:22:42 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/26 08:47:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	sh_init_count(t_command_count *count)
{
	count->active = 0;
	count->tmp_value = 1;
}

static int	sh_init_command_line_ret(t_shell *shell,
		t_command_line *command_line)
{
	command_line->fd = g_term_fd;
	if (!(command_line->searcher.dy_str = ft_dy_str_new(63)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_init_command_line (2)"));
	command_line->searcher.active = 0;
	command_line->searcher.head = NULL;
	command_line->searcher.unsuccessful = 0;
	command_line->prompt = NULL;
	command_line->to_append_str = NULL;
	command_line->prev_prompt_len = -1;
	if (update_prompt(shell, command_line) == FAILURE)
		return (FAILURE);
	command_line->clipboard = NULL;
	if (!(command_line->dy_str = ft_dy_str_new(63)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_init_command_line (3)"));
	return (SUCCESS);
}

int			sh_init_command_line(t_shell *shell, t_command_line *command_line)
{
	command_line->edit_counter = 0;
	sh_init_count(&command_line->count);
	sh_init_count(&command_line->motion_count);
	command_line->current_count = &command_line->count;
	command_line->shell = shell;
	command_line->edit_line = NULL;
	command_line->saves_stack = NULL;
	command_line->last_ft_command.motion = NULL;
	command_line->last_ft_command.locked = 0;
	command_line->autocompletion.choices = NULL;
	command_line->autocompletion.head = NULL;
	command_line->autocompletion.active = 0;
	command_line->interrupted = 0;
	command_line->autocompletion.scrolled_lines = 0;
	command_line->pinned_index = -1;
	command_line->scrolled_lines = 0;
	command_line->context = E_CONTEXT_STANDARD;
	command_line->edit_style = E_EDIT_STYLE_READLINE;
	command_line->mode = E_MODE_INSERT;
	return (sh_init_command_line_ret(shell, command_line));
}
