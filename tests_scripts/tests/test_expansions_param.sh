# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_expansions_param.sh                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:50 by jmartel           #+#    #+#              #
#    Updated: 2019/08/06 13:12:07 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Redirections tests
launch "Parameter expansion"
	launch "General"
	test_launch 'foo=okalm bar=tamer' 'echo ${foo}' 'echo ${bar}' 'echo ${foo}${bar}'
	test_launch ''

	launch ":- and -"
	## :- and -
	test_launch 'var=wea' 'echo ${var:-okalm}'
	test_launch 'var=wea' 'echo ${var-okalm}'
	test_launch 'var=' 'echo ${var:-okalm}'
	test_launch 'var=' 'echo ${var-okalm}'
	test_launch 'echo ${var:-okalm}'
	test_launch 'echo ${var-okalm}'
	test_launch 'qweqweqwe=wea' 'echo ${qweqweqwe:-okalm}'
	test_launch 'qweqweqwe=wea' 'echo ${qweqweqwe-okalm}'
	test_launch 'qweqweqwe=' 'echo ${qweqweqwe:-okalm}'
	test_launch 'qweqweqwe=' 'echo ${qweqweqwe-okalm}'
	test_launch 'echo ${qweqweqwe:-okalm}'
	test_launch 'echo ${qweqweqwe-okalm}'

	# test_launch 'echo ${-}'
	test_launch 'echo ${:-}'
	test_launch 'echo ${sd-}'
	test_launch 'echo ${sd:-}'
	test_launch 'echo ${-asd}'
	test_launch 'echo ${:-asd}'

	launch ":= and ="
	## := and =
	test_launch 'var=wea' 'echo ${var:=okalm}'
	test_launch 'var=wea' 'echo ${var=okalm}'
	test_launch 'var=' 'echo ${var:=okalm}'
	test_launch 'var=' 'echo ${var=okalm}'
	test_launch 'echo ${var:=okalm}'
	test_launch 'echo ${var=okalm}'
	test_launch 'qweqweqwe=wea' 'echo ${qweqweqwe:=okalm}'
	test_launch 'qweqweqwe=wea' 'echo ${qweqweqwe=okalm}'
	test_launch 'qweqweqwe=' 'echo ${qweqweqwe:=okalm}'
	test_launch 'qweqweqwe=' 'echo ${qweqweqwe=okalm}'
	test_launch 'echo ${qweqweqwe:=okalm}'
	test_launch 'echo ${qweqweqwe=okalm}'

	test_launch 'echo ${=}'
	test_launch 'echo ${:=}'
	test_launch 'echo ${sd=}'
	test_launch 'echo ${sd:=}'
	test_launch 'echo ${=asd}'
	test_launch 'echo ${:=asd}'

	launch ":? and ?"
	## :? and ?
	test_launch 'var=wea' 'echo ${var:?okalm}' 'ls'
	test_launch 'var=wea' 'echo ${var?okalm}' 'ls'
	test_launch 'var=' 'echo ${var:?okalm}' 'ls'
	test_launch 'var=' 'echo ${var?okalm}' 'ls'
	test_launch 'echo ${var:?okalm}' 'ls'
	test_launch 'echo ${var?okalm}' 'ls'
	test_launch 'qweqweqwe=wea' 'echo ${qweqweqwe:?okalm}' 'ls'
	test_launch 'qweqweqwe=wea' 'echo ${qweqweqwe?okalm}' 'ls'
	test_launch 'qweqweqwe=' 'echo ${qweqweqwe:?okalm}' 'ls'
	test_launch 'qweqweqwe=' 'echo ${qweqweqwe?okalm}' 'ls'
	test_launch 'echo ${qweqweqwe:?okalm} ; ls'
	test_launch 'echo ${qweqweqwe?okalm} && ls'
	test_launch 'echo ${qweqweqwe?okalm} || ls'
	test_launch 'ls okalm' 'echo ${?}' 'echo $?'
	test_launch 'echo ${var?}'
	test_launch 'echo ${var:?}'
	test_launch 'echo ${var?:}'
	test_launch 'echo ${var?ok}'
	test_launch 'echo ${var:?ok}'
	test_launch 'echo ${var?:ok}'
	
	test_launch 'echo ${:?}' 'ls'
	test_launch 'echo ${sd?}' 'ls'
	test_launch 'echo ${sd:?}' 'ls'
	test_launch 'echo ${?asd}' 'ls '
	test_launch 'echo ${:?asd}' 'ls'

	launch ":+ and +"
	## :+ and +
	test_launch 'var=wea' 'okalm=tamer' 'echo ${var:+okalm}'
	test_launch 'var=wea' 'echo ${var:+okalm}'
	test_launch 'var=wea' 'okalm=tamer' 'echo ${var+okalm}'
	test_launch 'var=wea' 'echo ${var+okalm}'
	test_launch 'var='  'okalm=tamer' 'echo ${var:+okalm}'
	test_launch 'var='  'echo ${var:+okalm}'
	test_launch 'var=' 'okalm=tamer' 'echo ${var+okalm}'
	test_launch 'var=' 'echo ${var+okalm}'
	test_launch 'okalm=tamer' 'echo ${var:+okalm}'
	test_launch 'echo ${var+okalm}'
	test_launch 'qweqweqwe=wea' 'okalm=tamer' 'echo ${qweqweqwe:+okalm}'
	test_launch 'qweqweqwe=wea' 'echo ${qweqweqwe+okalm}'
	test_launch 'qweqweqwe=' 'okalm=tamer' 'echo ${qweqweqwe:+okalm}'
	test_launch 'qweqweqwe=' 'echo ${qweqweqwe+okalm}'
	test_launch 'echo ' 'okalm=tamer' '${qweqweqwe:+okalm}'
	test_launch 'echo ${qweqweqwe+okalm}'

	test_launch 'echo ${+}'
	test_launch 'echo ${:+}'
	test_launch 'echo ${sd+}'
	test_launch 'echo ${sd:+}'
	test_launch 'echo ${+asd}'
	test_launch 'echo ${:+asd}'

	launch "Quoting tests"
	test_launch 'echo ${""}'
	test_launch 'echo ${\}ls:=sd}'
	test_launch 'echo ${"wd"sd:+okalm}'
	test_launch 'wd=adq''echo ${"wd"sd:+okalm}'
	test_launch 'echo ${"wd"sd:+okalm}'

	launch "Random"
	## Invalid tests
	test_launch 'echo ${=:}' 'echo ${?:}' 'echo ${-:}' 'echo ${+:}'
	test_launch 'echo ${::}' 'echo ${:==}'  'echo ${=:::+}'  'echo ${+::=}'  'echo ${=::-}' 
	test_launch 'echo ${}'
	# test_launch 'echo ${'
	test_launch 'echo \$}'
	test_launch 'echo ${()}'
	test_launch 'echo ${asdw+}'
	test_launch 'echo ${:asd}'
	test_launch 'echo ${:}'
	test_launch 'echo ${s:}'
	test_launch 'echo ${{{{}'
	# test_launch 'echo ${{{{'
	test_launch 'echo ${?}'

	test_launch 'echo ${X:=abc}'
	test_launch 'echo ${posix:?}'
	test_launch 'echo ${#HOME}'
	test_launch 'echo ${x#$HOME}'
	test_launch 'dest=/backups' 'echo "$dest"'
	test_launch 'echo ${USER:=foo}'
	test_launch 'ls ~/${asd:-okalm}'
	test_launch 'ls ~/${}'
	test_launch 'ls ~/$'

	# launch "Deprecated"
	# test_launch 'echo $}}}}'
	# test_launch 'echo ${#?}'
	# test_launch 'echo ${??}'
	# test_launch 'echo ${$}'
	# test_launch 'echo ${#$}'
	# test_launch 'echo ${$$}'

finish
