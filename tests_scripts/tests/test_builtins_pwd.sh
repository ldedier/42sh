# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins_pwd.sh                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/22 19:04:59 by jmartel           #+#    #+#              #
#    Updated: 2019/11/13 04:46:13 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "pwd"
	test_launch "pwd"
	test_launch "pwd | cat -e"
	test_launch "pwd | cat -e | wc"
	test_launch "PWD=" "OLDPWD=" "pwd"
	test_launch "pwd sqs"
	test_launch "pwd sqs aze"
	test_launch "mkdir dir ; cd dir ; rm -r ../dir ; pwd" "cd .. ; pwd"
	test_launch "cd sandbox/link/link" "pwd -P"
	test_launch "cd sandbox/link/link" "pwd -L"
	test_launch "cd sandbox/link/link" "pwd -L -P"
	test_launch "cd sandbox/link/link" "pwd -L -P -L"

	launch_show "write pwd"
	test_launch "pwd 1>&-"
	test_launch "pwd -E 1>&-"
	test_launch "pwd -E 2>&-"
	test_launch "pwd 2>&-"
