# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_expansions_tilde.sh                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/06 16:09:28 by jmartel           #+#    #+#              #
#    Updated: 2019/09/04 11:54:12 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Tilde expansion"
launch "Normal tests"
	test_launch 'ls -a ~/'
	test_launch 'ls ~' 'ls ~ '
	test_launch 'echo ~'
	test_launch 'echo ~' 'echo $?'
	test_launch 'asd ~/'
	test_launch 'echo ~asdqw/'
	test_launch 'cd ~d/' 'ls' 'cd ~/' 'ls'
	test_launch 'ls -a ~$easd'

launch "Hard tests"
	test_launch 'echo ~~~~~~~~' 
	test_launch 'echo ~~~~~~~~' 'echo $?'
	test_launch 'echo ~~~~~~~~///////'
	test_launch 'echo ~/~/~/~/~/~/~/~/'
	test_launch 'echo /~'
	test_launch 'echo asdq~'
	test_launch 'echo weq~asd'
	test_launch 'echo okalm~'
	test_launch 'echo ~oadasd'
	test_launch 'echo ~as\dasdas/'
	test_launch 'echo ~as"dasd"as/'

launch "Quote tests"
	test_launch 'echo ~    /~ /~ "~"'
	test_launch 'echo "~"\~' 
	test_launch 'echo "~"\~' 'echo $?'
	test_launch 'echo "~/"~/~/~/~/~/~/~/'
	test_launch 'echo "/~"'
	test_launch 'echo "asdq~"'
	test_launch 'ls -A "~/""'
	test_launch 'ls "~"' 'ls ~ '
	test_launch "echo '~''"
	test_launch 'echo \~'
	test_launch 'asd \~\/'
	test_launch 'echo \~asdqw/'
	test_launch 'cd \~d/' 'ls' 'cd "~/"' 'ls'
	test_launch 'cd \~d/' 'ls' 'cd '\''~/'\''' 'ls'

# launch "Deprecated"
	# test_launch 'ls ~jmartel/'
finish