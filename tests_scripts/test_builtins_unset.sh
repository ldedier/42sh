# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins_unset.sh                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/22 19:05:09 by jmartel           #+#    #+#              #
#    Updated: 2019/08/22 19:05:12 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "unset"
	launch "parser"
	test_launch "unset SHLVL _ OLDPWD" "unset"
	test_launch "unset SHLVL _ OLDPWD" "unset -E"
	test_launch "unset SHLVL _ OLDPWD" "unset -p"
	test_launch "unset SHLVL _ OLDPWD" "unset -- -p"
	test_launch "unset SHLVL _ OLDPWD" "unset -p -- -p"
	test_launch "unset SHLVL _ OLDPWD" "unset -E -p"
	test_launch "unset SHLVL _ OLDPWD" "unset -- Okqlm SPecul"
	test_launch "unset SHLVL _ OLDPWD" "unset -p -p -p -p"
	test_launch "unset SHLVL _ OLDPWD" "unset -p -p -p -p --"

	launch "arguments"
	test_launch "unset SHLVL _ OLDPWD" "unset var; echo $?" "export"
	test_launch "unset SHLVL _ OLDPWD" "unset PWD OLDPWD; echo $?" "export"
	test_launch "unset SHLVL _ OLDPWD" "unset var=okalm; echo $?" "export"
	test_launch "unset SHLVL _ OLDPWD" "unset va; echo $?" "export"
	test_launch "unset SHLVL _ OLDPWD" "unset PWD var=\"okalmose speculos\"; echo $?" "export"

	launch "write"
	test_launch "unset SHLVL _ OLDPWD" "unset 1>&-"
	test_launch "unset SHLVL _ OLDPWD" "unset -E 1>&-"
	test_launch "unset SHLVL _ OLDPWD" "unset -E 2>&-"
	test_launch "unset SHLVL _ OLDPWD" "unset 2>&-"