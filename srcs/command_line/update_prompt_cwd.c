/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_prompt_cwd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 15:58:24 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/25 07:21:58 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		update_prompt_from_absolute_path(char *cwd, char **new_prompt)
{
	char	*path;

	if (get_path_from_absolute_path(cwd, &path))
	{
		free(cwd);
		return (sh_perror(SH_ERR1_MALLOC, "update_prompt_cwd (1)"));
	}
	free(cwd);
	if (!(*new_prompt = ft_strjoin_free(*new_prompt, path, 1)))
		return (sh_perror(SH_ERR1_MALLOC, "update_prompt_cwd (2)"));
	free(path);
	return (SUCCESS);
}

int		update_prompt_cwd_bonus_tilde(t_shell *shell,
			char **new_prompt, char *cwd, int *returned)
{
	char	*home;

	*returned = 1;
	if (!(home = get_home_dup(shell)))
	{
		free(*new_prompt);
		free(cwd);
		return (sh_perror(SH_ERR1_MALLOC, "update_prompt_cwd(5)"));
	}
	if (ft_strequ(home, cwd))
	{
		free(cwd);
		free(home);
		return (update_prompt_cwd_home(new_prompt));
	}
	free(home);
	*returned = 0;
	return (0);
}

int		update_prompt_cwd(t_shell *shell, char **new_prompt)
{
	char	*cwd;
	int		ret;
	int		returned;

	if (!(*new_prompt = ft_strdup("→ ")))
		return (sh_perror("cwd error", "update_prompt_cwd(3)"));
	if (!(cwd = sh_builtin_pwd_logical(shell->env)))
	{
		return (ft_free_turn(*new_prompt,
			sh_perror("Can't determine current working directory",
				"update_prompt_cwd (4)")));
	}
	if (BONUS_HOME_AS_TILDE_PROMPT)
	{
		ret = update_prompt_cwd_bonus_tilde(shell, new_prompt, cwd, &returned);
		if (returned)
			return (ret);
	}
	return (update_prompt_from_absolute_path(cwd, new_prompt));
}
