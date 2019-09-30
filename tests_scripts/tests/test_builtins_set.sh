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
	test_launch 'unset _' "var=tamer" "set | grep var="
	test_launch 'unset _' "var=tamer set | grep var="
	test_launch 'unset _' "HOME=/ set | grep HOME="
	test_launch 'unset _' "HOME=/ | set | grep HOME="
	test_launch 'unset _' "HOME=/" "HOME=Okalm | set | grep HOME="
	test_launch 'unset _' "var=Okalmos" "var=tamer set | grep HOME="
	test_launch 'unset _' "var=Okalmos" "var=tamer | set | grep HOME="

	test_launch 'unset _' 'export okalm' 'export okalm' 'unset _ ; set | grep okalm' 'unset _ ; export | grep okalm'
	test_launch 'unset _' 'var=Tamer' 'unset _ ; set | grep var=Tamer' 'unset _ ; export | grep var=Tamer'
	test_launch 'unset _' 'variable=' 'unset _ ; set | grep variable=' 'unset _ ; export | grep variable='
	test_launch 'unset _' 'set | grep USER' 'unset _ ; export | grep USER'
	test_launch 'unset _' 'unset USER' 'unset _ ; set | grep USER' 'unset _ ; export | grep USER'
	test_launch 'unset _' 'variable=' 'unset _ ; set | grep variable= ; unset _ ; export | grep variable=' 'unset variable' 'unset _ ; set | grep variable= ; unset _ ; export | grep variable='
	test_launch 'unset _' 'export variable=' 'unset _ ; set | grep variable= ; unset _ ; export | grep variable=' 'unset variable' 'unset _ ; set | grep variable= ; export | grep variable='
	test_launch 'unset _' 'Okalm=os' 'set | grep Okalm=os ; export | grep Okalm=os' 'export Okalm' 'set | grep Okalm=os ; export | grep Okalm=os' 'unset Okalm' 'set | grep Okalm=os ; export | grep Okalm=os'

	test_launch 'variable=tamer' 'export variable' 'unset_ ; set | grep variable ; unset _ ; export | grep variable'
	test_launch 'variable=tamer' 'export variable=' 'unset_ ; set | grep variable ; unset _ ; export | grep variable'
	test_launch 'variable=tamer' 'export variable=OKALM' 'unset_ ; set | grep variable ; unset _ ; export | grep variable'
	test_launch 'variable=tamer' 'export var=OKALM' 'unset_ ; set | grep variable ; unset _ ; export | grep variable'
