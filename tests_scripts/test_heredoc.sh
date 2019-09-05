# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_heredoc.sh                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/03 10:58:30 by jdugoudr          #+#    #+#              #
#    Updated: 2019/09/05 13:26:12 by jdugoudr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Heredoc"
	launch "Simple heredoc"
	test_launch_pipe ./tests_files/heredoc_1
	test_launch_pipe ./tests_files/heredoc_2
	test_launch_pipe ./tests_files/heredoc_3
	test_launch_pipe ./tests_files/heredoc_4
	test_launch_pipe ./tests_files/heredoc_5
	test_launch_pipe ./tests_files/heredoc_6
	launch "Expansion heredoc"
	test_launch_pipe ./tests_files/heredoc_7
	test_launch_pipe ./tests_files/heredoc_8
	test_launch_pipe ./tests_files/heredoc_9
	test_launch_pipe ./tests_files/heredoc_10
	test_launch_pipe ./tests_files/heredoc_11
	test_launch_pipe ./tests_files/heredoc_12
	test_launch_pipe ./tests_files/heredoc_13
	test_launch_pipe ./tests_files/heredoc_14
	launch "Hard"
	test_launch_pipe ./tests_files/heredoc_15
	test_launch_pipe ./tests_files/heredoc_16
	test_launch_pipe ./tests_files/heredoc_17
	test_launch_pipe ./tests_files/heredoc_18
	test_launch_pipe ./tests_files/heredoc_19
	test_launch_pipe ./tests_files/heredoc_20
