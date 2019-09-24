# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins_2.sh                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/06 16:09:28 by jmartel           #+#    #+#              #
#    Updated: 2019/08/18 11:50:13 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Builtins (2)"
	launch_show "type"
	# launch "parser"
	# test_launch 'type -q '
	# test_launch 'type -z -q -r'
	# test_launch 'type -v -e -l'

	launch_show "Simple tests"
	test_launch 'type ; echo $?'
	test_launch 'type [['
	test_launch 'type { }'
	test_launch 'type ]]'
	test_launch 'type ]'
	test_launch 'type -- ; echo $?'
	test_launch 'type -a -- ls; echo $?'
	test_launch 'type -a -- bash; echo $?'
	test_launch 'type -- -a bash; echo $?'
	test_launch 'type ls cd brew type'
	test_launch 'type ls cd brew none type'
	test_launch 'type ls cd brew type none'
	test_launch 'ls ; type ls cd brew type while'
	test_launch 'ls ; type ls cd none brew type while'
	test_launch 'ls' 'type ls cd brew type while'
	test_launch 'ls' 'type ls cd brew none type while'

	test_launch 'type -aa cd ls brew while type'
	test_launch 'type -p ls brew while type'
	test_launch 'type -t cd ls brew while type'
	test_launch 'type -a -p -t -a cd ls brew while type'
	test_launch 'type -a -- p cd ls brew while type'
	test_launch 'type -a -p -- -t cd ls brew while type'
	test_launch 'type --t --a cd ls brew while type'
	test_launch 'type -t -a- cd ls brew while type'
	test_launch 'type -a cd ls brew while type -a'
	test_launch 'type cd ls brew while type'
	test_launch 'type -p -t cd ls brew  type while'
	test_launch 'type -t -p cd ls brew  type while'
	test_launch 'type -a -p -t cd ls brew  type while'
	test_launch 'type -a -t -p cd ls brew type while'
	test_launch 'type -p -t -a cd ls brew  type while'
	test_launch 'type -t -p -a cd ls brew  type while'
	test_launch 'ls' 'type -p -t cd ls brew  type while'
	test_launch 'ls' 'type -t -p cd ls brew  type while'
	test_launch 'ls' 'type -a -p -t cd ls brew  type while'
	test_launch 'ls' 'type -a -t -p cd ls brewe type while'

	launch_show "write"
	test_launch "type 1>&-"
	test_launch "type ls 1>&-"
	test_launch "type nothing 1>&-"
	test_launch "type -E 1>&-"
	test_launch "type -E 2>&-"
	test_launch "type 2>&-"


finish