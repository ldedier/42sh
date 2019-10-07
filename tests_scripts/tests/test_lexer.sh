# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_lexer.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:41 by jmartel           #+#    #+#              #
#    Updated: 2019/09/05 16:03:41 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Lexer"
	launch_show "Quotes"
	test_launch '"e"c"h"o lol' 'ls'
	test_launch '"echo" lol' 'ls'
	test_launch '""echo""  "" lol' 'ls'
	test_launch '""echo"" "lol"' 'ls'
	test_launch '"ech"o Okalm' 'ls'
	test_launch '"e"c"h"o lol' 'ls'
	test_launch '"e"c"h"o lol' 'ls'
	test_launch '"e"c"h"o lol' 'ls'
	test_launch '""""""ec""""h""o lol' 'ls'
	test_launch 'ec"ho lol' 'ls'

	echo "\"l\"\'\'\"l\"\\\\' '\pwd "  > file
	test_launch_pipe file
	echo "2'''  '\ \ \ \ \'\'\'\'\"\"\"\"\ \"        \"ls" > file
	test_launch_pipe file

	launch_show "lexer on expansion"
	test_launch '\ls \$HOME'
	test_launch '\ls $\H\O\M\E'
	test_launch 'l\s $HOME\'
	test_launch '""'
	test_launch '"\\\""\\ls'
	test_launch '"var=pwe" echo $var ; echo $var'
	
	launch_show "multiple lines"
	for i in `seq 1 22` ; do
		test_launch_pipe ./tests_files/lexer/lexer_${i}
	done
	for i in `seq 30 35` ; do
		test_launch_pipe ./tests_files/lexer/lexer_${i}
	done

	launch_show "Solo quotes"
	for i in `seq 23 29` ; do
		test_launch_pipe ./tests_files/lexer/lexer_${i}
	done
	
	launch_show "Random"
	test_launch '"var=pwe"'
	test_launch 'ls ""'

	launch_show	"Braces and parenthesis detection"
	test_launch '( ! ls ) && pwd'
	test_launch '( ! ls ) || pwd'
	test_launch '( ! ls && pwd )'
	test_launch '( ! ls || pwd )'
	test_launch '( VAR=foo ) ; echo $VAR'
	test_launch '( export VAR=foo ) ; echo $VAR'
	test_launch '( nocmd )'
	test_launch '( { echo jey } )'
	test_launch '( echo jey } )'
	test_launch '( echo jey } )'
	test_launch '{ echo lol { }} | cat -e ; }'

finish

rm file
