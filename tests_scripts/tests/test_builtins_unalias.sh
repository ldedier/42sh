# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins_unalias.sh                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/22 19:05:09 by jmartel           #+#    #+#              #
#    Updated: 2019/08/22 19:05:12 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "unalias"
	launch_show "parser"
	test_launch "unalias"
	test_launch "unalias -E"
	test_launch "unalias -a -a -E"
	test_launch "unalias -a -a"
	test_launch "unalias -- ok"
	test_launch "unalias -- nothing"
	test_launch "unalias -- nothing -a"
	test_launch "unalias -a nothing -a"

	launch_show "arguments"
	test_launch "alias a1=ls a2=second a3=pwd" "unalias a1 nothing a2" 'echo $? ; alias'
	test_launch "alias a1=ls a2=second a3=pwd" "unalias a1 a2 a1" 'echo $? ; alias'
	test_launch "alias a1=ls a2=second a3=pwd" "unalias a1 nothing a3" 'echo $? ; alias'
	test_launch "alias a1=ls a2=second a3=pwd" "unalias a1 a2 a3" 'echo $? ; alias'
	test_launch "alias a1=ls a2=second a3=pwd" "unalias a1 -a" 'echo $? ; alias'
	test_launch "alias a1=ls a2=second a3=pwd" "unalias -a a1 a2" 'echo $? ; alias'
	test_launch "alias a1=ls a2=second a3=pwd" "unalias -a a1 a2 a3" 'echo $? ; alias'
	test_launch "alias a1=ls a2=second a3=pwd" "unalias -a a3" 'echo $? ; alias'

	launch_show "write"
	test_launch "unalias 1>&-"
	test_launch "unalias 1>&- -a"
	test_launch "unalias 1>&- -E"
	test_launch "unalias 1>&- nothing"
	test_launch "unalias tamer 1>&-"
	test_launch "unalias -E 1>&-"
	test_launch "unalias -E 2>&-"
	test_launch "unalias nothing 2>&-"
	test_launch "unalias 2>&-"
