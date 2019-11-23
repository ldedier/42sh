# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins_test.sh                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/07 17:02:22 by jdugoudr          #+#    #+#              #
#    Updated: 2019/11/21 15:51:15 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "test"
	#initilisation
	blt_test_files="${obj_dir}/blt_test_file"
	mkdir -p ${blt_test_files} ${blt_test_files}/a ${blt_test_files}/dir_no_perm
	mkfifo ${blt_test_files}/a/b
	ln -s ${blt_test_files}/a/b ${blt_test_files}/c
	touch ${blt_test_files}/d ${blt_test_files}/g
	chmod 333 ${blt_test_files}/a
	chmod 444 ${blt_test_files}/d
	chmod u+s ${blt_test_files}/d
	chmod 020 ${blt_test_files}/g
	chmod 000 ${blt_test_files}/dir_no_perm
	chmod g+s ${blt_test_files}/dir_no_perm

	launch_show "unary test"
	test_launch	"test" 'echo $?'
	test_launch	"test ''" 'echo $?'
	test_launch	"test hey" 'echo $?'
	test_launch	"test ! hey" 'echo $?'
	test_launch	"test ! '(' hey ')'" 'echo $?'
	test_launch	"test '(' ! hey ')'" 'echo $?'
	test_launch	"test '('" 'echo $?'
	test_launch	"test !" 'echo $?'
	test_launch	"test ! -d blop" 'echo $?'
	test_launch	"test  -d /" 'echo $?'
	test_launch "test '(' -b ')' ${blt_test_files}/d" 'echo $?'
	test_launch "test '(' ! -c ')' ${blt_test_files}/d" 'echo $?'
	test_launch "test -d ${blt_test_files}/" 'echo $?'
	test_launch "test -d ${blt_test_files}/a/b" '$?'
	test_launch "test -d ${blt_test_files}/dir_no_perm" 'echo $?'
	test_launch "test -d ${blt_test_files}/dir_no_perm" 'echo $?'
	test_launch	"test ! -e blop" 'echo $?'
	test_launch	"test -e /tmp" 'echo $?'
	test_launch	"test -e ~" 'echo $?'
	test_launch	"test -f ~" 'echo $?'
	test_launch	"test -f ${blt_test_files}/a" 'echo $?'
	test_launch	"test -f ${blt_test_files}/d" 'echo $?'
	test_launch	"test -f ${blt_test_files}/a/b" 'echo $?'
	test_launch	"test '(' -f ${blt_test_files}/c ')'" 'echo $?'
	test_launch	"test '(' -g ${blt_test_files}/c ')'" 'echo $?'
	test_launch	"test '(' -f ${blt_test_files}/dir_no_perm ')'" 'echo $?'
	test_launch	"test '(' -f . ')'" 'echo $?'
	test_launch	"test '(' -f ${blt_test_files}/c ')'" 'echo $?'
	test_launch	"test '(' -f ${blt_test_files}/d ')'" 'echo $?'
	test_launch	"test '(' -g ${blt_test_files}/d ')'" 'echo $?'
	test_launch	"test '(' -g ${blt_test_files}/dir_no_perm ')'" 'echo $?'
	test_launch	"test '(' -L ${blt_test_files}/dir_no_perm ')'" 'echo $?'
	test_launch	"test '(' -L ${blt_test_files}/c ')'" 'echo $?'
	test_launch	"test '(' -L ${blt_test_files}/a/b ')'" 'echo $?'
	test_launch	"test '(' -p ${blt_test_files}/a/b ')'" 'echo $?'
	test_launch	"test '(' -p ${blt_test_files}/c ')'" 'echo $?'
	test_launch "test ! -r ${blt_test_files}/d" 'echo $?'
	test_launch "test ! -r ${blt_test_files}/dir_no_perm" 'echo $?'
	test_launch "test ! -s ${blt_test_files}/dir_no_perm" 'echo $?'
	test_launch "test ! -s ${blt_test_files}/d" 'echo $?'
	test_launch "test ! -u ${blt_test_files}/d" 'echo $?'
	test_launch "test ! -u ${blt_test_files}/dir_no_perm" 'echo $?'
	test_launch "test ! -w ${blt_test_files}/dir_no_perm" 'echo $?'
	test_launch "test ! -w ${blt_test_files}/g" 'echo $?'
	test_launch "test  -w ${blt_test_files}/a/b" 'echo $?'
	test_launch "test  -x ${blt_test_files}/a/b" 'echo $?'
	test_launch "test  -x ${blt_test_files}/dir_no_perm" 'echo $?'
	test_launch "test  -x ${blt_test_files}/a" 'echo $?'
	test_launch "test  -x ../21sh" 'echo $?'
	test_launch "test  -z 'test d une string'" 'echo $?'
	test_launch "test  -z ''" 'echo $?'
	
	launch_show "binary"
	test_launch "test  -z = ''" 'echo $?'
	test_launch 'test  $USER = ${USER}' 'echo $?'
	test_launch 'test  $USER = hohoho' 'echo $?'
	test_launch "test  -z != ''" 'echo $?'
	test_launch 'test  ! $USER != ${USER}' 'echo $?'
	test_launch 'test  $USER != hohoho' 'echo $?'
	test_launch "test  45812349 -eq 45821346758" 'echo $?'
	test_launch "test  0 -eq 0"  'cho $?'
	test_launch "test  ! -0 -eq 0" 'echo $?'
	test_launch "test  45812349 -ne 45821346758" 'echo $?'
	test_launch "test  0 -ne 0" 'echo $?'
	test_launch "test  ! -5 -ne 0" 'echo $?'
	test_launch "test  ! -5 -gt 0" 'echo $?'
	test_launch "test  ! 5 -gt 0" 'echo $?'
	test_launch "test  ! 5 -ge 5" 'echo $?'
	test_launch "test  ! +5 -ge 5" 'echo $?'
	test_launch "test  ! +83749537 -ge -38475295" 'echo $?'
	test_launch "test  ! -5 -lt 0" 'echo $?'
	test_launch "test  ! 5 -lt 0" 'echo $?'
	test_launch "test  ! 5 -le 5" 'echo $?'
	test_launch "test  ! +5 -le 5" 'echo $?'
	test_launch "test  ! -83749537 -le +38475295" 'echo $?'

	launch_show "errors"
	test_launch	"test '(' hey ! ')'" 'echo $?'
	test_launch	"test '(' hey ')' ho" 'echo $?'
	test_launch	"test '(' =  ho ')'" 'echo $?'
	test_launch	"test blop -p  ho" 'echo $?'
	test_launch	"test '(' blop -p  ho ')'" 'echo $?'
	test_launch "test  $USER -eq hohoho" 'echo $?'
	test_launch "test  $USER -le hohoho" 'echo $?'
	test_launch "test  8475348593 -le hohoho" 'echo $?'
	test_launch "test  8475348593 -ge 93750283574853945348573947584738450" 'echo $?'
	test_launch "test  8475348593 -ge ''" 'echo $?'
	test_launch "test  8475348593 -ge" 'echo $?'
	test_launch "test  8475348593 -ne 38473h43495" 'echo $?'
	test_launch "test  8475348593 -ne 38473h43495 8374238" 'echo $?'
	test_launch "test  8475348593 -ne 38473h43495.8374238" 'echo $?'

	launch_show "random"
	test_launch	"test -p /dev/fd/0" 'echo $?'
	test_launch	"test -S /dev/fd/0" 'echo $?'
	test_launch	"test -s /dev/fd/0" 'echo $?'
	test_launch	"test -g /dev/fd/0" 'echo $?'
	test_launch	"test -g /dev/urandom" 'echo $?'
	test_launch	"test -s /dev/urandom" 'echo $?'

	#rm files
	chmod -R 777 ${blt_test_files}
	rm -rf ${blt_test_files}
