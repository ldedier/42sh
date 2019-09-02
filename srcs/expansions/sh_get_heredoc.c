#include "sh_21.h"

static int	loop_expansion(char **str, t_context *context)
{
	int	start_expansion;
	int ret;

	start_expansion = 0;
	while ((*str)[start_expansion])
	{
		if ((*str)[start_expansion] == '\\' && (*str)[start_expansion + 1] == '$')
		{
			ft_strcpy(*str, (*str) + 1);
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

char		*get_heredoc(t_context *context, char **stop,
		char *(*heredoc_func)(const char *), int *ret)
{
	int 			do_expansion;
	char 			*str;

	do_expansion = 1;
	if (ft_strchr(*stop, '\'') || ft_strchr(*stop, '\"') || ft_strchr(*stop, '\\'))
	{
		do_expansion = 0;
		if ((*ret = sh_scan_expansions(stop, 0, do_expansion, context)) != SUCCESS)
			return (NULL);
	}
	if (isatty(0))
		str = heredoc(context->shell, *stop, heredoc_func, ret);
	else
		str = heredoc_canonical_mode(context->shell, *stop, heredoc_func, ret);
	if (*ret == SUCCESS && do_expansion)
		*ret = loop_expansion(&str, context);
	return (str);
}
