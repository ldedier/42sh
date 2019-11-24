/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 13:41:08 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/24 15:23:14 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_init_terminal_database(char **env)
{
	char	*termtype;
	int		success;

	if ((termtype = sh_env_get_value(env, "TERM")))
		success = tgetent(NULL, termtype);
	else
		success = tgetent(NULL, DEFAULT_TERM);
	if (success < 0)
	{
		return (sh_perror("Could not access the termcap data base",
				"sh_init_terminal_database"));
	}
	if (success == 0)
	{
		return (sh_perror("The terminal specified is not defined",
					"sh_init_terminal_database"));
	}
	if (sh_check_term() != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

int		sh_set_term_sig(int value)
{
	if (!value)
		g_glob.term.c_lflag &= ~(ISIG);
	else
		g_glob.term.c_lflag |= ISIG;
	if (tcsetattr(g_term_fd, TCSANOW, &g_glob.term) == -1)
	{
		return (sh_perror("Could not modify this terminal attributes",
			"sh_init_terminal"));
	}
	return (SUCCESS);
}

int		sh_init_terminal(t_shell *shell, char **env)
{
	if (sh_init_terminal_database(env))
		return (1);
	if (tcgetattr(g_term_fd, &g_glob.term_init) == -1)
		return (sh_perror(SH_ERR1_TERM_CPY, "sh_init_terminal"));
	if (tcgetattr(g_term_fd, &shell->term) == -1)
		return (sh_perror(SH_ERR1_TERM_CPY, "sh_init_terminal"));
	shell->term.c_lflag &= ~(ICANON);
	shell->term.c_lflag &= ~(ECHO);
	shell->term.c_lflag &= ~(ISIG);
	shell->term.c_cc[VMIN] = 1;
	shell->term.c_cc[VTIME] = 0;
	if (tcsetattr(g_term_fd, TCSANOW, &shell->term) == -1)
	{
		return (sh_perror("Could not modify this terminal attributes",
			"sh_init_terminal"));
	}
	if (ioctl(g_term_fd, TIOCGWINSZ, &g_glob.winsize) == -1)
		return (1);
	g_glob.term = shell->term;
	return (0);
}
