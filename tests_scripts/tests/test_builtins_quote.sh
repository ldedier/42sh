# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins_quote.sh                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/29 13:34:50 by jdugoudr          #+#    #+#              #
#    Updated: 2019/08/29 14:01:32 by jdugoudr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


launch "quote"
	test_launch 'echo simple test   without quote   !!'
	test_launch 'echo "simple test   with doublequote   !!"'
	test_launch "echo 'simple test   with doublequote   !!'"
	test_launch 'ec\ho \hey hey hey'
	test_launch "echo '\'hey \'hey hey"
	test_launch "l\s \-l \/"
	test_launch 'echo "\"\\\$$USER\$USER\\""'
	test_launch "echo '\"$USER\$USER'"
