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
	launch_show "parser"
	launch_show "arguments"
	launch_show "returned value"

	launch_show "write set"
	test_launch "set 1>&-"
# 	test_launch " -E 1>&-"
# 	test_launch " -E 2>&-"
# 	test_launch " 2>&-"

