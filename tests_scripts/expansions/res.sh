#!/bin/bash

old_log_file="./logs/prev"
new_log_file="./logs/new"

new_ok=`grep -c OK $new_log_file`
old_ok=`grep -c OK $old_log_file`
new_ko=`grep -c KO $new_log_file`
old_ko=`grep -c KO $old_log_file`

if [ "$old_ok" -ne "$new_ok" ] ; then
	echo New Ok : $new_ok
	echo Old Ok : $old_ok
	echo ""
	echo New Ko : $new_ko
	echo Old Ko : $old_ko
else
	echo OK
fi
