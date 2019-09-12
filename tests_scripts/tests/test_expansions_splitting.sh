# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_expansions_splitting.sh                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/06 16:09:28 by jmartel           #+#    #+#              #
#    Updated: 2019/09/04 11:54:12 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Field splitting"
	launch "simple"
		test_launch 'var="Okalmose speculos"' 'echo $var'
		test_launch 'var="-l -A"' 'ls $var'
		test_launch 'var="ls -l"' '$var -A'
		test_launch 'var="ls -l -A"' '$var'

finish