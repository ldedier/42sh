# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_exec.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:41 by jmartel           #+#    #+#              #
#    Updated: 2019/09/05 16:06:21 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "exec"
	launch_show "Basic"
	test_launch 'touch exec' './exec' 'rm exec'
	test_launch 'touch exec ; chmod 000 exec' './exec' 'chmod 777 exec ; rm exec'
	test_launch 'touch exec ; chmod +x exec' './exec' 'rm exec'
	test_launch 'mkdir dir'  './dir' 'rm -r dir'
	test_launch 'rm -rf dir'
	test_launch './nofile'
	test_launch 'touch file ; chmod -x file' './file' 'echo $?' 'rm -f file'
	test_launch '" ls "' 'echo $?' '"ls "' 'echo $?'

	launch_show "Permissions"
	test_launch 'echo "#!/bin/bash" >file' 'echo "echo lol" >> file' 'chmod 777 file' './file' 'chmod 777 file ; rm file'
	test_launch 'echo "#!/bin/bash" >file' 'echo "echo lol" >> file' 'chmod 600 file' './file' 'chmod 777 file ; rm file'
	test_launch 'echo "#!/bin/bash" >file' 'echo "echo lol" >> file' 'chmod 500 file' './file' 'chmod 777 file ; rm file'
	test_launch 'echo "#!/bin/bash" >file' 'echo "echo lol" >> file' 'chmod 400 file' './file' 'chmod 777 file ; rm file'
	test_launch 'echo "#!/bin/bash" >file' 'echo "echo lol" >> file' 'chmod 300 file' './file' 'chmod 777 file ; rm file'
	test_launch 'echo "#!/bin/bash" >file' 'echo "echo lol" >> file' 'chmod 200 file' './file' 'chmod 777 file ; rm file'
	test_launch 'echo "#!/bin/bash" >file' 'echo "echo lol" >> file' 'chmod 100 file' './file' 'chmod 777 file ; rm file'
	test_launch 'echo "#!/bin/bash" >file' 'echo "echo lol" >> file' 'chmod 000 file' './file' 'chmod 777 file ; rm file'

	launch_show "execve fail"
	if [ ! -f "${src_dir}/.execve_fail" ] ; then echo -e ${RED}"CANNOT FIND EXECVE_FAIL BINARY"${EOC}
	else
		test_launch "./${src_dir}/.execve_fail"
		test_launch "PATH=.:/usr/bin" "${src_dir}/.execve_fail"
		test_launch "env ./${src_dir}/.execve_fail"
		test_launch "PATH=.:/usr/bin' 'env ${src_dir}/.execve_fail"
		test_launch "./${src_dir}/.execve_fail | wc"
		test_launch "PATH=.:/usr/bin" "${src_dir}/.execve_fail | wc"
		test_launch "env ./${src_dir}/.execve_fail | wc"
		test_launch "PATH=.:/usr/bin" "env ${src_dir}/.execve_fail | wc"
	fi
finish
