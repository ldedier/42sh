# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_heredoc.sh                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/03 10:58:30 by jdugoudr          #+#    #+#              #
#    Updated: 2019/09/05 16:04:11 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Heredoc"
	launch_show "Simple heredoc"
		for i in `seq 1 6`; do
			test_launch_pipe ./tests_files/heredoc/heredoc_${i}
		done
	launch_show "Expansion heredoc"
		for i in `seq 7 14`; do
			test_launch_pipe ./tests_files/heredoc/heredoc_${i}
		done
	launch_show "Hard"
		for i in `seq 15 20`; do
			test_launch_pipe ./tests_files/heredoc/heredoc_${i}
		done
	launch_show "Quoting"
		for i in `seq 21 30` ; do
			test_launch_pipe ./tests_files/heredoc/heredoc_${i}
		done
	launch_show "Parameter expansion"
		for i in `seq 31 35` ; do
			test_launch_pipe ./tests_files/heredoc/heredoc_${i}
		done
	launch_show "Tilde"
		for i in `seq 36 40` ; do
			test_launch_pipe ./tests_files/heredoc/heredoc_${i}
		done
	launch_show "fd"
		for i in `seq 41 43` ; do
			test_launch_pipe ./tests_files/heredoc/heredoc_${i}
		done


finish
