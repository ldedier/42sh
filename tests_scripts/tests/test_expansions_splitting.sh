# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_expansions_splitting.sh                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/06 16:09:28 by jmartel           #+#    #+#              #
#    Updated: 2019/09/12 09:44:12 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Field splitting"
	launch "simple"
		test_launch 'var="Okalmose speculos"' 'echo $var'
		test_launch 'var="-l -A"' 'ls $var'
		test_launch 'var="ls -l"' '$var -A'
		test_launch 'var="ls -l -A"' '$var'
		test_launch 'IFS="-"' 'var="ls -l -A"' '$var'
		test_launch 'IFS="- "' 'var="ls -l -A"' '$var'
		test_launch 'var="Okalmos     Specul     os"' 'echo $var'
		test_launch 'IFS="A "' 'var="OkAlm   SpeculAs"' 'echo $var'
		test_launch "var='\"Okalmos   Speculos\"'" 'echo $var'
		test_launch 'IFS=AAAAAA''var=AAAAA' 'echo $var'
		test_launch 'IFS=A''var=AAAAA' 'echo $var'
		test_launch 'IFS=ABC''var=BAC' 'echo $var'
		test_launch 'IFS=ABC''var=B   A      C' 'echo $var'

	launch "hard"
		for i in `seq 1 5` ; do
			test_launch_pipe ./tests_files/splitting/splitting_${i}
		done


# TESTS with specialchars (quotes, ...) in IFS var

finish