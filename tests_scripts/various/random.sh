#!/bin/bash


## Usage : 
##	./launcher [-v] [-q] [-2] [-e] [file]
##		-v : Activate Valgrind tests
##		-2 : Activate comparison on stderr
##		-q : Activate quiet mode : only show OK or KO
##		-e : Show only failed tests (hide [OK])
##		-r : Compare returned values with bash
##		file : give the name of a file, or simply it's kind
##			(ex : expansions for test_expansions.sh)
##			else, every files would be launched

path=".."
suppressions_file=".my_supp.supp"
exec="42sh"
log_dir="logs" # watchout we rm -rf this

test_stderr=""
verbose="ok"
show_error=""
test_returned_values=""
file=""
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

	if [ -f "test_${arg}.sh" ] ; then
		file="$file test_${arg}.sh"
	elif [ -f "${arg}" ] ; then
		file="$file ${arg}"
	fi
done

if [ ! -z $valgrind ] ; then
	echo "initializing the valgrind configuration..."
	./init.sh
	echo "OK !"
fi

green="\\033[32m"
yellow="\\033[33m"
red="\\033[31m"
eoc="\\033[0m"

((passed=0))
((tried=0))
((diff_passed=0))
((diff_tried=0))

source functions.sh

random ()
{
	cat /dev/random | LC_CTYPE=C tr -dc "$RANDOM_CHARS" | head -c "$RANDOM_LEN" > file
}

test_random_input ()
{
	if [ `grep -i -c rm file` -ne 0 ]  ; then return 1 ; fi
	if [ `grep -i -c mv file` -ne 0 ]  ; then return 1 ; fi
	if [ `grep -i -c cp file` -ne 0 ]  ; then return 1 ; fi
	if [ `grep -i -c ln file` -ne 0 ]  ; then return 1 ; fi
	if [ `grep -i -c git file` -ne 0 ] ; then  return 1 ; fi
	return 0
}

rm -f tests_launched

mkdir -p random_sandbox/protection_dir/protection_dir/protection_dir/protection_dir/
cd random_sandbox/protection_dir/protection_dir/protection_dir/protection_dir/

#RANDOM_CHARS=" \"\'\\\`     qwertyuiopasdfghjklzxcvbnm1234567890!@#$%^&*()_+                       "
# RANDOM_CHARS="\"\`\`\ [:blank:][:alnum:][:space:][:space:][:print:]\\\"\ "
RANDOM_CHARS="<<>>&&\"\`\`\'\'\"\"    azetyuioplknqds1230987654)({}\$\$\$\#\@\#\#\\\\\\\\ck\$\"\ [:space:][:space:]"
RANDOM_LEN=30

for i in {1..200} ; do
	RANDOM_LEN=$i
	for j in {1..100} ; do
		random
		cat file >> ../../../../../tests_launched
		echo "" >> ../../../../../tests_launched
		test_random_input
		if [ $? -eq 1 ] ; then continue ; fi
		test_launch_pipe file
	done
done

rm -f file
