# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_expansions_param.sh                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:50 by jmartel           #+#    #+#              #
#    Updated: 2019/11/09 08:33:41 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Redirections tests
launch "Parameter_expansion"
	launch_show "General"
	test_launch 'foo=okalm bar=tamer' 'echo ${foo}' 'echo ${bar}' 'echo ${foo}${bar}'

	launch_show ":- and -"
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

	launch_show ":= and ="
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

	launch_show ":? and ?"
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

	launch_show ":+ and +"
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

	launch_show "expansions in word"
	test_launch 'TOTO=hoho ; echo ${TOTO##"ho"} ; echo ${TOTO##\ho} ; echo ${TOTO##$TOTO}'
	test_launch 'TOTO=hoho ; echo ${TOTO%%"ho"} ; echo ${TOTO%%\ho} ; echo ${TOTO%%$TOTO}'
	test_launch 'param=Okalmos word=VARIABLE' 'echo ${param:-$word} ; echo ${param:-${word}}'
	test_launch 'param=Okalmos word=VARIABLE' 'echo ${noparam:-$word} ; echo ${noparam:-${word}}'
	test_launch 'param=Okalmos word=VARIABLE' 'echo ${param:+$word} ; echo ${param:+${word}}'
	test_launch 'param=Okalmos word=VARIABLE' 'echo ${noparam:+$word} ; echo ${noparam:+${word}}'
	test_launch 'param=Okalmos word=VARIABLE' 'echo ${param:?$word} ; echo ${param:?${word}}'
	test_launch 'param=Okalmos word=VARIABLE' 'echo ${noparam:?$word} ; echo ${noparam:?${word}}'
	test_launch 'param=Okalmos word=VARIABLE' 'echo ${param:=$word} ; echo ${param:=${word}}'
	test_launch 'param=Okalmos word=VARIABLE' 'echo ${noparam:=$word} ; echo ${noparam:=${word}}'
	test_launch 'echo ${param:-~} ; echo ${param:-~}'
	test_launch 'echo ${noparam:-~} ; echo ${noparam:-~}'
	test_launch 'echo ${param:-"~"} ; echo ${param:-"~"}'
	test_launch 'echo ${noparam:-"~"} ; echo ${noparam:-"~"}'
	test_launch 's=Oklma d=TAMER ; echo ${param:-$s$d} ; echo $?'
	test_launch 's=Oklma ; echo ${param:-$s$d} ; echo $?'
	test_launch 's=Oklma ; echo ${param:+$s$d} ; echo $?'

	launch_show "Quoting tests"
	test_launch 'echo ${""}'
	test_launch 'echo ${\}ls:=sd}'
	test_launch 'echo ${"wd"sd:+okalm}'
	test_launch 'wd=adq''echo ${"wd"sd:+okalm}'
	test_launch 'echo ${"wd"sd:+okalm}'

	launch_show "Random"
	test_launch 'echo ${=:}' 'echo ${?:}' 'echo ${-:}' 'echo ${+:}'
	test_launch 'echo ${::}' 'echo ${:==}'  'echo ${=:::+}'  'echo ${+::=}'  'echo ${=::-}' 
	test_launch 'echo ${}'
	test_launch 'echo ${()}'
	test_launch 'echo ${asdw+}'
	test_launch 'echo ${:asd}'
	test_launch 'echo ${:}'
	test_launch 'echo ${s:}'
	test_launch 'echo ${{{{}'
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


	launch_show "random"
		test_launch 'param=OkalmosSpeculos' 'echo ${param%\%Speculos}'
		test_launch 'param=OkalmosSpeculos' 'echo ${param%"%Speculos"}'
		test_launch 'param=OkalmosSpeculos' 'echo ${param%"#Speculos"}'
		test_launch 'param=OkalmosSpeculos' 'echo ${param#\#Okalmos}'

	launch_show "Field splitting Errors"
		test_launch 'param="Okalmos Speculos"' 'echo ${param#Speculos}'
		test_launch 'param="Okalmos Speculos"' 'echo ${param#Okalmos}'
		test_launch 'param="Okalmos Speculos"' 'echo ${param##Speculos}'
		test_launch 'param="Okalmos Speculos"' 'echo ${param##Okalmos}'
		test_launch 'param="Okalmos Speculos"' 'echo ${param%Speculos}'
		test_launch 'param="Okalmos Speculos"' 'echo ${param%Okalmos}'
		test_launch 'param="Okalmos Speculos"' 'echo ${param%%Speculos}'
		test_launch 'param="Okalmos Speculos"' 'echo ${param%%Okalmos}'


	# launch "Deprecated"
	# test_launch 'echo $}}}}'
	# test_launch 'echo ${#?}'
	# test_launch 'echo ${??}'
	# test_launch 'echo ${$}'
	# test_launch 'echo ${#$}'
	# test_launch 'echo ${$$}'
	# test_launch 'param="Okalmos Speculos"' 'echo ${##param}'
	# test_launch 'param="Okalmos Speculos"' 'echo ${##os}'
	# test_launch 'echo ${'
	# test_launch 'echo ${{{{'
	# test_launch 'echo \$}'
finish
