#!/bin/bash

pid=`pgrep 42sh`

if [ -z $pid ] ; then
	echo "Can't find pid"
	exit 1
else
	echo "pid : $pid"
fi

lsof_start ()
{
	lsof -p $pid | awk '{print $1,$2,$3,$4,$5,$6,$8, $9,$10}'
}

lsof_start > start
while [ 1 -eq 1 ] ; do 
	if ps $pid > /dev/null ; then
		if ! diff start  <(lsof_start) ; then
			diff start <(lsof_start) >> fd_leaks.log
			echo -e \n\n >> fd_leaks.log
			lsof_start > start
		fi
	else
		rm -f start ; exit
	fi
	sleep 1
done

rm -f start
