# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins_echo.sh                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/22 19:04:50 by jmartel           #+#    #+#              #
#    Updated: 2019/08/22 19:05:15 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Echo"
	test_launch "echo -n okalm"
	test_launch "echo -n "
	test_launch "echo"
	test_launch "echo okalm"
	test_launch 'echo $env'
	test_launch 'echo $TERM'
	test_launch 'echo $poasd'
	test_launch 'echo $TERM $PATH'
	test_launch 'echo -n $TERM $PATH'
	test_launch 'echo $var $var $var'
	test_launch 'echo $s#var $var'
	test_launch 'echo "" "" "" "" okalm'
	test_launch 'echo -n -n -n ls -n'

	launch "parser"
	launch "arguments"
	launch "returned value"

launch "write echo"
	test_launch "echo 1>&-"
	test_launch "echo Okalm 1>&-"
	test_launch "echo -n Okalm 1>&-"
	test_launch "echo -n 1>&-"
	test_launch "echo -Z 1>&-"
	test_launch "echo -Z 2>&-"
	test_launch "echo 2>&-"

