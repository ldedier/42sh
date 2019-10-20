# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_globbing.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 05:23:32 by jmartel           #+#    #+#              #
#    Updated: 2019/10/20 05:46:50 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Globbing"
	launch_show "Simple"
	test_launch 'echo *'
	test_launch 'echo ?*'
	test_launch 'echo *?'
	test_launch 'echo ?*?'
	test_launch 'echo .*'
	test_launch 'echo ./*'

	launch_show ""
	
	launch_show "Correction"
	test_launch 'mkdir -p empty ; cd empty' 'touch a? b* [c]; ls -1'
	test_launch 'cd empty' 'echo a > aa && echo b > ab && cat -e a?'
	test_launch 'cd empty' 'rm -f *' 'ls'
	test_launch 'cd empty' 'mkdir -p one/two'
	test_launch 'cd empty' 'echo "four" > one/two/three'
	test_launch 'cd empty' 'echo "four" > one/five'
	test_launch 'cd empty' 'cat ./*/*/* ./*/*'
	test_launch 'cd empty' 'ls /??r'
	test_launch 'cd empty' 'rm -rf ./*' 'ls'
	test_launch 'cd empty' 'mkdir "[x" && touch "[x/foo"'
	test_launch 'cd empty' 'echo [*; echo *[x; echo [x/*'
	test_launch 'cd empty' 'rm -rf *'
	test_launch 'cd empty' 'touch "a[a-z][x" "ab[x"'
	test_launch 'cd empty' 'echo a[a-z][*; echo a[a-z]*; echo a[a\-z]*'
	test_launch 'cd empty' 'rm -f *'
	test_launch 'cd empty' 'touch ".bc" "abc" "bbc" "cbc" "-bc" \!bc "+bc" ",bc" "0bc" "1bc"'
	test_launch 'cd empty' 'echo [ab-]*'
	test_launch 'cd empty' 'echo [-ab]*'
	test_launch 'cd empty' 'echo [!-ab]*'
	test_launch 'cd empty' 'echo [!ab]*'
	test_launch 'cd empty' 'echo []ab]*'
	test_launch 'cd empty' 'echo [+--]*'
	test_launch 'cd empty' 'echo [--1]*'
	test_launch 'cd empty' 'echo [z-a]*'
	test_launch 'cd empty' 'echo [a-a]bc'
	test_launch 'cd empty' 'rm -f * .*; ls -A'
	test_launch 'cd empty' 'touch aa bb cc 11 22 33'
	test_launch 'cd empty' 'echo **'
	test_launch 'cd empty' 'echo [!a-z]'
	test_launch 'cd empty' 'echo [4-z][A-b]'
	test_launch 'rm -rf empty'

finish
