# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_syntax.sh                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:50 by jmartel           #+#    #+#              #
#    Updated: 2019/11/15 06:49:18 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Redirections tests
launch "syntaxe"
	test_launch "dqwdq" 'echo $?'
	test_launch ";" 'echo $?'
	test_launch ";;" 'echo $?'
	test_launch ">>>>" 'echo $?'
	test_launch ":>;:.>;" 'echo $?'
	test_launch "<<-" 'echo $?'

	test_launch "ls -l \"" 'echo $?'
	test_launch "ls -l \'" 'echo $?'
	test_launch "ls \\" "-A" 'echo $?'

finish
