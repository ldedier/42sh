#include "sh_21.h"

/*
** Expansion apply to heredoc
*/

static int	loop_expansion(char **str, t_context *context)
{
	int	start_expansion;
	int ret;

	start_expansion = 0;
	while ((*str)[start_expansion])
	{
		if ((*str)[start_expansion] == '\\' && (*str)[start_expansion + 1] == '$')
		{
			ft_strcpy(*str + start_expansion, (*str) + start_expansion + 1);
			start_expansion++;
		}
		if ((*str)[start_expansion] == '$')
		{
			if ((ret = sh_expansions_process(str, (*str) + start_expansion, context, &start_expansion)) != SUCCESS)
			{
				if (sh_env_update_ret_value_and_question(context->shell, ret))
				{
					free(*str);
					return (FAILURE);
				}
			}
		}
		else
			start_expansion++;
	}
	return (SUCCESS);
}

int 	sh_traverse_io_here_expansion(char **str, t_context *context, int apply_expansion)
{
	ft_printf("expansion mon copain !!!!\n");
	if (apply_expansion == 0)
		return (SUCCESS);
	else
		return (loop_expansion(str, context));
}