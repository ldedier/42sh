/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 11:03:06 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/09/12 04:54:36 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

char	*get_heredoc(t_context *context, t_heredoc *heredoc_data, int *ret)
{
	char			*str;
	char			*stop;

	stop = heredoc_data->stop;
	if (isatty(0))
		str = heredoc(context->shell, *heredoc_data, ret);
	else
		str = heredoc_canonical_mode(context->shell, stop, *heredoc_data, ret);
	return (str);
}
