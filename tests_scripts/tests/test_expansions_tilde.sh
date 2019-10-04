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

launch "Tilde_expansion"
	launch_show "Normal tests"
	test_launch 'ls -a ~/'
	test_launch 'ls ~' 'ls ~ '
	test_launch 'echo ~'
	test_launch 'echo ~' 'echo $?'
	test_launch 'asd ~/'
	test_launch 'echo ~asdqw/'
	test_launch 'cd ~d/' 'ls' 'cd ~/' 'ls'
	test_launch 'ls -a ~$easd'

	launch_show "Hard tests"
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

	launch_show "Quote tests"
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

	launch_show "Old errors"
	test_launch 'echo ~okalm'
	test_launch 'echo ~okalm\'
	test_launch 'echo ~okalm\ '
	test_launch 'echo ~okalm\d'
	test_launch 'echo ~:'
	test_launch 'echo ~~:'
	test_launch 'echo ~~/'
	test_launch 'var=~:~/: ; echo $var'
	test_launch 'var=~/:~::: ; echo $var'
	test_launch 'var=~/:~//::: ; echo $var'
	test_launch 'var=:~/:~/::: ; echo $var'
	test_launch 'var=:~/:~/::: ; echo $var'
	test_launch 'var=:~root/:~jmartel/::: ; echo $var'
	test_launch 'var=:~root/:~/jmartel::: ; echo $var'
	test_launch 'var=:~root/root::~jmartel:~root: ; echo $var'
	test_launch 'var=:~root/~root::~jmartel:~root: ; echo $var'
	test_launch 'var=:~root/~root/::~jmartel:~root: ; echo $var'
	test_launch 'var=:~root/root/~root/::~jmartel:~root: ; echo $var'


	launch_show "Bonus"
		test_launch 'ls ~jmartel/'
		test_launch 'ls ~jmartel//'
		test_launch 'ls ~jmartel'
		test_launch 'ls ~root/'
		test_launch 'ls ~root:'
		test_launch 'ls ~root//'
		test_launch 'ls ~root'
		test_launch 'ls ~noone'
		test_launch 'ls ~noone/'
		test_launch 'ls ~noone//'

finish