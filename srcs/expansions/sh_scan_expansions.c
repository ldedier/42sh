#include "sh_21.h"

static void	backslash(char *input, int *index, int quoted)
{
	if (quoted)
	{
		if (input[*index + 1] == '$' || input[*index + 1] == '"'
			|| input[*index + 1] == '\\')
			ft_strcpy(input + *index, input + *index + 1);
		else if (input[*index + 1] == '\n')
			ft_strcpy(input + *index, input + *index + 2);
	}
	else
		ft_strcpy(input + *index, input + *index + 1);
	(*index) += 1;
}

static int	quote_expansion(
	char **input, int *index, char c, t_context *context)
{
	int	ret;

	ft_strcpy(*input + *index, *input + *index + 1);
	while ((*input)[*index] != c)
	{
		if (c == '"' && (*input)[*index] == '$')
		{
			if ((ret = sh_expansions_process(
				input, *input + *index, context, index)) != SUCCESS)
			{
				if (sh_env_update_ret_value_and_question(context->shell, ret))
					return (FAILURE);
				return (ret);
			}
		}
		else if (c == '"' && (*input)[*index] == '\\')
			backslash(*input, index, 1);
		else
			*index += 1;
	}
	ft_strcpy(*input + *index, *input + *index + 1);
	return (SUCCESS);
}

/*
** sh_scan_expansions:
** Scan input, starting at index
** Remove quote, doble quote and backslah.
** Replace variable with looking in context variables.
*/

int			sh_scan_expansions(char **input, int index, t_context *context)
{
	int	ret;

	while ((*input)[index] != '\'' && (*input)[index] != '"'
		&& (*input)[index] != '\\' && (*input)[index] != '$'
		&& (*input)[index])
		index++;
	if ((*input)[index] == '\0')
		return (SUCCESS);
	if ((*input)[index] == '\'' || (*input)[index] == '"')
	{
		if ((ret = quote_expansion(
			input, &index, (*input)[index], context)) != SUCCESS)
			return (ret);
	}
	else if ((*input)[index] == '$')
	{
		if ((ret = sh_unquoted_var(input, &index, context)) != SUCCESS)
			return (ret);
	}
	else
		backslash(*input, &index, 0);
	return (sh_scan_expansions(input, index, context));
}
