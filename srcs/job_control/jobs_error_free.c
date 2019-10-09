/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_error_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 02:00:14 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/08 16:17:44 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_perror.h"

int		jobs_error_free(const char *err, const char *suff, int to_free, int ret)
{
	if (to_free)
		job_control_free();
	sh_perror(err, suff);
	return (ret);
}