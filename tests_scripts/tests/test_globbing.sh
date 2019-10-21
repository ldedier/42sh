# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_globbing.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 05:23:32 by jmartel           #+#    #+#              #
#    Updated: 2019/10/21 08:06:35 by jmartel          ###   ########.fr        #
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

	launch_show "brace"
	test_launch 'mkdir -p sandbox' 'cd sandbox ' 'touch a b c d aa bb cc dd ab cd bc file1 file2 file3 file4 "[ab]" "[" "]" "[aa" "a]a" \!'
	test_launch 'cd sandbox' 'echo [a] ; echo $?' 'echo [a]* ; echo $?' 'echo [!a] ; echo $?'
	test_launch 'cd sandbox' 'echo [a-a][a-a] ; echo $?' 'echo [!a][!a] ; echo $?' 'echo [!] ; echo $?'
	test_launch 'cd sandbox' 'echo [a-aa-ab-bb-b] ; echo $?' 'echo [!a-aa-ab-bb-b] ; echo $?' 'echo [!a-a!a-a!b-bb-b] ; echo $?' 'echo [!a-aa-ab-b!b!-b] ; echo $?'
	test_launch 'cd sandbox' 'echo [!] ; echo $?' 'echo [\!] ; echo $?' 'echo [!\!] ; echo $?' 'echo [!!] ; echo $?'
	launch_show "brace quoted"
	test_launch 'cd sandbox' 'echo [!a-ba\ ]'
	test_launch 'cd sandbox' 'echo "[!a-bz ]"' 'echo "[!a-bz]"'
	test_launch 'cd sandbox' ''
	test_launch 'cd sandbox' ''
	test_launch 'cd sandbox' ''

	launch_show "star"
	test_launch 'cd sandbox' 'echo *' 'echo *' 'echo .*' 'echo ./*' 'echo **' 'echo ***'
	test_launch 'cd sandbox' 'echo \*'
	test_launch 'cd sandbox' 'echo ../**/../**' 'echo [a]*[b] ; echo $?' 'echo [!a]*[!b] ; echo $?' 'echo ?*? ; echo $?'

	launch_show "old errors"
	test_launch 'cd sandbox' 'echo file?' 'echo file\?'
	test_launch 'cd sandbox' 'echo file*' 'echo file\*'
	test_launch 'cd sandbox' 'echo file[1-2] ; echo file[!1-3]' 'echo file\[1-2]'
	test_launch 'cd sandbox' 'echo file\[1-2]'
	test_launch 'cd sandbox' 'echo file\[!1-2]'
	test_launch 'cd sandbox' 'echo file"[!2-3]"'
	test_launch 'cd sandbox' 'echo .*/"a"* '
	
	# test_launch 'rm -rf sandbox'
	
	launch_show "Correction"
	test_launch 'mkdir -p empty ; cd empty' 'touch a? b* [c]; ls -1'
	test_launch 'cd empty' 'echo a > aa && echo b > ab && cat -e a?'
	# test_launch 'cd empty' 'rm -f *' 'ls'
	test_launch 'cd empty' 'mkdir -p one/two'
	test_launch 'cd empty' 'echo "four" > one/two/three'
	test_launch 'cd empty' 'echo "four" > one/five'
	test_launch 'cd empty' 'cat ./*/*/* ./*/*'
	test_launch 'cd empty' 'ls /??r'
	# test_launch 'cd empty' 'rm -rf ./*' 'ls'
	test_launch 'cd empty' 'mkdir "[x" && touch "[x/foo"'
	test_launch 'cd empty' 'echo [*; echo *[x; echo [x/*'
	# test_launch 'cd empty' 'rm -rf *'
	test_launch 'cd empty' 'touch "a[a-z][x" "ab[x"'
	test_launch 'cd empty' 'echo a[a-z][*; echo a[a-z]*; echo a[a\-z]*'
	# test_launch 'cd empty' 'rm -f *'
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
	# test_launch 'cd empty' 'rm -f * .*; ls -A'
	test_launch 'cd empty' 'touch aa bb cc 11 22 33'
	test_launch 'cd empty' 'echo **'
	test_launch 'cd empty' 'echo [!a-z]'
	test_launch 'cd empty' 'echo [4-z][A-b]'
	# test_launch 'rm -rf empty'

finish
