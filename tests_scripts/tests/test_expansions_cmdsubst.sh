# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_expansions_cmdsubst.sh                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/10 06:04:23 by jmartel           #+#    #+#              #
#    Updated: 2019/11/26 07:38:43 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Command_Substitution_dollar"
	launch_show "Simple"
	test_launch '$()'
	test_launch '$(  )'
	test_launch '$(nocmd)'
	test_launch 'echo $(nocmd)'
	test_launch '$(ls)'
	test_launch '$(  ls     )'
	test_launch 'echo $(ls)'
	test_launch 'echo $(ls) | cat -e'
	test_launch 'echo $(ls -a) | cat -e'
	test_launch 'echo $(ls -a nodir) | cat -e'
	test_launch 'var=.. ; echo $(ls -a $var) | cat -e'
	test_launch 'var="ls -la" ; echo $($var ..) | cat -e'
	test_launch 'shopt -s expand_aliases' 'alias var="ls -a" ; echo $(var ..) | cat -e'
	test_launch 'shopt -s expand_aliases' 'alias var="ls -a | wc -l" ; echo $(var ..) | cat -e'
	test_launch 'shopt -s expand_aliases' 'alias var="ls -a | wc > file" ; echo $(var ..) | cat -e ; cat file ; rm -f file'
	test_launch 'echo $(echo $(ls) | cat -e ) | cat -e'
	test_launch 'shopt -s expand_aliases' 'var="ls    -a" cmd=echo ; alias cmd=echo' '$cmd $(cmd $($var) | cat -e ) | cat -e'
	test_launch '$(export HOME=/ ; cd ; pwd)' 'pwd ; cd ; pwd'
	test_launch 'unset HOME && echo $(cd;pwd)' 'export HOME=/ && echo $(cd;pwd)'

	launch_show "Changed IFS"
	test_launch 'export IFS="\ \"dsr"''"' 'var="ls -la" ; echo $($var ..) | cat -e'
	test_launch 'shopt -s expand_aliases' 'export IFS="\ \"dsr"''"' 'alias var="ls -a" ; echo $(var ..) | cat -e'
	test_launch 'shopt -s expand_aliases' 'export IFS="\ \"dsr"''"' 'alias var="ls -a | wc -l" ; echo $(var ..) | cat -e'
	test_launch 'shopt -s expand_aliases' 'export IFS="\ \"dsr"''"' 'alias var="ls -a | wc > file" ; echo $(var ..) | cat -e ; cat file ; rm -f file'
	test_launch 'export IFS="\ \"dsr"''"' 'echo $(echo $(ls) | cat -e ) | cat -e'
	test_launch 'shopt -s expand_aliases' 'export IFS="\ \"dsr"''"' 'var="ls    -a" cmd=echo ; alias cmd=echo' '$cmd $(cmd $($var) | cat -e ) | cat -e'

	launch_show "Hard"
	test_launch 'shopt -s expand_aliases' 'alias cmd="echo " opt="tamer     la      ..." ; echo $(cmd opt)'
	test_launch 'var1=Okalm var2=tamer var3=Speculos ; echo $(echo $var1$var2${#var3}Okslm$          tamer)'
	test_launch 'local=var echo $(echo $local var)' 'local=var ; echo $(echo $local var)'
	test_launch 'echo tamer > file' '<file $(cat) | cat -e ' 'echo $? ; rm file'
	test_launch 'var=$(ls -a | wc -l) ; echo $var'
	test_launch 'echo $(echo "taaaaam           e           r            O       kaaal mmmmm")'
	test_launch 'IFS=" a" ; echo $(echo "taaaaam           e           r            O       kaaal mmmmm")'
	test_launch 'var="taaaaam           e           r            O       kaaal mmmmm"' 'echo $(echo $var)'
	test_launch 'var="taaaaam           e           r            O       kaaal mmmmm"' 'IFS=" a" ; echo $(echo $var)'

launch "Command_Substitution_backquote"
	launch_show "Simple"
	test_launch '``'
	test_launch '`  `'
	test_launch '`nocmd`'
	test_launch 'echo `nocmd`'
	test_launch '`ls`'
	test_launch '`  ls     `'
	test_launch 'echo `ls`'
	test_launch 'echo `ls` | cat -e'
	test_launch 'echo `ls -a` | cat -e'
	test_launch 'var=.. ; echo `ls -a $var` | cat -e'
	test_launch 'var="ls -la" ; echo `$var ..` | cat -e'
	test_launch 'shopt -s expand_aliases' 'alias var="ls -a" ; echo `var ..` | cat -e'
	test_launch 'shopt -s expand_aliases' 'alias var="ls -a | wc -l" ; echo `var ..` | cat -e'
	test_launch 'shopt -s expand_aliases' 'alias var="ls -a | wc > file" ; echo `var ..` | cat -e ; cat file ; rm -f file'
	test_launch 'echo `echo `ls` | cat -e ` | cat -e'
	test_launch 'echo `ls nodfi`'
	test_launch '`ls $novar`'

launch "Process_Substitution"
	launch_show "Simple"
	test_launch 'cat -e < <(ls)'
	test_launch 'diff <(ls) <(ls -a)'
	test_launch 'sort <(cat -e <(grep fork <(ls -tr /usr/share/man/man2)) | (head -n 1 1> >(rev)))'
	test_launch 'ls | tee >(cat -e) >/dev/null'
	test_launch 'ls | wc >(cat -e) >/dev/null'
	test_launch 'sort -k 9 <(ls -l /bin) <(ls -l /usr/bin) <(ls -l ~/)'

## Deprecated
	# test_launch 'echo <(ls)        <(ls -l)'
	# test_launch 'echo <(ls) <(ls -l)'
	# test_launch 'echo <(ls)<(ls -l)'
