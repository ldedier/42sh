#!/bin/bash

path=".."
suppressions_file=".my_supp.supp"
exec="42sh"
log_dir="logs" # watchout we rm -rf this

test_stderr=""
verbose="ok"
show_error=""
test_returned_values=""
file=""

#Colors
red=\\033[31m
green=\\033[32m
yellow=\\033[33m
blue=\\033[34m
pink=\\033[35m
cyan=\\033[36m
grey=\\033[37m
eoc=\\033[0m

for arg in $@ ; do
	if [ "$arg" = "-v" ] ; then
		valgrind=true
		rm -rf "${log_dir}"
		mkdir -p $log_dir
	fi

	if [ "$arg" = "-2" ] ; then
		test_stderr="ok"
	fi

	if [ "$arg" = "-q" ] ; then
		verbose=""
	fi

	if [ "$arg" = "-e" ] ; then
		show_error="ok"
	fi

	if [ "$arg" = "-r" ] ; then
		test_returned_values="ok"
	fi

	if [ "$arg" = "-env" ] ; then
		controlled_env="ok"
	fi
done


source functions.sh

if [ -n "$1" ] ; then
	launch_test buffer
else
	exit 1
fi

exit $?