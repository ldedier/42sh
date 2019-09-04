#include "sh_21.h"

char		*get_heredoc(t_context *context, t_heredoc *heredoc_data, int *ret)
{
	char 			*str;
	char			*stop;

	*(heredoc_data->apply_expansion) = 1;
	stop = heredoc_data->stop;
	if (ft_strchr(stop, '\'') || ft_strchr(stop, '\"') || ft_strchr(stop, '\\'))
	{
		*(heredoc_data->apply_expansion) = 0;
		if ((*ret = sh_expansions_scan(&stop, 0, 0, context, NULL)) != SUCCESS)
			return (NULL);
	}
	if (isatty(0))
		str = heredoc(context->shell, *heredoc_data, ret);
	else
		str = heredoc_canonical_mode(context->shell, stop, *heredoc_data, ret);
	return (str);
}
