# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins_hash.sh                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/22 19:04:55 by jmartel           #+#    #+#              #
#    Updated: 2019/08/22 19:05:14 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "hash"
	test_launch "hash -h" "hash -s"
	test_launch "hash" "hash -r"
	test_launch "hash qkjhbdnsj"
	test_launch "hash -e"
	test_launch "hash '' "
	test_launch "hash '' '' -r ls "
	test_launch "hash -r" "hash"
	test_launch "cat file " "hash -r" "hash"
	# test_launch "hash ls brew" "hash -r -e -r" "hash"
	# test_launch "hash ls" "hash -e -r -e" "hash"
	# test_launch "hash /bin/ls" "hash date" "hash"
	# test_launch "hash ls ls ls ls date" "hash" "hash -r" "hash"
	test_launch "hash ls ls ls ls date" "hash -r" "hash"
	test_launch "hash -r ls -r"
	test_launch "hash -r -r ls -r -r ls"
	# test_launch "hash nothing ls" "hash"
	test_launch "hash -e"

	launch_show 'modifying PATH'
	test_launch 'hash ls' 'unset PATH' 'hash'
	test_launch 'hash ls' 'PATH=/bin' 'hash'
	test_launch 'hash ls' 'export PATH=/' 'hash'
	# test_launch 'hash ls' 'export PATH' 'hash'
	test_launch 'hash ls' 'export PATH=' 'hash'
	test_launch 'hash ls' 'PATH=' 'hash'
	test_launch 'hash ls' 'PATH="$PATH"' 'hash'

	launch_show "write hash"
	test_launch "hash 1>&-"
	test_launch "hash -E 1>&-"
	test_launch "hash -E 2>&-"
	test_launch "hash 2>&-"
