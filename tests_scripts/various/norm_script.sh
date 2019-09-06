#!/bin/bash

norminette_iter()
{
	for file in $1/*;
	do
		if [ -d "$file" ]; then
			echo "browsing ${file}/..."
			norminette_iter $file
		else
			result=$(norminette $file | grep Error)
		fi
		normed_filed=$?
		if [ $normed_filed -eq 0 ]; then
			echo $file
			echo "$result"
			exit $normed_filed
		fi
	done
	return 1
}

#folder="."
#if [ ! -z "$1" ]; then 
#	folder=$1
#fi
#norminette_iter "$folder"

file="unknown"

norminette $1 | \
while read line; do
	echo "$line" | grep "Error" > /dev/null
	normed=$?
	if [ $normed -eq 0 ]; then
		echo "Error on: $file"
		pkill -f norminette
		exit 1;
	fi
	file=$line
done
