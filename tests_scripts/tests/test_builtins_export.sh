# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins_export.sh                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/22 15:32:16 by jmartel           #+#    #+#              #
#    Updated: 2019/11/10 04:47:50 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "export"
	launch_show "parser"
	test_launch "unset SHLVL _ OLDPWD" "export"
	test_launch "unset SHLVL _ OLDPWD" "export -E"
	test_launch "unset SHLVL _ OLDPWD" "export -p"
	test_launch "unset SHLVL _ OLDPWD" "export -- -p"
	test_launch "unset SHLVL _ OLDPWD" "export -p -- -p"
	test_launch "unset SHLVL _ OLDPWD" "export -E -p"
	test_launch "unset SHLVL _ OLDPWD" "export -- Okqlm SPecul"
	test_launch "unset SHLVL _ OLDPWD" "export -p -p -p -p"
	test_launch "unset SHLVL _ OLDPWD" "export -p -p -p -p --"

	launch_show "arguments"
	test_launch 'unset SHLVL _ OLDPWD' 'export var; echo $?' "export"
	test_launch 'unset SHLVL _ OLDPWD' 'export PWD OLDPWD; echo $?' "export"
	test_launch 'unset SHLVL _ OLDPWD' 'export var=okalm; echo $?' "export"
	test_launch 'unset SHLVL _ OLDPWD' 'export va; echo $?' "export"
	test_launch 'unset SHLVL _ OLDPWD' 'export PWD var="\"okalmose speculos\""; echo $?' "export"

	launch_show "write"
	test_launch "unset SHLVL _ OLDPWD" "export 1>&-"
	test_launch "unset SHLVL _ OLDPWD" "export -E 1>&-"
	test_launch "unset SHLVL _ OLDPWD" "export -E 2>&-"
	test_launch "unset SHLVL _ OLDPWD" "export 2>&-"

	launch_show "old_errors"
	test_launch "unset SHLVL _ OLDPWD" "var=tamer export var ; echo $var" "export"
	test_launch "unset SHLVL _ OLDPWD" "var=tamer export tamer ; echo $var" "export"
	test_launch "unset SHLVL _ OLDPWD" "var=tamer ; export var ; echo $var" "export"
	test_launch "unset SHLVL _ OLDPWD" "var=tamer ; export tamer ; echo $var" "export"
	test_launch "unset SHLVL _ OLDPWD" "var=tamer ls ; export var ; echo $var" "export"
	test_launch "unset SHLVL _ OLDPWD" "var=tamer ls ; export tamer ; echo $var" "export"

	test_launch "export variable ; variable="         "export | grep variable ; echo ; set | grep variable ; echo ; env | grep variale"
	test_launch "export variable ; variable= ls"      "export | grep variable ; echo ; set | grep variable ; echo ; env | grep variale"
	test_launch "export variable ; variable= nocmd"   "export | grep variable ; echo ; set | grep variable ; echo ; env | grep variale"
	test_launch "export variable ; variable=Tamer"    "export | grep variable ; echo ; set | grep variable ; echo ; env | grep variale"
	test_launch "export variable ; variable=Tamre ls" "export | grep variable ; echo ; set | grep variable ; echo ; env | grep variale"
	test_launch "export variable ; variable=Ta nocmd" "export | grep variable ; echo ; set | grep variable ; echo ; env | grep variale"
	
	test_launch "variable=var env   | grep variable=var" 'echo $?' "export | grep variable ; echo ; set | grep variable ; echo ; env | grep variale"
	test_launch "variable=var set   | grep variable=var" 'echo $?' "export | grep variable ; echo ; set | grep variable ; echo ; env | grep variale"
	test_launch "variable=var export| grep variable=var" 'echo $?' "export | grep variable ; echo ; set | grep variable ; echo ; env | grep variale"
	test_launch "variable=var nocmd                    " 'echo $?' "export | grep variable ; echo ; set | grep variable ; echo ; env | grep variale"

	test_launch ' ( (TOKEN201910142215_NAME=TOKEN201910142215_VALUE env | grep TOKEN ) ; env | grep TOKEN) ; env | grep TOKEN'

finish
