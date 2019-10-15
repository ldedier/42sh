# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_redirections.sh                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:50 by jmartel           #+#    #+#              #
#    Updated: 2019/10/14 22:52:04 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Redirections tests
launch "Redirections"
	test_launch "echo Okalm > mybuf ; cat mybuf | wc -c ; rm mybuf"
	test_launch "echo tamer > file ; <file wc | cat | wc ; rm file"
	test_launch "echo tamer > file ; <file wc | cat | wc > file ; ls -a file ; rm file"
	test_launch "echo lol > file ; echo lalala | cat < file ; rm file"

## here doc
	test_launch "cat <<eoc" "ls -a" "okalm" "eoc"
	test_launch "ls <<eoc" "ls -a" "okalm" "eoc"
	test_launch "cat <<eoc 1>file1 2>file2" "ls -a" "okalm" "eoc" "cat file1" "cat file2" "rm file1 file2"
	test_launch "cat <<   eoc 1>file1 2>file2" "ls -a" "okalm" "eoc" "cat file1" "cat file2" "rm file1 file2"
	test_launch "cat <<   Okalm" "ls -a" "okalm" " Okalm" "Okalm " "Okalm"
	test_launch "cat << eof" "dqwdq\\\\" "dwqdq\\" " dqwdq\\" "haha " "e\\" "o\\" "f"
	test_launch "cat << eof" "dqwdq\\\\\\" "dwqdq\\" " dqwdq\\" "haha " "e\\" "o\\" "f\\"
	test_launch "cat << eof" "dqwdq\\\\\\" "dwqdq\\" " d\\qwd\\\\qdqwd\\qdqwd\\" "haha " "e\\" "o\\" "f\\"

## Closing fd
	test_launch "echo lol 1>&-" "ls -a"
	test_launch "ls nofile 2>&-"
	test_launch "nocmd 2>&-"

## Duplicationg fd
	test_launch 'ls nowhere 2>&1 ; echo $?'
	test_launch 'ls . 1>&filename ; echo $?' 'cat filename ; rm filename'
	test_launch 'ls nowhere 2<&1 ; echo $?'
	test_launch 'ls nowhere 2<&filename ; echo $?' 'ls filename' 'cat filename ; rm -f filename'
	test_launch 'ls 1<&2 | cat ; echo $?'
	test_launch 'ls 1>&2 2>&1 nofile || echo $?' 'echo $?'
	test_launch 'ls 1>&2 2>&1 nofile && echo $?' 'echo $?'
	test_launch 'ls 1>&2 2>&1 . || echo $?' 'echo $?'
	test_launch 'ls 1>&2 2>&1 . && echo $?' 'echo $?'
	test_launch 'ls 1>&2 2>&1 1>&- nofile && echo $?' 'echo $?'
	test_launch 'ls 1>&2 2>&1 1>&- nofile || echo $?' 'echo $?'
	test_launch 'ls 1>&2 2>&1 1>&- . && echo $?' 'echo $?'
	test_launch 'ls 1>&2 2>&1 1>&- . || echo $?' 'echo $?'
	test_launch 'ls 1>&2 2>&1 2>&- . || echo $?' 'echo $?'
	test_launch 'ls 1>&2 2>&1 2>&- . && echo $?' 'echo $?'
	test_launch 'ls 1>&2 2>&1 2>&- nofile || echo $?' 'echo $?'
	test_launch 'ls 1>&2 2>&1 2>&- nofile && echo $?' 'echo $?'
	test_launch 'ls 1>&2 2>&- . && echo $?' 'echo $?'
	test_launch 'ls 1>&2 2>&- . || echo $?' 'echo $?'
	test_launch 'ls 1>&2 1>&- . || echo $?' 'echo $?'
	test_launch 'ls 1>&2 1>&- . && echo $?' 'echo $?'
	test_launch 'ls 1>&2 2>&- nofile && echo $?' 'echo $?'
	test_launch 'ls 1>&2 2>&- nofile || echo $?' 'echo $?'
	test_launch 'ls 1>&2 1>&- nofile || echo $?' 'echo $?'
	test_launch 'ls 1>&2 1>&- nofile && echo $?' 'echo $?'

## Hard
	test_launch "echo lol > file ; echo lal > file2 ;  cat < file2 | cat -e < file ; rm file ; rm file2"
	test_launch "echo lol > file ; cat < file | cat -e << eoc ; rm file" "heredoc_1" "heredoc_2" "eoc"
	test_launch "echo lol > file ; cat -e < file << eoc ; rm file" "heredoc_1" "heredoc_2" "eoc"
	test_launch "echo lol > file ; cat -e < file << eoc  < file ; rm file" "heredoc_1" "heredoc_2" "eoc"
	test_launch "echo lol > file ; cat file | cat -e << eoc ; rm file" "heredoc_1" "heredoc_2" "eoc"
	test_launch "echo lol > file ; cat file | cat -e << eoc ; rm file" "heredoc_1" "heredoc_2" "not a eoc"
	test_launch "ls -a . nofile > file 2>&1 ; rm file"
	test_launch "ls -a . nofile 2>&1 > file ; rm file"
	test_launch "echo lol >&- file"
	test_launch "echo lol >>"
	test_launch "cat <<"
	test_launch "cat 1<&"
	test_launch "cat 1<&"
	test_launch "cat <&"
	test_launch "ls -l .dqwd qwd qw ~ 2>&1 | cat -e"
	test_launch "touch file ; cat < file >&- ; rm file"
	test_launch "echo lol > file ; cat < file <&- ; rm file"
	test_launch "echo \"lol iuuiuiu\" > file ; cat < file | cat -e >> file ; cat file ; rm file"
	test_launch "cat < dqfqwfqwdwef auteur"
	test_launch "cat < dqfqwfqwdwef auteur | cat"
	test_launch "cat < auteur < auteur < auteur < auteur < auteur < Makefile < dqwdqwdqwfqwf ; ls"
	test_launch "cat < auteur < auteur < auteur < auteur < auteur < auteur < dqwdqwdqwfqwf && ls"
	test_launch "cat < auteur < auteur < auteur < auteur < auteur < auteur < dqwdqwdqwfqwf || ls"
	test_launch "cat" "hello"
	test_launch "dwqdwq | cat"
	test_launch "cat | dqwd"
	test_launch "echo BEFORE ; echo tamer 5<&6 && echo ALLO?? ; echo AFTER"
	test_launch "echo lol > testmdr 2>&4 > testmdr2 ; ls ; rm testmdr testmdr2"
	test_launch "echo lol > testmdr 4>&4 > testmdr2 ; ls ; rm testmdr testmdr2"
	test_launch "echo lol > testmdr 4<&4 > testmdr2 ; ls ; rm testmdr testmdr2"
	test_launch "echo lol > testmdr 2<&4 > testmdr2 ; ls ; rm testmdr testmdr2"
	test_launch "echo dodo 12>&1 4>&12"
	test_launch "echo dodo 12>&12"
	test_launch "echo dodo 12>&12 4>&12"
	test_launch "echo dodo 1>&- 3>&- 4>&- 5>&-"

## With expansion
	test_launch 'TEST=file ; echo test > $TEST ; ls ; rm file'
	test_launch 'TEST= ; echo test > $TEST ; ls'
	test_launch 'echo test > $NOEXIST ; ls'
	test_launch 'TEST="test  with  space" ; echo test > $TEST ; ls ; rm $TEST'
	test_launch 'TEST="test  with  space" ; echo test > "$TEST" ; ls ; rm "$TEST"'
	test_launch 'file=buffer' 'echo tamertamer > buffer' 'cat $file' '<$file cat'
	test_launch 'file=buffer' 'echo tamertamer > buffer' 'cat $file' '< $file cat'
	test_launch 'file=buffer' 'echo okalm > $file' 'cat $file'
finish
