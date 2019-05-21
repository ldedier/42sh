# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_pipes.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:47 by jmartel           #+#    #+#              #
#    Updated: 2019/05/21 16:00:48 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Pipes tests
launch "Pipes simple"
	test "ls -la"
	test "ls -la | wc"
	test "ls -la | wc | wc"
	test "ls -la | wc | wc ; ls -la "
finish