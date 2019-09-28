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
	launch_show "write set"
	test_launch "set 1>&-"

	## Manual tests
test_launch "var=tamer" "set | grep var="
test_launch "var=tamer set | grep var="
test_launch "HOME=/ set | grep HOME="
test_launch "HOME=/ | set | grep HOME="
test_launch "HOME=/" "HOME=Okalm | set | grep HOME="
test_launch "var=Okalmos" "var=tamer set | grep HOME="
test_launch "var=Okalmos" "var=tamer | set | grep HOME="
