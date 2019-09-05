# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_heredoc.sh                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/03 10:58:30 by jdugoudr          #+#    #+#              #
#    Updated: 2019/09/05 13:43:12 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Heredoc"
	launch "Simple heredoc"
		for i in `seq 1 6`; do
			test_launch_pipe ./tests_files/heredoc_${i}
		done
	launch "Expansion heredoc"
		for i in `seq 7 14`; do
			test_launch_pipe ./tests_files/heredoc_${i}
		done
	launch "Hard"
		for i in `seq 15 20`; do
			test_launch_pipe ./tests_files/heredoc_${i}
		done
	launch "Quoting"
		for i in `seq 21 30` ; do
			test_launch_pipe ./tests_files/heredoc_${i}
		done
	launch "Parameter expansion"
		for i in `seq 31 35` ; do
			test_launch_pipe ./tests_files/heredoc_${i}
		done
	launch "Tilde"
		for i in `seq 36 40` ; do
			test_launch_pipe ./tests_files/heredoc_${i}
		done
	launch "fd"
		for i in `seq 41 45` ; do
			test_launch_pipe ./tests_files/heredoc_${i}
		done


finish
