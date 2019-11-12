# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins_cd.sh                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/22 19:04:46 by jmartel           #+#    #+#              #
#    Updated: 2019/11/10 06:38:43 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "cd"
	launch_show "cdpath"
	test_launch 'unset CDPATH' 'pwd' 'cd tmp ; echo $? ; pwd' 'cd ; pwd' 'cd ; echo $? ; pwd ; cd - ; echo $? ; pwd'
	test_launch 'unset CDPATH' 'cd ~ ; pwd' ' cd - ; pwd' 'cd ; echo $? ; pwd ; cd - ; echo $? ; pwd'
	test_launch 'unset CDPATH' 'cd srcs ; echo $? ; pwd' 'cd objs ; echo $? ; pwd' 'cd logs ; echo $? ; pwd' 'cd ; echo $? ; pwd ; cd - ; echo $? ; pwd'
	test_launch 'CDPATH=""' 'cd tmp ; echo $? ; pwd' 'cd ~/ ; pwd' 'cd $HOME ; pwd' 'cd Desktop' 'cd ; echo $? ; pwd ; cd - ; echo $? ; pwd'
	test_launch 'CDPATH=""' 'cd srcs ; echo $? ; pwd' 'cd objs ; echo $? ; pwd' 'cd logs ; echo $? ; pwd' 'cd ; echo $? ; pwd ; cd - ; echo $? ; pwd'
	test_launch 'CDPATH=""' 'cd ~ ; pwd' ' cd - ; pwd' 'cd ; echo $? ; pwd ; cd - ; echo $? ; pwd'
	test_launch 'CDPATH="/"'    'cd srcs ; echo $? ; pwd' 'cd Desktop ; echo $? ; pwd' 'cd tmp ; echo $? ; pwd' 'cd ; echo $? ; pwd ; cd - ; echo $? ; pwd'
	test_launch 'CDPATH="$HOME' 'cd srcs ; echo $? ; pwd' 'cd Desktop ; echo $? ; pwd' 'cd tmp ; echo $? ; pwd' 'cd ; echo $? ; pwd ; cd - ; echo $? ; pwd'
	test_launch 'CDPATH=":$HOME:/' 'cd srcs ; echo $? ; pwd' 'cd Desktop ; echo $? ; pwd' 'cd tmp ; echo $? ; pwd' 'cd ; echo $? ; pwd ; cd - ; echo $? ; pwd'
	test_launch 'CDPATH=":::::$HOME:/' 'cd srcs ; echo $? ; pwd' 'cd Desktop ; echo $? ; pwd' 'cd tmp ; echo $? ; pwd' 'cd ; echo $? ; pwd ; cd - ; echo $? ; pwd'
	test_launch 'CDPATH="/:$HOME' 'cd srcs ; echo $? ; pwd' 'cd Desktop ; echo $? ; pwd' 'cd tmp ; echo $? ; pwd' 'cd ; echo $? ; pwd ; cd - ; echo $? ; pwd'
	test_launch 'CDPATH="/:$HOME:' 'cd srcs ; echo $? ; pwd' 'cd Desktop ; echo $? ; pwd' 'cd tmp ; echo $? ; pwd' 'cd ; echo $? ; pwd ; cd - ; echo $? ; pwd'
	test_launch 'CDPATH="/:$HOME:::::' 'cd srcs ; echo $? ; pwd' 'cd Desktop ; echo $? ; pwd' 'cd tmp ; echo $? ; pwd' 'cd ; echo $? ; pwd ; cd - ; echo $? ; pwd'

	test_launch "CDPATH=~/ cd Desktop ; pwd ; cd .. ; pwd"
	test_launch "CDPATH=/:~/ cd Desktop ; pwd ; cd .. ; pwd"
	test_launch "CDPATH=:~/ cd Desktop ; pwd ; cd .. ; pwd"
	test_launch "CDPATH=~/ ; cd Desktop ; pwd ; cd .. ; pwd"
	test_launch "CDPATH=/:~/ ; cd Desktop ; pwd ; cd .. ; pwd"
	test_launch "CDPATH=:~/ ; cd Desktop ; pwd ; cd .. ; pwd"
	test_launch "CDPATH=:/ ; cd Desktop ; pwd ; cd .. ; pwd"
	test_launch "CDPATH=:/: ; cd Desktop ; pwd ; cd .. ; pwd"
	test_launch "export CDPATH=~/ ; cd Desktop ; pwd ; cd .. ; pwd"
	test_launch "export CDPATH=/: ; cd Desktop ; pwd ; cd .. ; pwd"
	test_launch "export CDPATH=/:~/ ; cd Desktop ; pwd ; cd .. ; pwd"

	test_launch "CDPATH=/ cd tmp ; pwd ; cd .. ; pwd"
	test_launch "CDPATH=/:. cd tmp ; pwd ; cd .. ; pwd"
	test_launch "CDPATH=:/ cd tmp ; pwd ; cd .. ; pwd"
	test_launch "CDPATH=/ ; cd tmp ; pwd ; cd .. ; pwd"
	test_launch "CDPATH=/:/ ; cd tmp ; pwd ; cd .. ; pwd"
	test_launch "CDPATH=:/ ; cd tmp ; pwd ; cd .. ; pwd"
	test_launch "CDPATH=:/ ; cd tmp ; pwd ; cd .. ; pwd"
	test_launch "CDPATH=:/: ; cd tmp ; pwd ; cd .. ; pwd"
	test_launch "export CDPATH=/ ; cd tmp ; pwd ; cd .. ; pwd"
	test_launch "export CDPATH=/: ; cd tmp ; pwd ; cd .. ; pwd"
	test_launch "export CDPATH=/:. ; cd tmp ; pwd ; cd .. ; pwd"


	launch_show "simple"
	test_launch "cd" 'echo $?' "pwd"
	test_launch "cd ~/" 'echo $?' "pwd" "cd .. ; pwd"
	test_launch "cd /" 'echo $?' "cd ../.." 'echo $?' "pwd" 'echo $?'
	test_launch "cd ." "pwd" 'echo $?' "cd ../../" "pwd" 'echo $?'
	test_launch "cd ../../../../../../../../../../" 'echo $?'
	test_launch "cd -P /var" 'echo $?' "pwd" 'echo $?'
	test_launch "cd -L /var" 'echo $?' "pwd" 'echo $?'
	test_launch 'mkdir -p ./cdtest ; cd cdtest ; echo $? ; ln -s ../cdtest  ./link' "cd ./link" 'echo $?' "ls -a ; pwd ; cd ../.. ; rm -r cdtest"
	test_launch "mkdir dir ; ln -s dir link" 'echo $?' "cd dir ; pwd ; pwd -P" "cd ../link ; pwd ; pwd -P" "cd -P ../link ; pwd ; pwd -P" "cd .. ; rm -r dir link"
	test_launch "mkdir dir ; chmod 100 dir ; cd dir && pwd && cd .. ; chmod 777 dir ; rm -r dir" "rm -rf dir"
	test_launch "mkdir dir ; chmod 600 dir ; cd dir && pwd && cd .. ; chmod 777 dir ; rm -r dir" "rm -rf dir"
	test_launch "mkdir dir ; chmod 666 dir ; cd dir && pwd && cd .. ; chmod 777 dir ; rm -r dir" "rm -rf dir"
	test_launch "mkdir dir ; chmod 667 dir ; cd dir && pwd && cd .. ; chmod 777 dir ; rm -r dir" "rm -rf dir"

	launch_show "harder"
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
	test_launch "PWD=asd" "cd - ; pwd" "cd - ; pwd"
	test_launch "OLDPWD=asd" "cd - ; pwd" "cd - ; pwd"
	test_launch "OLDPWD=asd" "cd .. ; pwd" "cd - ; pwd" "cd - ; pwd"

	launch_show "parser"
	test_launch 'mkdir -p cdtest ; cd cdtest ; rm -f link ; ln -s cdtest link'
	test_launch 'cd -P cdtest/link/link' 'echo $? ; pwd'
	test_launch 'cd -P -P -P -L cdtest/link/link' 'echo $? ; pwd'
	test_launch 'cd -P -P -P -L -- cdtest/link/link' 'echo $? ; pwd'
	test_launch 'cd -P -P -P -L -- -P cdtest/link/link' 'echo $? ; pwd'
	test_launch 'cd -P -P -P -L -- -P' 'echo $? ; pwd'
	test_launch 'cd -P -P -P -L -- -E' 'echo $? ; pwd'
	test_launch 'cd -P -P -P -E -- cdtest/link' 'echo $? ; pwd'
	test_launch 'cd --ok cdtest/link' 'echo $? ; pwd'
	test_launch 'cd --ok cdtest/link/' 'echo $? ; pwd'
	test_launch 'rm -rf cdtest'

	launch_show "arguments"
	test_launch 'cd nodir' 'echo $? ; pwd'
	test_launch 'cd start.sh' 'echo $? ; pwd'
	test_launch 'cd ../start.sh' 'echo $? ; pwd'
	test_launch 'cd ./start.sh' 'echo $? ; pwd'
	test_launch 'cd ////' 'echo $? ; pwd'
	test_launch 'cd ..../.../..' 'echo $? ; pwd'
	test_launch 'cd /..../.../..' 'echo $? ; pwd'

	launch_show "returned value"
	test_launch "cd nodir" 'ech	o $?'
	test_launch "ln -s nowhere link"  "cd link" 'echo $?'
	test_launch "rm link" "cd .." 'echo $?'
	test_launch "cd" 'echo $?'

	launch_show "write"
	test_launch "cd 1>&-"
	test_launch "cd -E 1>&-"
	test_launch "cd -E 2>&-"
	test_launch "cd 2>&-"
	test_launch "cd nofile 1>&-"
	test_launch "cd nofile 2>&-"

	launch_show "Old errors"
	test_launch "cd ././../.." 'echo $?' "pwd"
	test_launch 'cd -P ././../..' 'echo $?' "pwd"
	test_launch 'cd ...' 'echo $?' "pwd"
	test_launch 'cd -P ...' 'echo $?' "pwd"
	test_launch 'cd /. ; echo $? ; pwd'
	test_launch 'cd /.. ; echo $? ; pwd'
	test_launch 'cd /./ ; echo $? ; pwd'
	test_launch 'cd /../ ; echo $? ; pwd'
	test_launch 'cd /././ ; echo $? ; pwd'
	test_launch 'cd /./../ ; echo $? ; pwd'
	test_launch 'cd /.././ ; echo $? ; pwd'

	launch_show "Old errors"
	test_launch "cd ././../.." 'echo $?' "pwd"
	test_launch 'cd -P ././../..' 'echo $?' "pwd"
	test_launch 'cd ...' 'echo $?' "pwd"
	test_launch 'cd -P ...' 'echo $?' "pwd"
	test_launch 'cd .//..' 'echo $?' "pwd"
	test_launch 'cd .//../' 'echo $?' "pwd"
	test_launch 'cd .././../' 'echo $?' "pwd"
	test_launch 'cd /./../' 'echo $?' "pwd"
	test_launch 'cd /./../tmp' 'echo $?' "pwd"
	test_launch 'cd okalm/..' 'echo $?' "pwd"
	test_launch 'cd ./okalm/..' 'echo $?' "pwd"
	test_launch 'cd ../okalm/..' 'echo $?' "pwd"
	test_launch 'cd /../okalm/..' 'echo $?' "pwd"
	test_launch 'cd ././.pwd/okalm/../..' 'echo $?' "pwd"

#	launch_show "Deprecated"
	# test_launch "PWD=" "OLDPWD=" "cd -" "cd -"
	# test_launch "PWD=/ OLDPWD=/var cd - ; cd -"
	# test_launch "PWD=/ OLDPWD=/var cd -" "cd -"
	# test_launch "ln -s . link" "cd link ; pwd" "cd link ; pwd" "pwd -P" " pwd -L" "rm link"
	# test_launch "ln -s . link" "cd link" "cd link" "pwd -L ; pwd -P" "rm link" # "cd .." "pwd ; cd ."
