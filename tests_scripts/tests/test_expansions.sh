# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_expansions.sh                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/23 13:10:40 by jmartel           #+#    #+#              #
#    Updated: 2019/11/26 07:38:12 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Expansions tests
launch "Expansions"
	launch_show "Random"
	test_launch 'echo $var'
	test_launch 'echo $TERM'
	test_launch 'var=Okalm' 'echo $var'
	test_launch 'var=Okalm' 'echo $var' 'var=po' 'echo $var'
	test_launch 'var=Okalm' 'echo ${pwd:=ol}'
	test_launch 'w=' 'echo $w'
	test_launch 'echo ${}'
	test_launch 'echo ${)'
	test_launch 'echo $novar ls'
	test_launch	'echo $pwd $pwd'
	test_launch 'shopt -s expand_aliases' 'alias al="$var"' 'var="ls -a ; al"' 'al ; echo $?' '$var ; echo $?'
	test_launch 'shopt -s expand_aliases' 'var="ls -a ; al"' 'alias al="$var"' 'al ; echo $?' '$var ; echo $?'
	test_launch 'ahsdiouashdiuasdhioasjdopasdjoldniouhjnqwioejqnwoel=adisuhiduashnodklajsodiajlsdlkasasdhuasodiu' 'echo $ahsdiouashdiuasdhioasjdopasdjoldniouhjnqwioejqnwoel='

	launch_show "Basic"
	test_launch '=qsda'
	test_launch 'var=okalm ; echo $var'
	test_launch 'var=qwe 	&& echo $var'
	test_launch 'var=qwe 	&& echo $vqr'
	test_launch 'var=asdqw || echo $var'
	test_launch 'var=asdqw || echo $vqr'
	test_launch 'var1=okalmos' 'var2=speculos' 'echo $var1 $var2'
	test_launch 'var1=okalmos' 'var2=speculos' 'echo $var1$var2'
	test_launch 'var1=okalmos var2=speculos var3=O' 'echo $var1$var2$var3'
	test_launch '=asd' '=' '12=we'
	test_launch '-=qwe' '--=qwe' '"pwe=qwe"'
	test_launch 'var=pwd' '$var'
	
	launch_show "#"
	test_launch 'var=Okalm' 'echo $#var $var'
	test_launch 'var=' 'echo $#var $var'
	test_launch 'echo $s#var $var'
	test_launch 'var=asd' 'echo $#v#ar $v#ar'
	test_launch 'var=asd' 'echo #$#v#ar $v#ar'
	test_launch 'var=asd' 'echo #$#v#ar $v#ar#'
	test_launch 'var=' 'echo $s#v#ar $v#ar'
	test_launch 'var=' 'echo #$#v#ar $v#ar'
	test_launch 'var=' 'echo #$#v#ar $v#ar#'
	test_launch 'echo $#v#ar $v#ar'
	test_launch 'echo #$g#v#ar $v#ar'
	test_launch 'echo #$d#v#ar $v#ar#'
	test_launch 'echo #~$~d#v#ar $v#ar#'
	test_launch 'echo #~$d~#~v#~ar $v~#ar#'

	launch_show "Special Variables"
	test_launch 'echo $?'
	test_launch 'echo $? ; ls ; echo $?'
	test_launch 'echo $? ; ls asdqwe ; echo $?'
	test_launch 'echo $? ; okalm ; echo $?'
	test_launch 'echo $? ; echo $?'
	test_launch 'touch file ; chmod 666 file' './file ; echo $?' 'rm file'
	test_launch 'echo $?' '?=123' 'echo $?'
	test_launch 'echo $#' '#=123' 'echo $#'
	test_launch 'echo $$ > buffer1' '$=1' 'echo $$>buffer2' 'diff buffer1 buffer2' 'rm buffer1 buffer2'

	launch_show 'assignments'
	test_launch 'PATH='\''$PATH'\'' ; echo $PATH'
	test_launch 'PATH='\''$var'\'' ; var='\''$PATH'\'' ; echo $PATH$var$PATH$var$PATH'
	test_launch 'var=$HOME ; echo $var'
	test_launch 'var='\'''\''$HOME ; echo $var'
	test_launch 'var='\''$HOME'\'' ; echo $var'
	test_launch 'var=\"$HOME\" ; echo $var'
	test_launch 'var='\sd\'' $HOME ; echo $var'
	test_launch 'var=$ASD ; echo $var'
	test_launch 'var=asd'\''$ASD'\'' ; echo $var'
	test_launch 'var="Okalm os speculos"$USER ; echo $var'
	test_launch 'var====== ; echo $var'
	test_launch 'var=\=\=\=\=\=\= ; echo $var'
	test_launch 'var\=\=\=\=\=\=\= ; echo $var'
	test_launch '\v\a\r=\=\=\=\=\=\= ; echo $var'
	test_launch '\v\a\r\=\=\=\=\=\=\= ; echo $var'
	test_launch '\v\a\r\=\\\\\=\=\=\=\=\= ; echo $var'
	test_launch 'false' 'var=okalm' 'echo $?'
	test_launch 'false' 'var=okalm false' 'echo $?'

	launch_show 'Failed tests'
	test_launch 'var=Okalmos v=tamer' 'echo "$var"$var$var$"var"'
	test_launch 'var=Okalmos v=tamer' "echo $'var'"
	test_launch 'var=Okalmos v=tamer' 'echo $v'"'ar'"
	test_launch 'var=Okalmos v=tamer' 'echo $"var"'
	test_launch 'var=Okalmos v=tamer' 'echo $"v"ar"'
	test_launch 'var=Okalmos v=tamer' 'echo $\var'
	test_launch 'var=Okalmos v=tamer' 'echo $\v\a\r'
	test_launch 'var=Okalmos v=tamer' 'echo $v\a\r'
	test_launch 'echo $'
	test_launch 'cd $'
	test_launch 'echo "$"'
	test_launch 'echo $'
	test_launch 'echo \$'
	test_launch 'echo "\$"'
	test_launch "echo '$'"
	test_launch 'echo ~/~/ '
	test_launch 'HOME="/path    /path" echo $HOME'
	test_launch 'HOME="/path    /path" ; echo $HOME'
	test_launch 'var=~:~/: ; echo $var'
	test_launch 'var=~/:~::: ; echo $var'
	test_launch 'var=~/:~//::: ; echo $var'
	test_launch 'var=:~/:~/::: ; echo $var'

	launch_show "Hybrid"
	# test_launch 'var=root' 'echo $(echo ~/) ; echo $(echo ~$var/)' 'echo ~$var/'
	test_launch 'shopt -s expand_aliases' 'alias cmd='"'"'cd ~/'"'" 'alias ; cmd ; echo $?' 'pwd'
	test_launch 'ls -a ; !ls' 'ls ; !ls ; ls -a' 'alias ls=echo' '!ls'

	launch_show "Expansions on all tokens types"
	test_launch 'var=file' 'echo tamer > $file'
	test_launch 'var=2' 'ls rien $var > file'
	test_launch 'var="      spa     ces"' '<$var cat'
	test_launch 'var="      spa     ces"' 'touch "$var"' '<"$var" cat' 'rm -f "$var"'
	test_launch 'var="      spa     ces"' 'echo > $var' 'cat "$var"' 'rm -f "$var"'
	test_launch 'var="      spa     ces"' 'echo > "$var"' 'cat "$var"' 'rm -f "$var"'
	test_launch 'var=">file"' 'echo oklam $var' 'cat file ; rm -f file'

	launch_show "invalid names"
	test_launch 'var=tamer okalm=speculos' 'echo $%%$var ; echo $+++$+++ ; echo \$\$$&---$okalm$++'
	test_launch 'var=tamer okalm=speculos' 'echo \$var$%%$var' 'echo "$var$%%$novar$%%"'
	test_launch 'var=tamer okalm=speculos' 'echo \$var$%%$var' 'echo "\$var\$%%\$novar\$%%"'
	test_launch 'var=tamer okalm=speculos' 'echo $%%$var'
	test_launch 'var=tamer okalm=speculos' 'echo $+++$+++'
	test_launch 'var=tamer okalm=speculos' 'echo $\$\$+++$okalm$++'
	test_launch 'var=tamer okalm=speculos' 'echo "\$var\$%%\$novar\$%%"'
	test_launch 'var=tamer okalm=speculos' 'echo \$var$%%$var'
	test_launch 'var=tamer okalm=speculos' 'echo "$var$%%$novar$%%"'
	test_launch 'var=tamer okalm=speculos' 'echo \$var$%%$var'
	test_launch 'echo %$%%%'
	test_launch 'echo $var$%%%\$var'
	test_launch 'echo "$%%%%"'
	test_launch 'var=tamer okalm=dsadasd' 'echo %%%var$\++%%$okalm'
	test_launch 'var=tamer okalm=dsa    d   a  sd' 'echo $okalm%%$%%$okalm%% '
	test_launch 'var=tamer okalm=dsadasd' 'echo %++$++$var++%'

# launch "Deprecated"
	# launch "Hard"
	# test_launch '321=asd' 'echo $321' '312=' 'echo $312'


finish

