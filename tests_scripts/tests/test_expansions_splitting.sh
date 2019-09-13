# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_expansions_splitting.sh                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/06 16:09:28 by jmartel           #+#    #+#              #
#    Updated: 2019/09/12 23:48:11 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Field splitting"
	launch "simple"
		test_launch 'var="Okalmose speculos"' 'echo $var'
		test_launch 'var="-n pwd"' 'echo $var'
		test_launch 'var="echo -n"' '$var Okalmos'
		test_launch 'var="ls -NOOPT"' '$var .'
		test_launch 'var="echo -n okalmos speculos"' '$var'
		test_launch 'IFS="-"' 'var="ls -l -A"' '$var'
		test_launch 'IFS="- "' 'var="ls -l -A"' '$var'
		test_launch 'var="Okalmos     Specul     os"' 'echo $var'
		test_launch 'IFS="A "' 'var="OkAlm   SpeculAs"' 'echo $var'
		test_launch "var='\"Okalmos   Speculos\"'" 'echo $var'
		test_launch 'IFS=AAAAAA''var=AAAAA' 'echo $var'
		test_launch 'IFS=A''var=AAAAA' 'echo $var'
		test_launch 'IFS=ABC''var=BAC' 'echo $var'
		test_launch 'var="OkAAAlmos speculAs" IFS=A\ ' 'echo $var'
		test_launch 'IFS=ABC''var=B   A      C' 'echo $var'
		test_launch 'var="echo tamer | cat -e"' '$var'

	launch "IFS unset"
		test_launch 'unset IFS' 'var="Okalmos   speculos 		L "' 'echo $var'
		test_launch 'unset IFS' 'var="Okalmos   speculos 		L "' 'echo "$var"'
		test_launch 'unset IFS' 'var="		    	ASD			   	 	sda qwe"' 'echo $var'
		test_launch 'unset IFS' 'var="		    	ASD			   	 	sda qwe"' 'echo "$var"'
		test_launch 'unset IFS' 'v="   asdqwe    " a="qqwe     qwe     asd"' 'echo $v$a${v}    $a$v'
		test_launch 'unset IFS' 'v="   asdqwe    " a="qqwe     qwe     asd"' 'echo "$v"$a"${v}""    $a$v'
		test_launch 'unset IFS' 'v="   asdqwe    " a="qqwe     qwe     asd"' 'echo $v"$a"${v}    "$a$v"'
		test_launch 'unset IFS' 'v="   asdqwe    " a="qqwe     qwe     asd"' 'echo "$v$a${v}    $a$v"'
		test_launch 'unset IFS' 'v="   asdqwe    " a="qqwe     qwe     asd"' 'echo "$v$a${v}"    $a$v'
		test_launch 'unset IFS' 'c="Okalms asd  " v="A    SDQWE"' 'echo $c$v$v$c   $c$c$v$v'
		test_launch 'unset IFS' 'ok="   Je   suis   Okalm   " var="echo -n $ok"' '$var'
		test_launch 'unset IFS' 'ok="   Je   suis   Okalm   " var="echo -n $ok"' '"$var"'
		test_launch 'unset IFS' '' 'echo $var'
		test_launch 'unset IFS' '' 'echo $var'
		test_launch 'unset IFS' '' 'echo $var'
		test_launch 'unset IFS' '' 'echo $var'
		test_launch 'unset IFS' '' 'echo $var'

	launch "hard"
		for i in `seq 1 5` ; do
			test_launch_pipe ./tests_files/splitting/splitting_${i}
		done


# TESTS with specialchars (quotes, ...) in IFS var

finish