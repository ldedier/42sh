/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_globbing_for_substring_removal.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 05:50:11 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/08 06:19:36 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "sh_21.h"
int         parse_for_substring_removal(char *word, t_list **regexp_list)
{
    int     i;
    int     ret;
    i = 0;
    ret = SUCCESS;
    *regexp_list = NULL;
    ret = sh_regexp_parse_path_component(word, regexp_list);
    if (ret)
        ;// free regexp list if needed
    return (ret);
}
int         sh_globbing_for_substring_removal(char *param, char *word, t_list **matches)
{
    t_list      *regexp_list;
    int         ret;
    int         i;
    char        *buffer;
    if ((ret = parse_for_substring_removal(word, &regexp_list)) == FAILURE)// leaks ?
        return (ret);
    else if (ret == ERROR)
        return (SUCCESS);
    i = ft_strlen(param);
    *matches = NULL;
    while (i > 0)
    {
        param[i] = 0;
        dprintf(2, "trying to match : %s\n", param);
        if (sh_is_pattern_matching(param, regexp_list) == SUCCESS)
        {
            if (!(buffer = ft_strdup(param)))
                return (FAILURE); // leaks on regexp list, maybe more
            if (pattern_matching_push_new(matches, buffer))
                return (FAILURE); // same as up, (buffer is freed if error happend)
        }
        i--;
    }
    if (sh_verbose_globbing())
    {
        ft_lstput_fd(*matches, 2);
        ft_dprintf(2, "\n");
    }
    // ret = sh_expansions_pattern_matching(
    //  param, (t_list**)regexp_tab->tbl, &matches);
    return (SUCCESS);
    (void)param;
    (void)matches;
}
