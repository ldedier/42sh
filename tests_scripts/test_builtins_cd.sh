# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins_cd.sh                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/22 19:04:46 by jmartel           #+#    #+#              #
#    Updated: 2019/08/30 15:03:55 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "cd"
	test_launch "cd" 'echo $?' "pwd"
	test_launch "cd ~/" 'echo $?' "pwd" "cd .. ; pwd"
	test_launch "cd /" 'echo $?' "cd ../.." 'echo $?' "pwd" 'echo $?'
	test_launch "cd ." "pwd" 'echo $?' "cd ../../" "pwd" 'echo $?'
	test_launch "cd ../../../../../../../../../../" 'echo $?'
	test_launch "cd -P /var" 'echo $?' "pwd" 'echo $?'
	test_launch "cd -L /var" 'echo $?' "pwd" 'echo $?'
	test_launch "mkdir sandbox ; cd sandbox ; echo \$? ; ln -s ../sandbox  ./link" "cd ./link" 'echo $?' "ls -a ; pwd ; cd .. ; rm -r sandbox"
	test_launch "mkdir dir ; ln -s dir link" 'echo $?' "cd dir ; pwd ; pwd -P" "cd ../link ; pwd ; pwd -P" "cd -P ../link ; pwd ; pwd -P" "cd .. ; rm -r dir link"

	test_launch "cd -" 'echo $?' "pwd"
	test_launch "cd '' '' && pwd"
	test_launch "cd '' '' || pwd"
	test_launch "cd '' && pwd"
	test_launch "cd '' || pwd"
	test_launch "cd sd tre" "cd gfd fcds ''" "pwd"
	test_launch "cd ../../ ; cd -"
	test_launch "PWD=asdqw OLDPWD=Okalm cd -" "cd -"
	test_launch "PWD=asdqw OLDPWD=Okalm" "cd -"
	test_launch "touch file" "cd file && wd && cd .." "rm file"
	test_launch "mkdir dir ; chmod 100 dir ; cd dir && pwd && cd .. ; chmod 777 dir ; rm -r dir" "rm -rf dir"
	test_launch "mkdir dir ; chmod 600 dir ; cd dir && pwd && cd .. ; chmod 777 dir ; rm -r dir" "rm -rf dir"
	test_launch "mkdir dir ; chmod 666 dir ; cd dir && pwd && cd .. ; chmod 777 dir ; rm -r dir" "rm -rf dir"
	test_launch "mkdir dir ; chmod 667 dir ; cd dir && pwd && cd .. ; chmod 777 dir ; rm -r dir" "rm -rf dir"

	test_launch "PWD=asd" "cd - ; pwd" "cd - ; pwd"
	test_launch "OLDPWD=asd" "cd - ; pwd" "cd - ; pwd"
	test_launch "OLDPWD=asd" "cd .. ; pwd" "cd - ; pwd" "cd - ; pwd"

## Create symlink to test -P option
# mkdir sandbox ; cd sandbox ; ln -s sandbox link


	launch "parser"
	test_launch 'cd -P sandbox/link/link' 'echo $? ; pwd'
	test_launch 'cd -P -P -P -L sandbox/link/link' 'echo $? ; pwd'
	test_launch 'cd -P -P -P -L -- sandbox/link/link' 'echo $? ; pwd'
	test_launch 'cd -P -P -P -L -- -P sandbox/link/link' 'echo $? ; pwd'
	test_launch 'cd -P -P -P -L -- -P' 'echo $? ; pwd'
	test_launch 'cd -P -P -P -L -- -E' 'echo $? ; pwd'
	test_launch 'cd -P -P -P -E -- sandbox/link' 'echo $? ; pwd'
	test_launch 'cd --ok sandbox/link' 'echo $? ; pwd'
	test_launch 'cd --ok sandbox/link/' 'echo $? ; pwd'

	launch "arguments"
	test_launch 'cd nodir' 'echo $? ; pwd'
	test_launch 'cd start.sh' 'echo $? ; pwd'
	test_launch 'cd ../start.sh' 'echo $? ; pwd'
	test_launch 'cd ./start.sh' 'echo $? ; pwd'
	test_launch 'cd ////' 'echo $? ; pwd'
	test_launch 'cd ..../.../..' 'echo $? ; pwd'
	test_launch 'cd /..../.../..' 'echo $? ; pwd'

	launch "returned value"
	test_launch "cd nodir" 'ech	o $?'
	test_launch "ln -s nowhere link"  "cd link" 'echo $?'
	test_launch "rm link" "cd .." 'echo $?'
	test_launch "cd" 'echo $?'

	launch "write"
	test_launch "cd 1>&-"
	test_launch "cd -E 1>&-"
	test_launch "cd -E 2>&-"
	test_launch "cd 2>&-"
	test_launch "cd nofile 1>&-"
	test_launch "cd nofile 2>&-"

	launch "Old errors"
	test_launch "cd ././../.." 'echo $?' "pwd"
	test_launch 'cd -P ././../..' 'echo $?' "pwd"
	test_launch 'cd ...' 'echo $?' "pwd"
	test_launch 'cd -P ...' 'echo $?' "pwd"

	launch "Old errors"
	test_launch "cd ././../.." 'echo $?' "pwd"
	test_launch 'cd -P ././../..' 'echo $?' "pwd"
	test_launch 'cd ...' 'echo $?' "pwd"
	test_launch 'cd -P ...' 'echo $?' "pwd"

#	launch "Deprecated"
	# test_launch "PWD=" "OLDPWD=" "cd -" "cd -"
	# test_launch "PWD=/ OLDPWD=/var cd - ; cd -"
	# test_launch "PWD=/ OLDPWD=/var cd -" "cd -"
	# test_launch "ln -s . link" "cd link ; pwd" "cd link ; pwd" "pwd -P" " pwd -L" "rm link"
	# test_launch "ln -s . link" "cd link" "cd link" "pwd -L ; pwd -P" "rm link" # "cd .." "pwd ; cd ."
