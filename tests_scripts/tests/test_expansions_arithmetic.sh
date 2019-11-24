# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_expansions_arithmetic.sh                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/17 19:22:25 by jmartel           #+#    #+#              #
#    Updated: 2019/11/25 00:17:31 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "arithmetic"
	launch_show ""
	test_launch ''

	launch_show "Basic"
	test_launch 'echo $((12   +   3)) ; echo $?' 'echo $?'
	test_launch 'echo $((3 -   7)) ; echo $?' 'echo $?'
	test_launch 'echo $((-6    / 4)) ; echo $?' 'echo $?'
	test_launch 'echo $((   7  + 2  * -5)) ; echo $?' 'echo $?'
	test_launch 'echo $((  3    %   1   + 2 )) ; echo $?' 'echo $?'
	test_launch 'echo $((3  %  4)) ; echo $?' 'echo $?'
	test_launch 'echo $((2  > 1 * 4)) ; echo $?' 'echo $?'
	test_launch 'echo $((5 <= 5)) ; echo $?' 'echo $?'
	test_launch 'echo $((6 > 3*2)) ; echo $?' 'echo $?'
	test_launch 'echo $((2147483647 + 2)) ; echo $?' 'echo $?'
	test_launch 'a=0 ; b=0 ; echo $((a+++b)) ; echo $?' 'echo $a $b $?'
	test_launch 'a=0 ; b=0 ; echo $((a+ ++b)) ; echo $?' 'echo $a $b $?'
	test_launch 'a=0 ; b=0 ; echo $((a++ +b)) ; echo $?' 'echo $a $b $?'

	launch_show "Testing implementation"
	test_launch 'a=var1' 'echo $((a+1)) ; echo $?' 'echo $((a++ + 2)) ; echo $?' 'echo $? $a $b'
	test_launch 'a=hid42den' 'echo $((a + 5)) ; echo $?' 'echo $a $b $?'
	
	launch_show 'syntax error'
	test_launch  'echo $(()) ; echo $?' 'echo $a $b $?'
	test_launch  'echo $((+)) ; echo $?' 'echo $a $b $?'
	test_launch  'echo $((12*)) ; echo $?' 'a=23 ; echo $((a*)) ; echo $?' 'echo $a $b $?'
	test_launch  'echo $((**12)) ; echo $?' 'echo $a $b $?'
	test_launch  'echo $((/5)) ; echo $?' 'echo $a $b $?'

	test_launch 'echo $((1---42))'
	test_launch 'a=10; b=20; echo $((a-b)) ; echo $?' ' echo $a $b $?'
	test_launch 'a=10; b=20; echo $((a---b)) ; echo $?' ' echo $a $b $?'
	test_launch 'a=10; b=20; echo $((a-----b)) ; echo $?' ' echo $a $b $?'
	test_launch 'a=10; b=20; echo $((a------b)) ; echo $?' ' echo $a $b $?'
	test_launch 'a=10; b=20; echo $((a--++-b)) ; echo $?' ' echo $a $b $?'
	test_launch 'a=10; b=20; echo $((a-++---b)) ; echo $?' ' echo $a $b $?'
	test_launch 'a=10; b=20; echo $((a-++-++b)) ; echo $?' ' echo $a $b $?'
	test_launch 'a=10; b=20; echo $((a-++--b)) ; echo $?' ' echo $a $b $?'
	test_launch 'a=10; b=20; echo $((a+--++--b)) ; echo $?' ' echo $a $b $?'

	test_launch 'echo $((-10+3/1000000000000000000000000000000000000000))'

	test_launch 'echo $((1 - - - - + + + - - - - + + + - - - - 5 > 4)) ; echo $?' 'echo $?'
	test_launch 'echo $((1 - - - - + + + - - - - + + + - - - - 5 > 6)) ; echo $?' 'echo $?'
	test_launch 'echo $((1 - - - - + + + - - - - + + + - - - - 5 == 6)) ; echo $?' 'echo $?'

	test_launch 'echo $((2147483647  *  5)) ; echo $?' 'echo $?'
	test_launch 'echo $((-2147483647 / 2 *7 * -1)) ; echo $?' 'echo $?'
	test_launch 'echo $((77777777 % 7 * 4 -5 +8 /8)) ; echo $?' 'echo $?'
	test_launch 'echo $((123412+213-4123*12/23-421+123%123*2)) ; echo $?' 'echo $?'

	launch_show "Recursive expansions"
	test_launch 'var=Tamer v=12 ___=54 var234=-8 ; echo $?' 'echo $((6 - $var234+45)) ; echo $?' 'echo $?'
	test_launch 'var=Tamer v=12 ___=54 var234=-8 ; echo $?' 'echo $((34 + $var2342 % 4+45)) ; echo $?' 'echo $?'
	test_launch 'var=Tamer v=12 ___=54 var234=-8 ; echo $?' 'echo $(($var2342++ -7 * 8)) ; echo $?' 'echo $?'
	test_launch 'var2=var var=Tamer v=12 ___=54 var234=-8' 'echo $((${var}++ * 7 )) ; echo $var $var2 ; echo $?' 'echo $?'
	test_launch 'var=Tamer v=12 ___=54 var234=-8 ; echo $?' 'echo $((12 + $var-- * 9 + 7)) ; echo $var $var2 ; echo $?' 'echo $?'
	test_launch 'var=Tamer v=12 ___=54 var234=-8 ; echo $?' '___=$((7 - ___++ - 5))' 'echo $___ ; echo $?' 'echo $?'
	test_launch 'var=Tamer v=12 ___=54 var234=-8 ; echo $?' 'echo $((11 == v++)) $((12 == v++)) $((12 == v++)) ; echo $?' 'echo $?'
	test_launch 'var=Tamer v=12 ___=54 var234=-8 ; echo $?' 'echo $((75 * $((v++ * 8 + ${v})))) ; echo $?' 'echo $?'
	# test_launch 'var=Tamer v=12 ___=54 var234=-8 ; echo $?' 'echo $(($((var++)var + 2))) ; echo $?' 'echo $?'
	test_launch 'var=Tamer v=12 ___=54 var234=-8 ; echo $?' 'echo $(($((var))++)) ; echo $?' 'echo $?'

	launch_show "invalid characters"
	test_launch 'echo $((12-^^^))'
	test_launch 'echo $(())'

	launch_show "quotes"

	launch_show "randomly generated"
	test_launch 'echo $((333||33)) ; echo $?' 'echo $?'
	test_launch 'echo $((8)) ; echo $?' 'echo $?'
	test_launch 'echo $((7663||1)) ; echo $?' 'echo $?'
	test_launch 'echo $((8+-+22)) ; echo $?' 'echo $?'
	test_launch 'echo $((28!=740++88/654)) ; echo $?' 'echo $?'
	test_launch 'echo $((84%35+8)) ; echo $?' 'echo $?'
	test_launch 'echo $((86758/3874125 >= 587438741*6587524256874))'
	test_launch 'echo $((35847 * 793746946466858476874)) ; echo $? ' 'echo $?'
	test_launch 'echo $((7854695221584654/0        *0)) ; echo $?' 'echo $?'
	test_launch 'echo $((1<=-1>=28>=45)) ; echo $?' 'echo $?'
	test_launch 'echo $((---------1*-----1)) ; echo $?' 'echo $?'
	test_launch 'echo $((-2*-2+2/2)) ; echo $?' 'echo $?'
	test_launch 'echo $((/>=<=* == 2)) ; echo $?' 'echo $?'

	launch_show 'correction'
	test_launch 'echo $((1+2)) ; echo $?' 'echo $?'
	test_launch 'echo $((1-2)) ; echo $?' 'echo $?'
	test_launch 'echo $((1+1))$((2+2))$((3+3)) ; echo $?' 'echo $?'
	test_launch 'a=1+1; echo $((${a})) ; echo $?' 'echo $?'
	test_launch 'b=4; echo $((b++)) $((++b)) $((--b)) $((b--)) ; echo $?' 'echo $?'
	test_launch 'echo $((65536 * 256 / 1024 % 2147483648)) ; echo $?' 'echo $?'
	test_launch 'echo $((2<3>0<=1>=2==0!=1)) ; echo $?' 'echo $?'
	test_launch 'c=8; echo $((123<=123 && 42%42 || c++ + 34)) ; echo $?' 'echo $?'

finish
