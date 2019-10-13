# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins_unset.sh                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/22 19:05:09 by jmartel           #+#    #+#              #
#    Updated: 2019/10/10 15:55:03 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "unset"
	launch_show "parser"
	test_launch "unset SHLVL _ OLDPWD" "unset"
	test_launch "unset SHLVL _ OLDPWD" "unset -E"
	test_launch "unset SHLVL _ OLDPWD" "unset -p"
	test_launch "unset SHLVL _ OLDPWD" "unset -- -p"
	test_launch "unset SHLVL _ OLDPWD" "unset -p -- -p"
	test_launch "unset SHLVL _ OLDPWD" "unset -E -p"
	test_launch "unset SHLVL _ OLDPWD" "unset -- Okqlm SPecul"
	test_launch "unset SHLVL _ OLDPWD" "unset -p -p -p -p"
	test_launch "unset SHLVL _ OLDPWD" "unset -p -p -p -p --"

	launch_show "arguments"
	test_launch "unset SHLVL _ OLDPWD" 'unset var; echo $?' "export"
	test_launch "unset SHLVL _ OLDPWD" 'unset PWD OLDPWD; echo $?' "export"
	test_launch "unset SHLVL _ OLDPWD" 'unset PWD OLDPWD PWD OLDPWD; echo $?' "export"
	test_launch "unset SHLVL _ OLDPWD" 'unset $PWD $OLDPWD ; echo $?' "export"
	test_launch "unset SHLVL _ OLDPWD" 'unset var=okalm; echo $?' "export"
	test_launch "unset SHLVL _ OLDPWD" 'unset va; echo $?' "export"
	test_launch "unset SHLVL _ OLDPWD" 'unset PWD var=\"okalmose speculos\"; echo $?' "export"
	test_launch "unset SHLVL _ OLDPWD" 'unset ""; echo $?' "export"
	test_launch "unset SHLVL _ OLDPWD" 'unset "" ""; echo $?' "export"
	test_launch "unset NOVARIABLE"

	launch_show "write"
	test_launch "unset SHLVL _ OLDPWD" "unset 1>&-"
	test_launch "unset SHLVL _ OLDPWD" "unset -E 1>&-"
	test_launch "unset SHLVL _ OLDPWD" "unset -E 2>&-"
	test_launch "unset SHLVL _ OLDPWD" "unset 2>&-"

	launch_show "old errors"
	test_launch 'export ONE=tamer TWO=OKlm THREE=asdasd' 'unset ONE TWO THREE' 'export | grep "ONE\|TWO\|THREE"' 'env | grep "ONE\|TWO\|THREE"'
	test_launch 'export ONE=tamer ; export TWO=OKlm THREE=asdasd' 'unset ONE TWO THREE' 'export | grep "ONE\|TWO\|THREE"' 'env | grep "ONE\|TWO\|THREE"'
	test_launch 'export ONE=tamer ; export TWO=OKlm ; export THREE=asdasd' 'unset ONE TWO THREE' 'export | grep "ONE\|TWO\|THREE"' 'env | grep "ONE\|TWO\|THREE"'
	test_launch 'export ONE=tamer TWO=OKlm THREE=asdasd' 'unset ONE ; unset TWO ; unset THREE' 'export | grep "ONE\|TWO\|THREE"' 'env | grep "ONE\|TWO\|THREE"'
	test_launch 'export ONE=tamer TWO=OKlm ; export THREE=asdasd' 'unset ONE ; unset TWO THREE' 'export | grep "ONE\|TWO\|THREE"' 'env | grep "ONE\|TWO\|THREE"'
	test_launch 'export ONE=tamer TWO=OKlm ; export THREE=asdasd' 'unset ONE ; unset TWO ; unset THREE' 'export | grep "ONE\|TWO\|THREE"' 'env | grep "ONE\|TWO\|THREE"'
