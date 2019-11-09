# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_expansions_substring_removal.sh               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:50 by jmartel           #+#    #+#              #
#    Updated: 2019/11/09 08:34:41 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "substring_removal"
	launch_show "# and ## no pattern matching"
	test_launch 'param="Okalmos Speculos"' 'echo ${param#}'
	test_launch 'param="Okalmos Speculos"' 'echo ${#}'
	test_launch 'param="Okalmos Speculos"' 'echo ${#os}'
	test_launch 'param="Okalmos Speculos"' 'echo ${#param}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param#param}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param#s}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param# Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param#Okalmos Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param#kalmos Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param#kamos Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param#Oka}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param#Okalmos Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param#OkalmosSpeculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${var#Okalmos Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param##}'
	test_launch 'param="Okalmos Speculos"' 'echo ${##}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param##param}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param##s}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param## Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param##Okalmos Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param##kalmos Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param##kamos Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param##Oka}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param##Okalmos Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param##OkalmosSpeculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${var##Okalmos Speculos}'

	launch_show "% and %% no pattern matching"
	test_launch 'param="Okalmos Speculos"' 'echo ${param%}'
	test_launch 'param="Okalmos Speculos"' 'echo ${%}'
	test_launch 'param="Okalmos Speculos"' 'echo ${%os}'
	test_launch 'param="Okalmos Speculos"' 'echo ${%param}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param%param}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param%s}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param% Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param%Okalmos Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param%kalmos Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param%kamos Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param%Oka}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param%Okalmos Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param%OkalmosSpeculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${var%Okalmos Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param%%}'
	test_launch 'param="Okalmos Speculos"' 'echo ${%%}'
	test_launch 'param="Okalmos Speculos"' 'echo ${%%os}'
	test_launch 'param="Okalmos Speculos"' 'echo ${%%param}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param%%param}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param%%s}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param%% Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param%%Okalmos Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param%%kalmos Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param%%kamos Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param%%Oka}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param%%Okalmos Speculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${param%%OkalmosSpeculos}'
	test_launch 'param="Okalmos Speculos"' 'echo ${var%%Okalmos Speculos}'

	launch_show "% pattern matching"

finish
