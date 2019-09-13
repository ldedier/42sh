# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    functions.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 15:58:19 by jmartel           #+#    #+#              #
#    Updated: 2019/09/13 00:02:44 by jmartel          ###   ########.fr        #
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
		if [ -n "$verbose" ] ; then
			echo -e "${yellow}`cat ${buffer}`${eoc}"
			echo -e "${cyan}" `cat $1` "${eoc}"
			echo -e "${cyan}" `cat $2` "${eoc}"
		fi
		if [ -n "$logging" ] ; then
			echo -e "KO" >> ${logging_file}
			echo -e `cat ${buffer}` >> ${logging_file}
			echo -e `cat $1` >> ${logging_file}
			echo -e `cat $2` >> ${logging_file}
			echo -e "" >> ${logging_file}
		fi
		return 1
	fi
	return 0
}

valgrind_test()
{
		tried=$((tried+1))
		tmp_log_file="${obj_dir}/tmp_log"
		inner_log_dir="${log_dir}/valgrind/test_${tried}"

		valgrind --leak-check=full --suppressions=$suppressions_file \
			--error-exitcode=$error_exit_code --log-file=$tmp_log_file ./${exec} < ${buffer} >/dev/null 2>&1
		ret=$?
		if [ $ret -eq $error_exit_code ] ; then
			echo -e "${red}valgrind error, tracing logs at ${inner_log_dir}${eoc}"
			echo -e "${yellow}`cat ${buffer}`${eoc}"
			mkdir -p $inner_log_dir
			cat ${buffer} > ${inner_log_dir}/failed_script
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
		if [ -n "$logging" ] ; then
			echo -e `cat ${buffer}` >> ${logging_file}
			echo -e "SEGFAULT OR SIGNAL RECEIVED" >> ${logging_file}
			echo -e "${sh_ret}" >> ${logging_file}
			echo -e "" >> ${logging_file}
		fi
	fi

	if [ -n "$test_returned_values" ] ; then

		if [ "$sh_ret" -ne  "$bash_ret" ] ; then
			if [ -n "$verbose" ] ; then
				echo -e "${red}BAD RETURNED VALUE"
				echo -e "bash : $bash_ret || 42sh : $sh_ret${eoc}"
				echo -e "${yellow}`cat ${buffer}`${eoc}"
			else
				echo -e "${red}KO${eoc}"
			fi

			if [ -n "$logging" ] ; then
				echo -e `cat ${buffer}` >> ${logging_file}
				echo -e "BAD RETURNED VALUE" >> ${logging_file}
				echo -e "bash : $bash_ret || 42sh : $sh_ret" >> ${logging_file}
				echo -e "" >> ${logging_file}
			fi
			return 1
		fi
	fi
	return 0
}

test_launch()
{
	str=""
	for i in "$1" "$2" "$3" "$4" "$5" "$6" "$7" "$8" "$9"
	do
		if [ -n "$i" ] ; then
			str="${str} ${i}"
		fi
	done
	sha="`<<<$str shasum | cut -d\  -f1`"

	res1_42sh="${obj_dir}/res1_42sh_${sha}"
	res2_42sh="${obj_dir}/res2_42sh_${sha}"
	res1_bash="${obj_dir}/res1_bash_${sha}"
	res2_bash="${obj_dir}/res2_bash_${sha}"

	buffer="${obj_dir}/${sha}"
	logging_file="${log_dir}/${sha}"
	rm -f ${logging_file}

	echo "$1" > ${buffer}
	for i in "$2" "$3" "$4" "$5" "$6" "$7" "$8" "$9"
	do
		if [ -n "$i" ] ; then
			echo "${i}" >> ${buffer} ; fi;
	done

	diff_tried=$((diff_tried+1))
	<${buffer} bash 1>${res1_bash} 2>${res2_bash}
	bash_ret=$?
	<${buffer} ./${exec} 1>${res1_42sh} 2>${res2_42sh}
	sh_ret=$?

	check_ret_value sh_ret bash_ret
	continue=$?
# echo "continue (stdout): $continue"
	if [ 0 -eq "$continue" ] ; then
		diff_files ${res1_42sh} ${res1_bash}
		continue=$?
	fi
# echo "continue (stderr): $continue"
	if [ 0 -eq "$continue" ] && [ -n "${test_stderr}" ] ; then
		diff_files ${res2_42sh} ${res2_bash}
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

	rm -f ${buffer}
	rm -f ${res1_bash} ${res1_42sh}
	rm -f ${res2_bash} ${res2_42sh}
}

test_launch_pipe()
{
	if [ ! -n "$1" ] ; then echo "test_launch_pipe : No file given" ; fi
	if [ ! -e "$1" ] ; then echo "test_launch_pipe : can't find $1" ;  return ; fi


	str="`cat ${1}`"
	sha="`<<<$str shasum | cut -d\  -f1`"

	res1_42sh="${obj_dir}/res1_42sh_${sha}"
	res2_42sh="${obj_dir}/res2_42sh_${sha}"
	res1_bash="${obj_dir}/res1_bash_${sha}"
	res2_bash="${obj_dir}/res2_bash_${sha}"

	buffer="${obj_dir}/${sha}"
	logging_file="${log_dir}/${sha}"
	rm -f ${logging_file}

	cp "$1" "${buffer}"

	diff_tried=$((diff_tried+1))
	touch ${res1_bash} ${res2_bash} ${res1_42sh} ${res2_42sh}
	cat "$1" | bash 1>${res1_bash} 2>${res2_bash}
	bash_ret=$?
	cat "$1" | ./${exec} 1>${res1_42sh} 2>${res2_42sh}
	sh_ret=$?

	check_ret_value sh_ret bash_ret
	continue=$?

# echo "continue (stdout): $continue"
	if [ 0 -eq "$continue" ] ; then
		diff_files ${res1_42sh} ${res1_bash}
		continue=$?
	fi
# echo "continue (stderr): $continue"
	if [ 0 -eq "$continue" ] && [ -n "${test_stderr}" ] ; then
		diff_files ${res2_42sh} ${res2_bash}
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

	rm -f ${buffer}
	rm -f ${res1_bash} ${res1_42sh}
	rm -f ${res2_bash} ${res2_42sh}
}
