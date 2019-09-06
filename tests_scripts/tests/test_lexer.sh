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
	launch "Quotes"
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

	launch "lexer on expansion"
	test_launch '\ls \$HOME'
	test_launch '\ls $\H\O\M\E'
	test_launch 'l\s $HOME\'
	test_launch '""'
	test_launch '"\\\""\\ls'
	
	launch "multiple lines"
	test_launch '"var=pwe" echo $var ; echo $var'

	test_launch '\ls "
	okalm"'

	for i in `seq 1 21` ; do
		test_launch_pipe ./tests_files/lexer/lexer_${i}
	done

	echo "ls \\" > file ; echo "-a" >>file
	test_launch_pipe file

	launch "Solo quotes"
	test_launch '"'
	test_launch "'"
	test_launch '\'
	echo -n \' > file
	test_launch_pipe file
	echo -n \" > file
	test_launch_pipe file
	echo -n \\ > file
	test_launch_pipe file
	
	echo \\ > file ; for i in 1 2 3 4 ; do echo \\ >> file ; done ; echo -n ls >> file ; test_launch file
	echo \" > file ; for i in 1 2 3 4 ; do echo \\ >> file ; done ; echo -n \"ls >> file ; test_launch file
	echo \\ > file ; for i in 1 2 3 4 ; do echo ls >> file ; done ; echo -n \" >> file ; test_launch file
	echo ls > file ; for i in 1 2 3 4 ; do echo " \\" >> file ; done ; echo -n -la >> file ; test_launch file

	launch "Random"
	test_launch '"var=pwe"'
	test_launch 'ls ""'

finish

rm file
