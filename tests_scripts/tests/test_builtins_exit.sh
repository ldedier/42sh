# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins_exit.sh                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/22 19:04:52 by jmartel           #+#    #+#              #
#    Updated: 2019/08/22 19:05:15 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "exit"
	launch_show "parser"
	test_launch 'exit ; ls'
	test_launch 'exit' 'ls'
	test_launch 'exit && ls'
	test_launch 'exit && ls ; ls'
	test_launch 'exit || ls'
	test_launch 'exit 1 ; echo $?'
	test_launch 'exit 12 ; echo $?'
	test_launch 'echo tamer ; exit 3 ; echo $?'
	test_launch 'exit 123 ; echo $?'
	
	launch_show "arguments"
	test_launch 'exit asd qwe ; ls'
	test_launch 'exit 15 2 ; ls'
	test_launch 'exit 13 asd ; ls'
	test_launch 'exit eqw 13 ; ls'
	test_launch 'exit -1 ; ls '
	test_launch 'exit asd qwe || ls'
	test_launch 'exit 15 2 || ls'
	test_launch 'exit 13 asd || ls'
	test_launch 'exit eqw 13 || ls'
	test_launch 'exit -1 || ls '

	test_launch 'exit asd qwe && ls'
	test_launch 'exit 15 2 && ls'
	test_launch 'exit 13 asd && ls'
	test_launch 'exit eqw 13 && ls'
	test_launch 'exit -1 && ls '

	test_launch 'exit 2 ; ls'
	test_launch 'exit 1234 ; ls'
	test_launch 'exit 256 ; ls '
	test_launch 'exit 255 ; ls'
	test_launch 'nocmd ; exit '
	test_launch 'nocmd ; exit 18'
	test_launch 'false || exit 18'
	test_launch 'false && exit 18'
	test_launch 'exit 1 | exit 2 | exit 3 | ls'

	launch_show "returned value"

	launch_show "write error"
	test_launch "exit 1>&-"
	test_launch "exit Okalm 1>&-"
	test_launch "exit Okalm 2>&-"
	test_launch "exit 2 2 2 2>&-"
	test_launch "exit 2 2 2 2>&-"
