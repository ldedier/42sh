# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_random.sh                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:41 by jmartel           #+#    #+#              #
#    Updated: 2019/09/05 16:33:21 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Shell"
	launch_show "Random"
	test_launch 'mkdir test123 ; cd test123 ; ls -a ; ls | cat | wc -c > fifi ; cat fifi ; cd .. ; rm -r test123'
	test_launch '.' './'
	test_launch '..' '../'
	test_launch '././..' '../../.'
	test_launch 'echo tamer > file' 'echo okalm >> file' '<file cat' '<file cat >file' 'cat file' 'rm file'
	test_launch 'env -i TERM=$TERM PATH=/bin '"${exec}" 'cd includes ; pwd ; cd - ; pwd'

	launch_show "segfault"
	test_launch "./${obj_dir}/segfault"       'echo $?'
	test_launch "./${obj_dir}/segfault | wc;" 'echo $?'
	test_launch "ls | ./${obj_dir}/segfault"  'echo $?'
	test_launch "./${obj_dir}/segfault && echo "'$? ; echo $?'
	test_launch "./${obj_dir}/segfault || echo "'$? ; echo $?'
	test_launch "./${obj_dir}/segfault ; echo  "'$? ;  echo $?'
	test_launch "./${obj_dir}/segfault | wc && echo "'$? ; echo $?'
	test_launch "ls | ./${obj_dir}/segfault && echo "'$? ; echo $?'
finish
