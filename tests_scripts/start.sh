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
##	./start.sh [-v] [-q] [-2] [-e] [file]
##		-v : Activate Valgrind tests
##		-2 : Activate comparison on stderr
##		-q : Activate quiet mode : only show OK or KO
##		-e : Show only failed tests (hide [OK])
##		-r : Compare returned values with bash
##		file : give file path, or simply it's type
##			(ex : expansions for test_expansions.sh)
##			to launch only this file,
##			else every files would be launched

## Colors
red=\\033[31m green=\\033[32m yellow=\\033[33m blue=\\033[34m
pink=\\033[35m cyan=\\033[36m grey=\\033[37m eoc=\\033[0m

## Path to project
path=".."
## Executable name
exec="42sh"
## Directory for valgrind logs
log_dir="./logs" # watchout we rm -rf this
## Directory used to store local configurtation and binaries
obj_dir="./obj"
## Directory used to store binaries source code
src_dir="./srcs"

## Valgrind tests variables
suppressions_file="${obj_dir}/my_supp.supp"
error_exit_code=247

## Options initialisation
test_stderr="" verbose="ok" show_error="" test_returned_values="" file=""
## Counters initialisation
passed=0 tried=0 diff_passed=0 diff_tried=0

## Parse options given as arguments
for arg in $@ ; do
	if [ "$arg" = "-v" ] ; then
		valgrind=true
		rm -rf "${log_dir}"
		mkdir -p $log_dir
	fi

	if [ "$arg" = "-2" ] ; then
		test_stderr="ok" ; fi

	if [ "$arg" = "-q" ] ; then
		verbose="" ; fi

	if [ "$arg" = "-e" ] ; then
		show_error="ok" ;fi

	if [ "$arg" = "-r" ] ; then
		test_returned_values="ok" ; fi

	if [ -f "tests/test_${arg}.sh" ] ; then
		file="$file test_${arg}.sh"
	elif [ -f "${arg}" ] ; then
		file="$file ${arg}"
	fi
done

make -C $path && cp "${path}/${exec}" . || exit

source ${src_dir}/functions.sh

## Call initialisation functions
del_history
compile_executable
if [ ! -z $valgrind ] ; then init_valgrind ; fi

## Trapping ctrl + c signal to clean before exiting
trap clean_and_exit 2

## Call tests files : all or specified one
if [ -n "$file" ] ; then
	for f in $file ; do
		source $f
	done
else
	for file in `ls tests/test_*.sh` ; do
		source $file
	done
fi

## Show results message
if [ "$tried" -ne 0 ] ; then
	echo "passed ${passed} valgrind tests out of ${tried}"
fi
echo "passed ${diff_passed} diff tests out of ${diff_tried}"

## Cleaning
clean_and_exit
