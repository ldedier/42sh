# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_pipes.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:47 by jmartel           #+#    #+#              #
#    Updated: 2019/09/05 15:36:31 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Pipes tests
launch "Pipes"
	launch_show "Simple"
		test_launch "ls | wc"
		test_launch "ls | wc | wc"
		test_launch "ls | wc | wc ; ls -a "
		test_launch "echo mdr | wc | cat -e | wc"
		test_launch "unknowncommand | exit | ls | wc | exit"
		test_launch "ls | wc | unknowncommand | ls | false | true | exit"
		test_launch "echo okal | cd .. ; pwd | true | unknowncommand | unknowncommand | exit"

	launch_show "on Builtins"
		test_launch 'pwd' 'cd ../../.. | echo lol | exit | echo lol' 'pwd'
		test_launch 'exit | exit'
		test_launch 'exit | true | exit'
		test_launch 'yes | head -c1'
		test_launch 'cat | cat | wc'
		test_launch 'emacs | emacs'
		test_launch 'cat start.sh | wc | cat 1>&2 | ls | cat sd | ls'
		test_launch 'env ls | cat | wc'
		test_launch 'env echo tamre | wc'
		test_launch 'env cd .. ; exit | echo asd'

	launch_show "here documents"
		test_launch '<<eof cat' 'olqsd' 'qdza ' 'eof' 'ls'
		test_launch '<<eof cat | wc' 'olqsd' 'qdza ' 'eof' 'ls'
		test_launch '3<<eof cat' 'olqsd' 'qdza ' 'eof' 'ls'
		test_launch '3<<eof cat | wc' 'olqsd' 'qdza ' 'eof' 'ls'
		test_launch '1<<eof cat' 'olqsd' 'qdza ' 'eof' 'ls'
		test_launch '1<<eof cat | wc' 'olqsd' 'qdza ' 'eof' 'ls'
		test_launch '1<<eof 2<<eof2 cat' 'olqsd' 'eof' 'tamer' 'eof2' 'ls'
		test_launch '1<<eof 2<<eof2 cat | wc' 'olqsd' 'eof' 'tamer' 'eof2' 'ls'
		test_launch '2<<eof 1<<eof2 cat' 'olqsd' 'eof' 'tamer' 'eof2' 'ls'
		test_launch '2<<eof 1<<eof2 cat | wc' 'olqsd' 'eof' 'tamer' 'eof2' 'ls'

	launch_show "duplicating fd"
		test_launch "rm -f file" "./obj/fd_write 1 okalm > file ; cat file | wc ; rm file"
		test_launch "rm -f file" "./obj/fd_write 3 okalm 3>file ; cat file" "rm file"
		test_launch "rm -f file" "./obj/fd_write 5 string 3>f3 4>f4 5>f5" "echo 3 ; cat f3" "echo 4 ; cat f4" "echo 5 ; cat f5" "rm f3 f4 f5"
		test_launch "rm -f file" "./obj/fd_write 1 okalm 1>&- 1>&- 1>&2 1>&-"
		test_launch "rm -f file" "./obj/fd_write 4 okalm 4>&- 4>&- 4>&1 4>&-"
		test_launch "rm -f file" "./obj/fd_write 4 okalm 4>&1 4>&2 4>&3 3>file ; cat file ; rm file"
		test_launch "rm -f file" "./obj/fd_write 4 okalm 4>&1 4>&2 3>file ; cat file ; rm file"

	launch_show "asynchronous"
		test_launch "sleep 0.1 | ls ; echo lol"
		test_launch 'pwd ; cd ..  | echo | exit ; pwd'
		test_launch 'true | exit'
		test_launch 'yes | head -c1'

	rm -f file

finish
