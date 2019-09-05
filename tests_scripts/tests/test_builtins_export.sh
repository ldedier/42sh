# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins_export.sh                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/22 15:32:16 by jmartel           #+#    #+#              #
#    Updated: 2019/08/22 17:43:00 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "export"
	launch "parser"
	test_launch "unset SHLVL _ OLDPWD" "export"
	test_launch "unset SHLVL _ OLDPWD" "export -E"
	test_launch "unset SHLVL _ OLDPWD" "export -p"
	test_launch "unset SHLVL _ OLDPWD" "export -- -p"
	test_launch "unset SHLVL _ OLDPWD" "export -p -- -p"
	test_launch "unset SHLVL _ OLDPWD" "export -E -p"
	test_launch "unset SHLVL _ OLDPWD" "export -- Okqlm SPecul"
	test_launch "unset SHLVL _ OLDPWD" "export -p -p -p -p"
	test_launch "unset SHLVL _ OLDPWD" "export -p -p -p -p --"

	launch "arguments"
	test_launch 'unset SHLVL _ OLDPWD" "export var; echo $?' "export"
	test_launch 'unset SHLVL _ OLDPWD" "export PWD OLDPWD; echo $?' "export"
	test_launch 'unset SHLVL _ OLDPWD" "export var=okalm; echo $?' "export"
	test_launch 'unset SHLVL _ OLDPWD" "export va; echo $?' "export"
	test_launch 'unset SHLVL _ OLDPWD' 'export PWD var=\"okalmose speculos\"; echo $?' "export"

	launch "write"
	test_launch "unset SHLVL _ OLDPWD" "export 1>&-"
	test_launch "unset SHLVL _ OLDPWD" "export -E 1>&-"
	test_launch "unset SHLVL _ OLDPWD" "export -E 2>&-"
	test_launch "unset SHLVL _ OLDPWD" "export 2>&-"

	launch "returned value"

