#!/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    launcher.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 15:58:23 by jmartel           #+#    #+#              #
#    Updated: 2019/05/21 15:58:23 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Usage : 
##	./launcher [-v] [-q] [-2]
##		-v : Activate Valgrind tests
##		-2 : Activate comparison on stderr
##		-q : Activate quiet mode : only show OK or KO

path=".."
suppressions_file="my_supp.supp"
exec="21sh"
log_dir="logs" # watchout we rm -rf this

if [ "$1" = "-v" ] || [ "$2" = "-v" ] || [ "$3" = "-v" ]; then
	valgrind=true
	rm -rf "${log_dir}" 
	mkdir -p $log_dir
fi

if [ "$1" = "-q" ] || [ "$2" = "-q" ] || [ "$3" = "-q" ] ; then
	verbose=""
else
	verbose="ok"
fi

if [ "$1" = "-2" ] || [ "$2" = "-2" ] || [ "$3" = "-2" ]; then
	test_stderr=1
else
	test_stderr=0
fi

if [ ! -z $valgrind ] && [ ! -f $suppressions_file ] ; then
	echo "initializing the valgrind configuration..."
	./init.sh
	echo "OK !"
fi


#Colors
red=\\033[31m
green=\\033[32m
yellow=\\033[33m
blue=\\033[34m
pink=\\033[35m
cyan=\\033[36m
grey=\\033[37m
eoc=\\033[0m

make -C $path && cp ${path}/${exec} .

((passed=0))
((tried=0))
((diff_passed=0))
((diff_tried=0))

source functions.sh

for file in `ls test_*` ; do
	source $file
done

## Other tests
launch "Others"
	test 'mkdir test123 ; cd test123 ; ls -a ; ls | cat | wc -c > fifi ; cat fifi ; cd .. ; rm -r test123'
finish

rm ${exec}
echo "passed ${passed} valgrind tests out of ${tried}"
echo "passed ${diff_passed} diff tests out of ${diff_tried}"
rm -rf "${exec}.dSYM"
