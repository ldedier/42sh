# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_globbing.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 05:23:32 by jmartel           #+#    #+#              #
#    Updated: 2019/11/26 01:32:39 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Globbing"
	launch_show "Creating sandbox ..."

	pwd=`pwd`

	rm -rf sandbox
	python3 srcs/globbing_sandbox.py

	cd sandbox
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
	test_launch 'cd sandbox' 'echo ["ab"]' "echo ['ab']"
	test_launch 'cd sandbox' 'echo [""""]' 'echo [""]'
	test_launch 'cd sandbox' 'echo ["a-b\""""b-b"]'
	test_launch 'cd sandbox' 'echo [\"ab]' "echo [\'ab]" 'echo [\\ab]?' 'echo [\"ab]?' "echo [\'ab]?" 'echo [\\ab]?'
	test_launch 'cd sandbox' 'echo []' 'echo [][]' 'echo ?[]?[]?' 'echo []?[]?[]'
	test_launch 'cd sandbox' ''

	launch_show "brace quoted"
	test_launch 'cd sandbox' 'echo [!a-ba\ ]'
	test_launch 'cd sandbox' 'echo "[!a-bz ]"' 'echo "[!a-bz]"'
	test_launch 'cd sandbox' 'echo [\!a-x]' 'echo [\!a-x]/*' 'echo [\!a-x]*' 'echo [\!a-x]/***'
	test_launch 'cd sandbox' 'echo \\[a]'
	test_launch 'cd sandbox' 'echo *[a-]b]' 'echo *[a-]b]*' 'echo [a-]b]*'

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
	test_launch 'nocmd *'
	test_launch 'nocmd */*'
	test_launch 'nocmd */*/*'

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

	launch_show 'old errors'
	test_launch 'cd sandbox' 'echo ?*' 'echo *?' 'echo *???*'
	test_launch 'cd sandbox' 'echo ?*/*?'
	test_launch 'cd sandbox' 'echo ????*/*/*?'

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
	test_launch 'cd empty' 'mkdir -p "[x"' 'touch "[x/foo" 11 22 223'
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

	launch_show "Absolute path"
	test_launch 'ls /de*'
	test_launch 'ls ~/De*'
	test_launch 'echo "/tmp"/*' 'echo "/tmp/"*'
	test_launch "echo '/tmp/'"'*' "echo '/tmp'/"'*' "echo /'tmp'/"'*'
	test_launch 'echo """"/tmp"""/*'
	test_launch 'echo ls ~/Desktop/[.][.abv]*'
	test_launch 'echo \/\t\m\p\/'

	launch_show "Globbing and field splitting"
	test_launch 'cd sandbox' 'var="*      *"' 'echo $var'
	test_launch 'cd sandbox' 'var="*      *"' 'echo "$var"'
	test_launch 'cd sandbox' 'var="*"' ' echo $var$var' 'echo "$var   $var"'
	test_launch 'cd sandbox' 'var=?*/      ???????*' 'echo $var' 'echo "$var"'

	rm -rf empty
	rm -rf sandbox

  	mkdir "./test_globbing" && cd "./test_globbing" && touch 'a' 'b' 'c' 'd' 'e' 'f' '!' '^' && cd ..
	launch_show "wesh tests"
	test_launch 'cd "./test_globbing"' '../obj/write_arguments [abc\]def]'
	test_launch 'cd "./test_globbing"' '../obj/write_arguments [abc\\\]def]'
	test_launch 'cd "./test_globbing"' '../obj/write_arguments [abc\\\\\]def]'
	test_launch 'cd "./test_globbing"' '../obj/write_arguments [abc\\\\\\\]def]"'
	rm -rf test_globbing

	test_launch 'tester'
	test_launch 'mkdir tester_dir ; cd tester_dir ; touch a b c d e f z "]" ' './obj/write_arguments [abc\]def]'
	test_launch 'tester_dir' './obj/write_arguments [abc\\\]def]'
	test_launch 'tester_dir' './obj/write_arguments [abc\\\\\]def]'
	test_launch 'tester_dir' './obj/write_arguments [abc\\\\\\\]def]' 'cd .. ; rm -rf tester_dir'
	rm -rf tester_dir

finish
