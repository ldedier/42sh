# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_lexer.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:41 by jmartel           #+#    #+#              #
#    Updated: 2019/11/15 06:51:55 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Lexer"
	launch_show 'reserved_words'
	test_launch '{ echo hi ; { ls } ; }' 'echo $?'
	test_launch ' { echo lol } | { cat -e }' 'echo $?'
	test_launch 'echo {}' 'echo $?' 'echo { }' 'echo $?'
	test_launch '{ export ABC=def; env|grep ABC; }; env|grep ABC|cat -e' 'echo $?'
	test_launch '{ echo baz; echo buz >out2; } >out' 'cat out ; echo $? ; cat out2 ; echo $?' 'rm -f out out2'

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
	
	launch_show "Alias substitution"
	for i in `seq 1 11` ; do
		test_launch_pipe ./tests_files/alias/alias_${i}
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

	launch_show "unclosed pipe"
	test_launch 'pwd | cat -e' 'pwd |' 'cat -e' 'echo $?'
	test_launch 'pwd |' 'cat -e' 'pwd' 'echo $?'
	test_launch 'pwd |' 'echo $?'
	test_launch 'pwd |' 'cat -e |' 'cat -e' 'echo $?'
	test_launch 'ls | | pwd' 'echo $?'
	test_launch 'ls | cat -e | ' 'echo $?'
	test_launch '|' 'echo $?'

	launch_show "unclosed expansions"
	test_launch 'echo `ls'  'echo $?'
	test_launch 'echo `ls' '-A' 'echo $?'
	test_launch 'echo ${param' 'echo $?'
	test_launch 'echo $(param' 'echo $?'
	test_launch 'echo <(param' 'echo $?'
	test_launch 'echo >(param' 'echo $?'

finish

rm -f file
