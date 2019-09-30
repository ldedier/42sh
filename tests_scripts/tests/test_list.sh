# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_list.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/23 13:10:40 by jmartel           #+#    #+#              #
#    Updated: 2019/06/20 15:52:38 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Lists"

	launch_show ";"
	test_launch 'ls - ; pwd'
	test_launch 'asd ; asd a ; qweqweqw ; pwd ; ls /'
	test_launch 'echo okalm ; ls nofile ; pwd ; asdqw ; cat nofile'

	launch_show "&&"
	test_launch 'ls && pwd'
	test_launch 'ls nofile && pwd && echo okalm'
	test_launch 'echo okalm && ls nofile && echo okalm'
	test_launch 'echo okalm && ls && echo okalm'
	test_launch 'ecasd okalm && ls && echo okalm'

	launch_show "||"
	test_launch 'ls || pwd'
	test_launch 'ls nofile || echo okalm'
	test_launch 'ls nofile || echo okalm || echo okalm'
	test_launch 'ls -a || echo okalm || echo okalm'
	test_launch 'lsasdqw -a || echqweo okalm || echo olm'
	test_launch 'cat <nofile || echo $?'
	test_launch 'cat <nofile && echo $?'
	test_launch 'cat <&nofile || echo $?'
	test_launch 'cat <&nofile && echo $?'

	launch_show "pipes in lists"
	test_launch "echo ls -la | pwd ; echo 1>&- 11111 && echo 2222222 "
	test_launch "cat nofile | pwd ; echo 1>&- 11111 && echo 2222222 "
	test_launch "echo ls -la | okalmtamer ; echo 1>&- 11111 && echo 2222222 "
	test_launch "okalmasd | okaldasd ; echo 1>&- 11111 && echo 2222222 "
	test_launch "echo ls -la | pwd ; echo 1>&- 11111 && echo 2222222 "
	test_launch "echo ls -la | pwd ; echo 2>&- 1>&- 11111 && echo 2222222 "
	test_launch "echo ls -la | gfda ; echo 11111 && echo 2222222 "
	test_launch "directtamere | asda ; echo 11111 && echo 2222222 "
	test_launch "directtamere | ls -a ; echo 11111 && echo 2222222 "

finish
