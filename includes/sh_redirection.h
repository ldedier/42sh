/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_redirection.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:58:00 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/23 20:42:20 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_REDIRECTION_H
# define SH_REDIRECTION_H

# define DGREAT_OPT					(O_WRONLY | O_APPEND | O_CREAT)
# define GREAT_OPT					(O_WRONLY | O_TRUNC | O_CREAT)

typedef enum		e_redirection_type
{
	INPUT,
	OUTPUT,
	PIPE
}					t_redirection_type;

typedef struct			s_redirection
{
	t_redirection_type	type;
	int					redirected_fd;
	int					fd;
	int					backup;
	int					was_closed;
}						t_redirection;


/*
********************************************************************************
*/

/*
** sh_add_redirection.c
*/
int 				sh_add_redirection_file(
	t_redirection_type type,
	int redirected_fd,
	int fd,
	t_list **list);
int					sh_add_redirection_aggreg(
	t_redirection_type type,
	int redirected_fd,
	int fd,
	t_list **list);
int 				sh_add_redirection_pipe(int fd, t_list **list);

/*
** sh_check_open_fd.c
*/
int					is_open(int fd);
int					sh_check_open_fd(t_redirection_type type, int fd);
int					sh_check_dst_fd(
	t_list *lst, t_redirection_type type, int fd);
int 				sh_check_src_fd(
	t_list *head, t_redirection *curr_redir);

/*
** sh_reset_redirection.c
*/
int					sh_reset_redirection(t_list **lst);

#endif
