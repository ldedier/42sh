#include "sh_21.h"

/*
** Expansion apply to heredoc
*/

static int	is_valid_var(char c)
{
	if (ft_isalnum(c))
		return (1);
	else if (c == '$' || c == '?')
		return (1);
	else if (c == '{')
		return (1);
	return (0);
}

int 	sh_traverse_io_here_expansion(char **str, int *start_expansion, t_context *context)
{
	int ret;

	if ((*str)[*start_expansion] == '$' && is_valid_var((*str)[*start_expansion + 1]))
	{
		if ((ret = sh_expansions_process(str, (*str) + *start_expansion, context, start_expansion)) != SUCCESS)
		{
			if (sh_env_update_ret_value_and_question(context->shell, ret))
				return (FAILURE);
			return (ERROR);
		}
	}
	else
		(*start_expansion) += 1;
	return (SUCCESS);
}