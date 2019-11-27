# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    functions.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 15:58:19 by jmartel           #+#    #+#              #
#    Updated: 2019/09/02 16:33:43 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

echo_ok()
{
	if [ ! -n "$show_error" ] ; then
		echo -e ${green}"OK"${eoc}
	fi
	diff_passed=$((diff_passed+1))
}

diff_files()
{
	res=`diff $1 $2`
	if [ -n "$res" ] ; then
		echo -e "${red}KO${eoc}"
		echo -e "${yellow}`cat buffer`${eoc}"
		if [ -n "$verbose" ] ; then
			echo -e "${cyan}" `cat $1` "${eoc}"
			echo -e "${cyan}" `cat $2` "${eoc}"
		fi
		return 1
	fi
	return 0
}

valgrind_test()
{
		tried=$((tried+1))
		tmp_log_file="tmp_log"
		inner_log_dir="${log_dir}/test_${tried}"
		error_exit_code=247

	cat buffer

		valgrind --leak-check=full --suppressions=$suppressions_file \
			--error-exitcode=$error_exit_code --log-file=$tmp_log_file ./42sh < buffer >/dev/null 2>&1
		ret=$?
		if [ $ret -eq $error_exit_code ] ; then
			echo -e "${red}valgrind error, tracing logs at ${inner_log_dir}${eoc}"
			echo -e "${yellow}`cat buffer`${eoc}"
			mkdir -p $inner_log_dir
			cat buffer > ${inner_log_dir}/failed_script
			cat $tmp_log_file > ${inner_log_dir}/valgrind_trace
			rm -f $tmp_log_file
		else
			if [ ! -n "$show_error" ] ; then
				echo -e "${green}no valgrind errors${eoc}"
			fi
			passed=$((passed+1))
			rm -f $tmp_log_file
		fi
}

check_ret_value()
{
	ret1=$1
	ret2=$2
	sh_ret=$((ret1 & 0xFF))
	bash_ret=$((ret2 & 0xFF))

	if [ $sh_ret -eq 130  -o $bash_ret -eq 130 ] ; then
		echo SIGINT received, exit
		kill -s SIGINT $$
	fi

	if [ "$sh_ret" -gt 130 -a "$sh_ret" -lt 200 ] ; then 
		echo -e "${red}SEGFAULT OR SIGNAL RECEIVED"
		echo -e "${sh_ret}${eoc}"
	fi

	if [ -n "$test_returned_values" ] ; then

		if [ "$sh_ret" -ne  "$bash_ret" ] ; then 
			echo -e "${red}BAD RETURNED VALUE"
			echo -e "bash : $bash_ret || 42sh : $sh_ret${eoc}"
			echo -e "${yellow}`cat buffer`${eoc}"
			return 1
		fi
	fi
	return 0
}

launch_test()
{
	if [ ! -n "$1" ] ; then echo "test_launch_pipe : No file given" ; fi
	if [ ! -e "$1" ] ; then echo "test_launch_pipe : can't find $1" ;  return ; fi

	diff_tried=$((diff_tried+1))
	touch res1.bash res2.bash res1.42sh res2.42sh
	if [ -n "$controlled_env" ] ; then
		cat "$1" | env -i PATH=$PATH TERM=$TERM PWD="`pwd`" bash 1>res1.bash 2>res2.bash
		bash_ret=$?
		cat "$1" | env -i PATH=$PATH TERM=$TERM PWD="`pwd`" ./${exec} 1>res1.42sh 2>res2.42sh
		sh_ret=$?
	else
		cat "$1" | bash 1>res1.bash 2>res2.bash
		bash_ret=$?
		cat "$1" | ./${exec} 1>res1.42sh 2>res2.42sh
		sh_ret=$?
	fi

	check_ret_value sh_ret bash_ret
	continue=$?

# echo "continue (stdout): $continue"
	if [ 0 -eq "$continue" ] ; then
		diff_files res1.42sh res1.bash
		continue=$?
	fi
# echo "continue (stderr): $continue"
	if [ 0 -eq "$continue" ] && [ -n "${test_stderr}" ] ; then
		diff_files res2.42sh res2.bash
		continue=$?
	fi
# echo "continue (ok): $continue"
	if [ 0 -eq "$continue" ] ; then
		echo_ok
	fi

# echo "continue (valgrind): $continue"
	if [ -n "$valgrind" ] ; then
		valgrind_test
	fi

	rm -f res1.bash res1.42sh
	rm -f res2.bash res2.42sh
	return $continue
}
