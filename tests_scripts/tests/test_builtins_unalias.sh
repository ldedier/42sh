# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins_unalias.sh                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/22 19:05:09 by jmartel           #+#    #+#              #
#    Updated: 2019/10/09 02:20:58 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "unalias"
	launch_show "parser"
	test_launch 'shopt -s expand_aliases' "unalias"
	test_launch 'shopt -s expand_aliases' "unalias -E"
	test_launch 'shopt -s expand_aliases' "unalias -a -a -E"
	test_launch 'shopt -s expand_aliases' "unalias -a -a"
	test_launch 'shopt -s expand_aliases' "unalias -- ok"
	test_launch 'shopt -s expand_aliases' "unalias -- nothing"
	test_launch 'shopt -s expand_aliases' "unalias -- nothing -a"
	test_launch 'shopt -s expand_aliases' "unalias -a nothing -a"

	launch_show "arguments"
	test_launch 'shopt -s expand_aliases' 'type unalias'
	test_launch 'shopt -s expand_aliases' "alias a1=ls a2=second a3=pwd" "unalias a1 nothing a2" 'echo $? ; alias'
	test_launch 'shopt -s expand_aliases' "alias a1=ls a2=second a3=pwd" "unalias a1 a2 a1" 'echo $? ; alias'
	test_launch 'shopt -s expand_aliases' "alias a1=ls a2=second a3=pwd" "unalias a1 nothing a3" 'echo $? ; alias'
	test_launch 'shopt -s expand_aliases' "alias a1=ls a2=second a3=pwd" "unalias a1 a2 a3" 'echo $? ; alias'
	test_launch 'shopt -s expand_aliases' "alias a1=ls a2=second a3=pwd" "unalias a1 -a" 'echo $? ; alias'
	test_launch 'shopt -s expand_aliases' "alias a1=ls a2=second a3=pwd" "unalias -a a1 a2" 'echo $? ; alias'
	test_launch 'shopt -s expand_aliases' "alias a1=ls a2=second a3=pwd" "unalias -a a1 a2 a3" 'echo $? ; alias'
	test_launch 'shopt -s expand_aliases' "alias a1=ls a2=second a3=pwd" "unalias -a a3" 'echo $? ; alias'
	test_launch 'shopt -s expand_aliases' 'unalias -a' 'unalias -a' 'unalias -a'
	test_launch 'shopt -s expand_aliases' 'alias ok="ls -a"' 'unalias -a' 'unalias -a'

	launch_show "write"
	test_launch 'shopt -s expand_aliases' "unalias 1>&-"
	test_launch 'shopt -s expand_aliases' "unalias 1>&- -a"
	test_launch 'shopt -s expand_aliases' "unalias 1>&- -E"
	test_launch 'shopt -s expand_aliases' "unalias 1>&- nothing"
	test_launch 'shopt -s expand_aliases' "unalias tamer 1>&-"
	test_launch 'shopt -s expand_aliases' "unalias -E 1>&-"
	test_launch 'shopt -s expand_aliases' "unalias -E 2>&-"
	test_launch 'shopt -s expand_aliases' "unalias nothing 2>&-"
	test_launch 'shopt -s expand_aliases' "unalias 2>&-"
