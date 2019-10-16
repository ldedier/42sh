# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_globbing.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 05:23:32 by jmartel           #+#    #+#              #
#    Updated: 2019/10/16 05:24:25 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Globbing"
	launch_show "Simple"
	test_launch 'echo *'
	test_launch 'echo ?*'
	test_launch 'echo *?'
	test_launch 'echo ?*?'

	launch_show ""
	launch_show ""


finish
