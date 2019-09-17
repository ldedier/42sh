/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_fc_s_synopsis.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:46:05 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/17 21:37:12 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	fill_finder(t_fc_operand **finder,
	t_fc_options *opts, char **substitution_str)
{
	if (!opts->from.parsed)
	{
		opts->from.un.integer = -1;
		opts->from.type = E_FC_INTEGER;
		opts->from.parsed = 1;
		*finder = &opts->from;
	}
	else if (opts->from.type == E_FC_STRING
			&& ft_strchr(opts->from.un.string, '=') && !opts->to.parsed)
	{
		opts->to.un.integer = -1;
		opts->to.type = E_FC_INTEGER;
		opts->to.parsed = 1;
		*substitution_str = opts->from.un.string;
		*finder = &opts->to;
	}
	else
		*finder = &opts->from;
}

char	*ft_substitute_occurences(char *str,
	char *to_replace, char *replacement)
{
	(void)str;
	(void)to_replace;
	(void)replacement;
	return (NULL);
}

char	*get_command_to_execute_fc(char *command, char *substitution_str)
{
	char	*to_replace;
	char	*replacement;
	int		equal_index;
	char	*res;

	if (!substitution_str)
		return (ft_strdup(command));
	else
	{
		equal_index = ft_strichr(substitution_str, '=');
		if (!(to_replace = ft_strndup(substitution_str, equal_index)))
			return (NULL);
		if (!(replacement = ft_strdup(&substitution_str[equal_index + 1])))
		{
			free(to_replace);
			return (NULL);
		}
		if (!(res = ft_substitute_occurences(command,
				to_replace, replacement)))
			return (ft_free_turn_strs(&replacement, &to_replace, NULL));
		free(replacement);
		free(to_replace);
		return (res);
	}
}

int		sh_builtin_fc_s_synopsis(t_context *context, t_fc_options *opts)
{
	t_dlist			*entry_ptr;
	t_fc_operand	*finder;
	char			*substitution_str;
	char			*res;
	t_entry			*entry;

	substitution_str = NULL;
	fill_finder(&finder, opts, &substitution_str);
	if (!(entry_ptr
		= get_entry_from_fc_operand(&context->shell->history, finder)))
	   	return (sh_perror_err(SH_BLT_NO_CMD_FOUND, NULL));
	entry = entry_ptr->content;
	if (!(res = get_command_to_execute_fc(entry->command, substitution_str)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_builtin_fc_s_synopsis"));
	ft_printf("RES: %s\n", res);
	free(res);
	return (SUCCESS);
}
