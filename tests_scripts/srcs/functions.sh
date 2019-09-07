# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    functions.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 15:58:19 by jmartel           #+#    #+#              #
#    Updated: 2019/09/06 14:32:57 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

clean_and_exit()
{
	rm ${exec}
	rm -rf "${exec}.dSYM"
	del_historic
	echo "Cleaned and exit"
	exit
}

del_historic()
{
	find ../ -name ".historic" -delete 2>/dev/null 1>/dev/null
}

init_valgrind()
{
	empty_binary="${obj_dir}/empty_binary"
	empty_main="${src_dir}/test_empty.c"
	supp_script="${src_dir}/supp_getter.perl"

	if [ -f "$suppressions_file" ] ; then
		echo -e ${green}"Found valgrind configuration file : ${supsuppressions_filep_file}"${eoc}
		echo -e ${green}"Valgrind initialized"${eoc}
		return
	fi
	if [ ! -f "$empty_binary" ] ; then
			gcc -o $empty_binary $empty_main && echo -e ${green}"Compiled : ${empty_binary}"${eoc} || exit
	fi
	valgrind --leak-check=full --gen-suppressions=all "./${empty_binary}" 2>&1 | perl ${supp_script} > $suppressions_file
	rm -rf "${empty_binary}.dSYM"
	echo -e ${green}"Valgrind initialized"${eoc}
}

compile_executable()
{
	mkdir -p "$obj_dir"
	for bin in "fd_write" "fd_read" "signal" "segfault" "write_true" "write_false"; do
		if [ ! -f "${obj_dir}/$bin" ] ; then
			gcc ${src_dir}/${bin}.c -o "${obj_dir}/${bin}" && echo -e ${green}"Compiled ${bin}"${eoc} || exit
		fi
	done
}

launch()
{
	if [ ! -n "$show_error" ] ; then
		echo -e "${pink}$1 tests :${eoc}"
	fi
}

finish()
{
	if [ ! -n "$show_error" ] ; then
		echo ""
	fi
}

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
		echo -e "${yellow}`cat ${obj_dir}/buffer`${eoc}"
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
		tmp_log_file="${obj_dir}/tmp_log"
		inner_log_dir="${log_dir}/test_${tried}"

		valgrind --leak-check=full --suppressions=$suppressions_file \
			--error-exitcode=$error_exit_code --log-file=$tmp_log_file ./${exec} < ${obj_dir}/buffer >/dev/null 2>&1
		ret=$?
		if [ $ret -eq $error_exit_code ] ; then
			echo -e "${red}valgrind error, tracing logs at ${inner_log_dir}${eoc}"
			echo -e "${yellow}`cat ${obj_dir}/buffer`${eoc}"
			mkdir -p $inner_log_dir
			cat ${obj_dir}/buffer > ${inner_log_dir}/failed_script
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

	if [ "$sh_ret" -gt 130 -a "$sh_ret" -lt 200 ] ; then 
		echo -e "${red}SEGFAULT OR SIGNAL RECEIVED"
		echo -e "${sh_ret}${eoc}"
	fi

	if [ -n "$test_returned_values" ] ; then

		if [ "$sh_ret" -ne  "$bash_ret" ] ; then 
			echo -e "${red}BAD RETURNED VALUE"
			echo -e "bash : $bash_ret || 42sh : $sh_ret${eoc}"
			echo -e "${yellow}`cat ${obj_dir}/buffer`${eoc}"
			return 1
		fi
	fi
	return 0
}

test_launch()
{
	echo "$1" > ${obj_dir}/buffer
	for i in "$2" "$3" "$4" "$5" "$6" "$7" "$8" "$9"
	do
		if [ -n "$i" ] ; then 
			echo "${i}" >> ${obj_dir}/buffer ; fi;
	done
	diff_tried=$((diff_tried+1))
	touch ${obj_dir}/res1.bash ${obj_dir}/res2.bash ${obj_dir}/res1.42sh ${obj_dir}/res2.42sh
	<${obj_dir}/buffer bash 1>${obj_dir}/res1.bash 2>${obj_dir}/res2.bash
	bash_ret=$?
	<${obj_dir}/buffer ./${exec} 1>${obj_dir}/res1.42sh 2>${obj_dir}/res2.42sh
	sh_ret=$?

	check_ret_value sh_ret bash_ret
	continue=$?
# echo "continue (stdout): $continue"
	if [ 0 -eq "$continue" ] ; then
		diff_files ${obj_dir}/res1.42sh ${obj_dir}/res1.bash
		continue=$?
	fi
# echo "continue (stderr): $continue"
	if [ 0 -eq "$continue" ] && [ -n "${test_stderr}" ] ; then
		diff_files ${obj_dir}/res2.42sh ${obj_dir}/res2.bash
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

	rm -f ${obj_dir}/buffer
	rm -f ${obj_dir}/res1.bash ${obj_dir}/res1.42sh
	rm -f ${obj_dir}/res2.bash ${obj_dir}/res2.42sh
}

test_launch_pipe()
{
	if [ ! -n "$1" ] ; then echo "test_launch_pipe : No file given" ; fi
	if [ ! -e "$1" ] ; then echo "test_launch_pipe : can't find $1" ;  return ; fi

	cp "$1" "${obj_dir}/buffer"

	diff_tried=$((diff_tried+1))
	touch ${obj_dir}/res1.bash ${obj_dir}/res2.bash ${obj_dir}/res1.42sh ${obj_dir}/res2.42sh
	cat "$1" | bash 1>${obj_dir}/res1.bash 2>${obj_dir}/res2.bash
	bash_ret=$?
	cat "$1" | ./${exec} 1>${obj_dir}/res1.42sh 2>${obj_dir}/res2.42sh
	sh_ret=$?

	check_ret_value sh_ret bash_ret
	continue=$?

# echo "continue (stdout): $continue"
	if [ 0 -eq "$continue" ] ; then
		diff_files ${obj_dir}/res1.42sh ${obj_dir}/res1.bash
		continue=$?
	fi
# echo "continue (stderr): $continue"
	if [ 0 -eq "$continue" ] && [ -n "${test_stderr}" ] ; then
		diff_files ${obj_dir}/res2.42sh ${obj_dir}/res2.bash
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

	rm -f ${obj_dir}/buffer
	rm -f ${obj_dir}/res1.bash ${obj_dir}/res1.42sh
	rm -f ${obj_dir}/res2.bash ${obj_dir}/res2.42sh
}
