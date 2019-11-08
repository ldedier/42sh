/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:43:57 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 19:44:01 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	print_word(t_word *word)
{
	ft_printf("\nstr: %s\n", word->str);
	ft_printf("to compare: %s\n", word->to_compare);
	ft_printf("len: %d\n", word->len);
	ft_printf("utf8_len: %d\n", word->utf8_len);
	ft_printf("start_index: %d\n", word->start_index);
	ft_printf("index_char_offset: %d\n", word->index_char_offset);
	ft_printf("index_byte_offset: %d\n", word->index_byte_offset);
}
