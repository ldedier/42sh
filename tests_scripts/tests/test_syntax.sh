# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_syntax.sh                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:50 by jmartel           #+#    #+#              #
#    Updated: 2019/06/20 13:35:36 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Redirections tests
launch "syntaxe"
	test_launch "dqwdq"
	test_launch ";"
	test_launch ";;"
	test_launch ">>>>"
	test_launch ":>;:.>;"
	test_launch "<<-"

	test_launch "ls -l \""
	test_launch "ls -l \'"
	test_launch "ls \\" "-A"

finish
