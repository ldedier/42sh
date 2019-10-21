#!/bin/bash

## Colors
red=\\033[31m green=\\033[32m yellow=\\033[33m blue=\\033[34m
pink=\\033[35m cyan=\\033[36m grey=\\033[37m eoc=\\033[0m

# set -o xtrace
# set -o verbose

input="./non_interactive.txt"
log_42="../logs/42sh.log"
log_bash="../logs/bash.log"

# touch $log_bash $log_42

rm $log_42 $log_bash

while IFS= read -r line
do
	echo -e ${yellow}$line${eoc}
	echo $line > infile
	bash < infile >> $log_bash
	../../../../42sh < infile >> $log_42
	x=`diff $log_bash $log_42`
	echo $x
	if [$x == ""]
		then	echo -e ${green}OK${eoc}
		else	echo -e ${red}KO${eoc}
	fi
	rm infile
done < "$input"