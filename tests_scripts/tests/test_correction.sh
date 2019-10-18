# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_correction.sh                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/28 01:13:40 by jmartel           #+#    #+#              #
#    Updated: 2019/10/10 14:04:51 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "correction"
	launch_show "gestion de l'environnement"

	test_launch 'a=hello b=world; b=42 echo ${a}_${b} && echo ${b}'
	test_launch 'directory=/ ls_opt=-atr' 'ls ${ls_opt} ${directory}'
	test_launch	'echo ${empty}|cat -e'
	test_launch "set | grep -E '(a|b)='"
	test_launch "env | grep -E '(a|b)='"
	test_launch 'export b' 'printenv b'
	test_launch 'ONESHOT= env | grep ONESHOT' 'env | grep ONESHOT'
	test_launch 'unset a b' "env | grep -E '(a|b)='" "set | grep -E '(a|b)='"
	test_launch 'unset PATH' 'PATH=/bin:/usr/bin' 'mkdir testdir' 'echo ${?}' 'ls -1 | grep testdir' 'rm -rf testdir'
	test_launch 'true; echo ${?}; false; echo ${?}'

	launch_show 'https://github.com/we-sh/42ShellTester'
	test_launch 'echo TOKEN201910101357_1 TOKEN201910101357_2 &>           new_file_stderr_and_stdout' 'rm new_file_stderr_and_stdout'
	test_launch 'echo TOKEN201910101357_1 TOKEN201910101357_2 &>new_file_stderr_and_stdout' 'rm new_file_stderr_and_stdout'