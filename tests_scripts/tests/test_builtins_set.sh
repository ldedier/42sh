#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins_set.sh                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/22 19:05:04 by jmartel           #+#    #+#              #
#    Updated: 2019/08/22 19:05:13 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "set"
	launch_show "write set"
	test_launch "set 1>&-"

	## Manual tests
	test_launch "var=tamer" "set | grep var="
	test_launch "var=tamer set | grep var="
	test_launch "HOME=/ set | grep HOME="
	test_launch "HOME=/ | set | grep HOME="
	test_launch "HOME=/" "HOME=Okalm | set | grep HOME="
	test_launch "var=Okalmos" "var=tamer set | grep HOME="
	test_launch "var=Okalmos" "var=tamer | set | grep HOME="

	test_launch 'export okalm' 'export okalm' 'set | grep okalm' 'export | grep okalm'
	test_launch 'var=Tamer' 'set | grep var=Tamer' 'export grep var=Tamer'
	test_launch 'variable=' 'set | grep variable=' 'export grep variable='
	test_launch 'set | grep HOME' 'eport | grep HOME'
	test_launch 'unset HOME' 'set | grep HOME' 'eport | grep HOME'
	test_launch 'variable=' 'set | grep variable= ; export grep variable=' 'unset variable' 'set | grep variable= ; export grep variable='
	test_launch 'export variable=' 'set | grep variable= ; export grep variable=' 'unset variable' 'set | grep variable= ; export grep variable='
