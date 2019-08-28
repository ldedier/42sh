/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unquoted_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 14:59:03 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/08/03 14:59:05 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int	sh_unquoted_var(char **input, int *index, t_context *context)
{
	int	ret;

	if ((ret = sh_expansions_process(
		input, *input + *index, context, index)) != SUCCESS)
	{
		if (sh_env_update_ret_value_and_question(context->shell, ret))
			return (FAILURE);
		return (ret);
	}
	return (SUCCESS);
}
