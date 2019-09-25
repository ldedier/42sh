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
	launch_show "randomly generated"
	test_launch "${true}  okalm  ||  ${true}  0  &&  ${true}  1 "
	test_launch "${false} okalm  &&  ${true}  0  &&  ${false} 1  ||  ${false} 2 "
	test_launch "${false} okalm  &&  ${false} 0  &&  ${true}  1  ||  ${false} 2 "
	test_launch "${true}  okalm  &&  ${false} 0  &&  ${false} 1 "
	test_launch "${false} okalm  ||  ${false} 0  ||  ${false} 1 "
	test_launch "${false} okalm  &&  ${true}  0  ||  ${true}  1  ||  ${true}  2 "
	test_launch "${false} okalm  &&  ${true}  0  ||  ${false} 1 "
	test_launch "${false} okalm  &&  ${false} 0  ||  ${true}  1  ||  ${false} 2 "
	test_launch "${false} okalm  ||  ${true}  0  &&  ${true}  1 "
	test_launch "${true}  okalm  &&  ${true}  0  ||  ${false} 1  ||  ${true}  2 "
	test_launch "${false} okalm  ||  ${false} 0  ||  ${false} 1  ||  ${false} 2 "
	test_launch "${false} okalm  ||  ${false} 0  ||  ${true}  1  &&  ${false} 2 "
	test_launch "${true}  okalm  &&  ${false} 0  &&  ${false} 1  ||  ${true}  2 "
	test_launch "${false} okalm  &&  ${false} 0 "
	test_launch "${true}  okalm  ||  ${false} 0  &&  ${true}  1  &&  ${true}  2 "
	test_launch "${true}  okalm  &&  ${false} 0  ||  ${false} 1 "
	test_launch "${false} okalm  &&  ${false} 0  ||  ${false} 1 "
	test_launch "${true}  okalm "
	test_launch "${false} okalm  &&  ${true}  0  ||  ${true}  1 "
	test_launch "${false} okalm  ||  ${false} 0  ||  ${true}  1  ||  ${false} 2 "
	test_launch "${false} okalm  ||  ${true}  0  ||  ${false} 1 "
	test_launch "${true}  okalm  ||  ${false} 0  &&  ${false} 1  &&  ${true}  2 "
	test_launch "${false} okalm  &&  ${true}  0  &&  ${true}  1 "
	test_launch "${true}  okalm  ||  ${false} 0  &&  ${true}  1 "
	test_launch "${true}  okalm  ||  ${true}  0  &&  ${true}  1  ||  ${true}  2 "
	test_launch "${false} okalm  ||  ${true}  0 "
	test_launch "${true}  okalm  ||  ${false} 0  &&  ${true}  1  &&  ${false} 2 "
	test_launch "${false} okalm  ||  ${false} 0  ||  ${false} 1  ||  ${true}  2 "
	test_launch "${false} okalm  &&  ${false} 0  ||  ${true}  1  &&  ${true}  2 "

finish