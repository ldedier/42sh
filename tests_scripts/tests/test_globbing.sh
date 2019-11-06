# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_globbing.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 05:23:32 by jmartel           #+#    #+#              #
#    Updated: 2019/11/07 00:23:41 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Globbing"
	launch_show "Creating sandbox ..."

	pwd=`pwd`
	rm -rf sandbox

	mkdir -p sandbox && cd sandbox
	touch file1 file1file1 file1file1file1file1 file2 file3 file4 "[ab]" "[" "]" "[aa" "a]a" '!' file2file2 file2file2file2
	touch '[' ']' '(' ')' x X xx XX xxx XXX xxxx XXXX 
	touch '\' '\\' '\\\' '\\[\]' '\[' '\]' '\!'
	for i in `seq 1 10` ; do
		touch `echo "print('a' * $i)" | python3`
		touch `echo "print('b' * $i)" | python3`
		touch `echo "print('b' * $i)" | python3`
		touch `echo "print('O' * $i)" | python3`
	done
	mkdir -p UUU/B/file2 ; touch UUU/B/file2/okalm 
	mkdir -p 1/2/3/4/5/6/7/8/9/
	for i in `seq 1 9` ; do
		cd $i 
		touch fils ok 123 '[' ']' '!' '*' '**' '\' '\\' 'VA' 'POS'
		mkdir okalm
		mkdir -p dir '""' quoted
	done
	for i in `seq 1 9` ; do cd .. ; done
	
	for i_dir in `seq 0 5` ; do
		mkdir -p dir_$i_dir
		for i_file in `seq 3 12` ; do
			touch dir_${i_dir}/file_${i_dir}_${i_file}
			mkdir -p dir_${i_dir}/sub_dir_${i_dir}_${i_file}
			touch dir_${i_dir}/sub_dir_${i_dir}_${i_file}/${i_dir}_${i_file}
			touch dir_${i_dir}/sub_dir_${i_dir}_${i_file}/a
			touch dir_${i_dir}/sub_dir_${i_dir}_${i_file}/aa
			touch dir_${i_dir}/sub_dir_${i_dir}_${i_file}/aaa
			touch dir_${i_dir}/sub_dir_${i_dir}_${i_file}/okalm
			touch dir_${i_dir}/sub_dir_${i_dir}_${i_file}/"***"
			touch dir_${i_dir}/sub_dir_${i_dir}_${i_file}/'!'
		done
	done

	cd ${pwd}

	launch_show "Simple"
	test_launch 'cd sandbox' 'ls *'
	test_launch 'cd sandbox' 'ls */*'
	test_launch 'cd sandbox' 'ls */*/ '
	test_launch 'cd sandbox' 'ls */*/*'
	test_launch 'cd sandbox' 'ls [a]/*/*'
	test_launch 'cd sandbox' 'ls [!ab]/*/*'
	test_launch 'cd sandbox' 'ls [!a-X]/*/*'
	test_launch 'cd sandbox' 'ls [!a-x]/*/*'
	test_launch 'cd sandbox' 'ls [a-x]/*/*'
	test_launch 'cd sandbox' 'ls ?*'
	test_launch 'cd sandbox' 'ls *?'
	test_launch 'cd sandbox' 'ls ?*?'
	test_launch 'cd sandbox' 'ls .*'
	test_launch 'cd sandbox' 'ls ./*'

	launch_show "brace"
	test_launch 'cd sandbox' 'echo [a] ; echo $?' 'echo [a]* ; echo $?' 'echo [!a]  ; echo $?'
	test_launch 'cd sandbox' 'echo [a-a][a-a]   ; echo $?' 'echo [!a][!a]  ; echo $?' 'echo [!] ; echo $?'
	test_launch 'cd sandbox' 'echo [a-aa-ab-bb-b]   ; echo $?' 'echo [!a-aa-ab-bb-b]  ; echo $?' 'echo [!a-a!a-a!b-bb-b] ; echo $?' 'echo [!a-aa-ab-b!b!-b] ; echo $?'
	test_launch 'cd sandbox' 'echo [!] ; echo $?' 'echo [\!] ; echo $?' 'echo [!\!] ; echo $?' 'echo [!!] ; echo $?'

	launch_show "brace quoted"
	test_launch 'cd sandbox' 'echo [!a-ba\ ]'
	test_launch 'cd sandbox' 'echo "[!a-bz ]"' 'echo "[!a-bz]"'
	test_launch 'cd sandbox' 'echo [\!a-x]' 'echo [\!a-x]/*' 'echo [\!a-x]*' 'echo [\!a-x]/***'
	test_launch 'cd sandbox' 'echo \\[a]'
	test_launch 'cd sandbox' ''

	launch_show "star"
	test_launch 'cd sandbox' 'echo *' 'echo *' 'echo .*' 'echo ./*' 'echo **' 'echo ***'
	test_launch 'cd sandbox' 'echo \*'
	test_launch 'cd sandbox' 'echo ../**/../**' 'echo [a]*[b] ; echo $?' 'echo [!a]*[!b] ; echo $?' 'echo ?*? ; echo $?'
	test_launch 'cd sandbox' 'echo */*/' 'echo */*'
	test_launch 'cd sandbox' 'echo /*/*' 'echo /*/*/'
	test_launch 'cd sandbox' 'echo /*' 'echo /*/'

	launch_show "question mark"
	test_launch 'cd sandbox' 'ls file?' 'ls file?*'
	test_launch 'cd sandbox' 'echo file?' 'echo ?????'
	test_launch 'cd sandbox' 'echo ?????/????????' 
	test_launch 'cd sandbox' 'ls ?????/????????'
	test_launch 'cd sandbox' 'ls ?????/????????/'
	test_launch 'cd sandbox' 'echo ?????/??????_?/'
	test_launch 'cd sandbox' 'echo ?????/??????_??/' 'echo ?????/??????_??'
	test_launch 'cd sandbox' 'echo dir??/??????_?/*/*' 'echo dir??/sub_dir_[0-5]_[3-8]/???'
	test_launch 'cd sandbox' 'echo dir??/sub_dir_[0-5]_[3-8]/???' 'echo dir??/sub_dir_[!0-5]_[3-8]/??'
	test_launch 'cd sandbox' 'echo dir??/sub_dir_[0-5]_[3-8]/???' 'echo dir??/sub_dir_[!023]_[821]/??'
	test_launch 'cd sandbox' 'echo ? ?*/*'

	launch_show "old errors"
	test_launch 'cd sandbox' 'echo file?' 'echo file\?'
	test_launch 'cd sandbox' 'echo file*' 'echo file\*'
	test_launch 'cd sandbox' 'echo file[1-2] ; echo file[!1-3]' 'echo file\[1-2]'
	test_launch 'cd sandbox' 'echo file\[1-2]'
	test_launch 'cd sandbox' 'echo file\[!1-2]'
	test_launch 'cd sandbox' 'echo file"[!2-3]"'
	test_launch 'cd sandbox' 'echo .*/"a"* '
	test_launch 'echo /dev/*'

	launch_show "Permissions"
	test_launch 'cd sandbox' 'touch permission ; chmod 700 permission' 'echo ?????????? ; echo $?' 'echo ??????????/ ; echo $?' 'echo perm* ; echo $?' 'chmod 777 permission ; rm permission'
	test_launch 'cd sandbox' 'touch permission ; chmod 600 permission' 'echo ?????????? ; echo $?' 'echo ??????????/ ; echo $?' 'echo perm* ; echo $?' 'chmod 777 permission ; rm permission'
	test_launch 'cd sandbox' 'touch permission ; chmod 500 permission' 'echo ?????????? ; echo $?' 'echo ??????????/ ; echo $?' 'echo perm* ; echo $?' 'chmod 777 permission ; rm permission'
	test_launch 'cd sandbox' 'touch permission ; chmod 400 permission' 'echo ?????????? ; echo $?' 'echo ??????????/ ; echo $?' 'echo perm* ; echo $?' 'chmod 777 permission ; rm permission'
	test_launch 'cd sandbox' 'touch permission ; chmod 300 permission' 'echo ?????????? ; echo $?' 'echo ??????????/ ; echo $?' 'echo perm* ; echo $?' 'chmod 777 permission ; rm permission'
	test_launch 'cd sandbox' 'touch permission ; chmod 200 permission' 'echo ?????????? ; echo $?' 'echo ??????????/ ; echo $?' 'echo perm* ; echo $?' 'chmod 777 permission ; rm permission'
	test_launch 'cd sandbox' 'touch permission ; chmod 100 permission' 'echo ?????????? ; echo $?' 'echo ??????????/ ; echo $?' 'echo perm* ; echo $?' 'chmod 777 permission ; rm permission'

	test_launch 'cd sandbox' 'mkdir permission ; chmod 700 permission' 'echo ?????????? ; echo $?' 'echo ??????????/ ; echo $?' 'echo perm* ; echo $?' 'echo perm*/ ; echo $?' 'chmod 777 permission ; rm -r permission'
	test_launch 'cd sandbox' 'mkdir permission ; chmod 600 permission' 'echo ?????????? ; echo $?' 'echo ??????????/ ; echo $?' 'echo perm* ; echo $?' 'echo perm*/ ; echo $?' 'chmod 777 permission ; rm -r permission'
	test_launch 'cd sandbox' 'mkdir permission ; chmod 500 permission' 'echo ?????????? ; echo $?' 'echo ??????????/ ; echo $?' 'echo perm* ; echo $?' 'echo perm*/ ; echo $?' 'chmod 777 permission ; rm -r permission'
	test_launch 'cd sandbox' 'mkdir permission ; chmod 400 permission' 'echo ?????????? ; echo $?' 'echo ??????????/ ; echo $?' 'echo perm* ; echo $?' 'echo perm*/ ; echo $?' 'chmod 777 permission ; rm -r permission'
	test_launch 'cd sandbox' 'mkdir permission ; chmod 300 permission' 'echo ?????????? ; echo $?' 'echo ??????????/ ; echo $?' 'echo perm* ; echo $?' 'echo perm*/ ; echo $?' 'chmod 777 permission ; rm -r permission'
	test_launch 'cd sandbox' 'mkdir permission ; chmod 200 permission' 'echo ?????????? ; echo $?' 'echo ??????????/ ; echo $?' 'echo perm* ; echo $?' 'echo perm*/ ; echo $?' 'chmod 777 permission ; rm -r permission'
	test_launch 'cd sandbox' 'mkdir permission ; chmod 100 permission' 'echo ?????????? ; echo $?' 'echo ??????????/ ; echo $?' 'echo perm* ; echo $?' 'echo perm*/ ; echo $?' 'chmod 777 permission ; rm -r permission'

	rm -rf sandbox

	launch_show "Correction"
	test_launch 'mkdir -p empty ; cd empty' 'touch a? b* [c]; ls -1'
	test_launch 'cd empty' 'echo a > aa && echo b > ab && cat -e a?'
	test_launch 'cd empty' 'rm -f *' 'ls'
	test_launch 'cd empty' 'mkdir -p one/two'
	test_launch 'cd empty' 'echo "four" > one/two/three'
	test_launch 'cd empty' 'echo "four" > one/five'
	test_launch 'cd empty' 'cat ./*/*/* ./*/*'
	test_launch 'cd empty' 'ls /??r'
	test_launch 'cd empty' 'rm -rf ./*' 'ls'
	test_launch 'cd empty' 'mkdir -p "[x"' 'touch "[x/foo"'
	test_launch 'cd empty' 'echo [*; echo *[x; echo [x/*'
	test_launch 'cd empty' 'rm -rf *'
	test_launch 'cd empty' 'touch "a[a-z][x" "ab[x"'
	test_launch 'cd empty' 'echo a[a-z][*; echo a[a-z]*; echo a[a\-z]*'
	test_launch 'cd empty' 'rm -f *'
	test_launch 'cd empty' 'touch ".bc" "abc" "bbc" "cbc" "-bc" \!bc "+bc" ",bc" "0bc" "1bc"'
	test_launch 'cd empty' 'echo [ab-]*'
	test_launch 'cd empty' 'echo [-ab]*'
	test_launch 'cd empty' 'echo [!-ab]*'
	test_launch 'cd empty' 'echo [!ab]*'
	test_launch 'cd empty' 'echo []ab]*'
	test_launch 'cd empty' 'echo [+--]*'
	test_launch 'cd empty' 'echo [--1]*'
	test_launch 'cd empty' 'echo [z-a]*'
	test_launch 'cd empty' 'echo [a-a]bc'
	test_launch 'cd empty' 'rm -f * .*; ls -A'
	test_launch 'cd empty' 'touch aa bb cc 11 22 33'
	test_launch 'cd empty' 'echo **'
	test_launch 'cd empty' 'echo [!a-z]'
	test_launch 'cd empty' 'echo [4-z][A-b]'
	
	rm -rf empty

finish
