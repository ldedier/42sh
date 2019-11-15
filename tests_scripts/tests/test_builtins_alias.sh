# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins_alias.sh                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/22 15:32:16 by jmartel           #+#    #+#              #
#    Updated: 2019/11/15 04:39:24 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "alias"
	launch_show "parser"
	test_launch 'shopt -s expand_aliases' 'alias -A -E'
	test_launch 'shopt -s expand_aliases' 'alias -E -E'
	test_launch 'shopt -s expand_aliases' 'alias -- -E -E'
	test_launch 'shopt -s expand_aliases' 'alias -- var'
	test_launch 'shopt -s expand_aliases' 'alias -- var='
	test_launch 'shopt -s expand_aliases' 'alias -- var=ok'
	test_launch 'shopt -s expand_aliases' 'alias -- -E var=ok'
	test_launch 'shopt -s expand_aliases' 'alias -- var=ok -E'

	launch_show "arguments"
	test_launch 'shopt -s expand_aliases' 'type alias'
	test_launch 'shopt -s expand_aliases' 'alias ls=ls' 'ls'
	test_launch 'shopt -s expand_aliases' 'alias ok=ls' 'ok' 'alias ok="ls -a"' 'ok' 'unalias ok' 'ok'
	test_launch 'shopt -s expand_aliases' 'alias ok=ls' 'ok ' 'alias ok="ls -a"' 'ok ' 'unalias ok' 'ok '
	test_launch 'shopt -s expand_aliases' 'alias ok=""' 'alias' 'ok'
	test_launch 'shopt -s expand_aliases' 'alias ok=' 'alias' 'ok' 'alias ok && unalias ok && alias && alias ok'
	test_launch 'shopt -s expand_aliases' 'alias ok=ls' 'ok -a && ok nodir'

	launch_show "write"
	test_launch 'shopt -s expand_aliases' "alias 1>&-"
	test_launch 'shopt -s expand_aliases' 'alias ok=ls' "alias 1>&-"
	test_launch 'shopt -s expand_aliases' "alias ok=ls 1>&-"
	test_launch 'shopt -s expand_aliases' "alias ok=ls" "alias ok 1>&-"
	test_launch 'shopt -s expand_aliases' "alias ok=ls" "alias ok= 1>&-" "alias ok 1>&-"
	test_launch 'shopt -s expand_aliases' "alias -E 1>&-"
	test_launch 'shopt -s expand_aliases' "alias -E ls=ok 1>&-" "alias"
	test_launch 'shopt -s expand_aliases' "alias -E 2>&-"
	test_launch 'shopt -s expand_aliases' "alias no 2>&-"

	launch_show 'correction'
	test_launch 'shopt -s expand_aliases' 'alias hello="echo \"hello, world\""' 'hello | cat -e' 'alias hello ; alias hello= ; helllo'
	test_launch 'shopt -s expand_aliases' "alias sub='(echo abc|'" 'sub cat -e)'
	test_launch 'shopt -s expand_aliases' 'alias rd="ls DOESTNOEXIST 2>>err"' 'rd ; rd ; rd' 'cat err' 'rm -f err'
	test_launch 'shopt -s expand_aliases' "alias aa='echo hello' bb='echo world'" 'aa; bb'
	test_launch 'shopt -s expand_aliases' "alias mk='mkdir -v' abc='def'" 'mk abc' 'rm -rf abc' 'alias'
	test_launch 'shopt -s expand_aliases' 'alias a=alias' 'a aa="echo \"alias builtin redefined\""' 'aa'
	test_launch 'shopt -s expand_aliases' 'alias b=c' 'alias c=d' 'alias d="echo shall works"' 'b'
	test_launch 'shopt -s expand_aliases' 'alias e="g"' 'alias f="e"' 'alias g="echo infinite loop" ; e' 'g'
	test_launch 'shopt -s expand_aliases' 'alias hello="echo \" Hello, world !\""' 'unalias hello' 'hello'
	test_launch 'shopt -s expand_aliases' 'alias hello="echo okalm"' 'unalias -a' 'alias'

	launch_show "old_errors"

finish
