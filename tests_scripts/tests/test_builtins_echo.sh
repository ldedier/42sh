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

	launch_show "parser"
		test_launch 'echo -X h'
		test_launch 'echo -B h'
		test_launch 'echo -n -X h'
		test_launch 'echo -X -n h'
		# test_launch 'echo -nn h'
		test_launch 'echo --n h'
		test_launch 'echo -n -n -n hh'
		test_launch 'echo e -n -n -n hh'
		test_launch 'echo -X -n -n -n hh'

	launch_show "arguments"
		test_launch 'echo "" "" "" "" \" \" ok'
		test_launch 'echo "\"\"\""'
		test_launch 'echo "$var
		"'

	launch_show "quotes"
		test_launch 'echo simple test   without quote   !!'
		test_launch 'echo "simple test   with doublequote   !!"'
		test_launch "echo 'simple test   with doublequote   !!'"
		test_launch 'ec\ho \hey hey hey'
		test_launch "echo '\'hey \'hey hey"
		test_launch "l\s \-l \/"
		test_launch 'echo "\"\\\$$USER\$USER\\""'
		test_launch "echo '\"$USER\$USER'"

	launch_show "returned value"
		test_launch "echo 1>&-"
		test_launch "echo Okalm 1>&-"
		test_launch "echo -n Okalm 1>&-"
		test_launch "echo -n 1>&-"
		test_launch "echo -Z 1>&-"
		test_launch "echo -Z 2>&-"
		test_launch "echo 2>&-"
