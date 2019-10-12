#!/bin/bash

x=`ps -ao pid,ppid,pgid,comm | grep sleep`
variable=`echo -e $x | awk -F" " '{print $1}'`
echo $variable
kill -$1 $variable
