# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_and_or.sh                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/06 14:33:59 by jmartel           #+#    #+#              #
#    Updated: 2019/09/06 14:39:05 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

true="./${obj_dir}/write_true"
false="./${obj_dir}/write_false"

launch "and_or"
	launch "&&"
		test_launch "$true && $false && $false"
		test_launch "$true && $false && $false"


finish