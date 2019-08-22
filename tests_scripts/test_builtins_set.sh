# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins_set.sh                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/22 19:05:04 by jmartel           #+#    #+#              #
#    Updated: 2019/08/22 19:05:13 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "set"

	launch "parser"
	launch "arguments"
	launch "returned value"

	launch "write set"
	test_launch "set 1>&-"
# 	test_launch " -E 1>&-"
# 	test_launch " -E 2>&-"
# 	test_launch " 2>&-"

