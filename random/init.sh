#!/bin/bash

path=".."
exec="42sh"
log_dir="logs" # watchout we rm -rf this

red=\\033[31m
eoc=\\033[0m

rm -f failed_commands

rm -rf $log_dir && mkdir -p $log_dir

if [ ! -f .my_supp.supp ] ; then
	./.init_valgrind.sh
fi

make -C $path 1>/dev/null && cp ${path}/${exec} .

if [ $? -ne 0 -o ! -e "./${exec}" ] ; then
	echo -e "${red}Can't copy ${exec}${eoc}"
	exit 1
fi

exit 0
