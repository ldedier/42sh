# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    functions.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 15:58:19 by jmartel           #+#    #+#              #
#    Updated: 2019/11/19 04:15:41 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

clean_and_exit()
{
	rm ${exec}
	rm -rf "${exec}.dSYM"
	del_history
	echo "Cleaned and exit"
	## Show results message
	if [ "$tried" -ne 0 ] ; then
	echo "passed ${passed} valgrind tests out of ${tried}"
	fi
	echo "passed ${diff_passed} diff tests out of ${diff_tried}"
	exit
}

del_history()
{
	find ../ -name ".history" -delete 2>/dev/null 1>/dev/null
}

init_valgrind()
{
	empty_binary="${obj_dir}/test_empty"
	empty_main="${src_dir}/test_empty.c"
	supp_script="${src_dir}/supp_getter.perl"

	if [ -f "$suppressions_file" ] ; then
		echo -e ${green}"Found valgrind configuration file : ${suppressions_file}"${eoc}
		echo -e ${green}"Valgrind initialized"${eoc}
		return
	fi
	if [ ! -f "$empty_binary" ] ; then
			gcc -o $empty_binary $empty_main && echo -e ${green}"Compiled ${empty_binary}"${eoc} || exit
	fi
	valgrind --leak-check=full --show-leak-kinds=all --gen-suppressions=all "./${empty_binary}" 2>&1 | perl ${supp_script} > $suppressions_file
	rm -rf "${empty_binary}.dSYM"
	echo -e ${green}"Created valgrind configuration file : ${suppressions_file}"${eoc}
	echo -e ${green}"Valgrind initialized"${eoc}
}

compile_executable()
{
	mkdir -p "$obj_dir"
	for bin in "fd_write" "fd_read" "signal" "segfault" "write_true" "write_false" "write_arguments"; do
		if [ ! -f "${obj_dir}/$bin" ] ; then
			gcc ${src_dir}/${bin}.c -o "${obj_dir}/${bin}" && echo -e ${green}"Compiled ${bin}"${eoc} || exit
		fi
	done
}

## Difference between launch and launch_show : 
##		Use launch once at begining of the file : launch is used to set the directory where logs would be stored
##		It also show the name of the test routine, as launch_show do.
launch_show()
{
	if [ ! -n "$show_error" ] ; then
		echo -e "${pink}$1 tests :${eoc}" ; fi
}
launch()
{
	if [ ! -n "$show_error" ] ; then
		echo -e "${pink}$1 tests :${eoc}" ; fi
	log_dir="${initial_log_dir}/$1"
	if [ -d "${log_dir}" ] ; then  rm -r "${log_dir}" ; fi
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

create_logging_file()
{
	if [ -f "${logging_file}" ] ; then
		rm -f "${logging_file}"
	elif [ ! -d "`dirname "${logging_file}"`" ] ; then
		mkdir -p "`dirname "${logging_file}"`"
	fi
	touch "${logging_file}"
}

diff_files()
{
	res=`diff $1 $2`
	if [ -n "$res" ] ; then
		echo -e "${red}KO${eoc}"
		echo -en "${yellow}"
		cat "${buffer}"
		echo -en "${eoc}"
		if [ -n "$verbose" ] ; then
			echo -e "${cyan}" `cat $1` "${eoc}"
			echo -e "${cyan}" `cat $2` "${eoc}"
		fi
		if [ -n "$logging" ] ; then
			create_logging_file
			echo -e "Script :" >> "${logging_file}"
			cat "${buffer}" >> "${logging_file}"
			echo -e "" >> "${logging_file}"
			echo -e "KO" >> "${logging_file}"
			echo -e "42sh :" >> "${logging_file}"
			echo -e `cat $1` >> "${logging_file}"
			echo -e "" >> "${logging_file}"
			echo -e "bash :" >> "${logging_file}"
			echo -e `cat $2` >> "${logging_file}"
			echo -e "" >> "${logging_file}"
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
			echo -en "${yellow}"
			cat "${buffer}"
			echo -en "${eoc}"
			mkdir -p $inner_log_dir
			cat ${buffer} > "${inner_log_dir}/failed_script"
			cat $tmp_log_file > "${inner_log_dir}/valgrind_trace"
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

	if [ "$sh_ret" -gt 128 -a "$sh_ret" -lt 200 ] ; then
		echo -e "${red}SEGFAULT OR SIGNAL RECEIVED"
		echo -e "${sh_ret}${eoc}"
		if [ -z "$test_returned_values" ] ; then echo -en "${yellow}" ;  cat "${buffer}" ; echo -en "${eoc}" ; fi
		if [ -n "$logging" ] ; then
			create_logging_file
			echo -e "Script :" >> "${logging_file}"
			echo -e cat "${buffer}" >> "${logging_file}"
			echo -e "" >> "${logging_file}"
			echo -e "SEGFAULT OR SIGNAL RECEIVED" >> "${logging_file}"
			echo -e "${sh_ret}" >> "${logging_file}"
			echo -e "" >> "${logging_file}"
		fi
	fi

	if [ -n "$test_returned_values" ] ; then

		if [ "$sh_ret" -ne  "$bash_ret" ] ; then
			if [ -n "$verbose" ] ; then
				echo -e "${red}BAD RETURNED VALUE"
				echo -e "bash : $bash_ret || 42sh : $sh_ret${eoc}"
				echo -en "${yellow}"
				cat "${buffer}"
				echo -en "${eoc}"
			else
				echo -e "${red}KO${eoc}"
			fi

			if [ -n "$logging" ] ; then
				create_logging_file
				echo -e "Script :" >> "${logging_file}"
				cat "${buffer}" >> "${logging_file}"
				echo -e "" >> "${logging_file}"
				echo -e "BAD RETURNED VALUE" >> "${logging_file}"
				echo -e "bash : $bash_ret || 42sh : $sh_ret" >> "${logging_file}"
				echo -e "" >> "${logging_file}"
			fi
			return 1
		fi
	fi
	return 0
}

test_launch()
{
	res1_42sh="${obj_dir}/res1_42sh_${diff_tried}"
	res2_42sh="${obj_dir}/res2_42sh_${diff_tried}"
	res1_bash="${obj_dir}/res1_bash_${diff_tried}"
	res2_bash="${obj_dir}/res2_bash_${diff_tried}"

	buffer="${obj_dir}/${diff_tried}"
	logging_file="${log_dir}/${diff_tried}"

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
	if [ 0 -eq "$continue" ] && [ -n "${test_stdout}" ] ; then
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

	rm "${res1_42sh}" "${res2_42sh}" "${res1_bash}" "${res2_bash}" "${buffer}"
}

test_launch_pipe()
{
	if [ ! -n "$1" ] ; then echo "test_launch_pipe : No file given" ; fi
	if [ ! -e "$1" ] ; then echo "test_launch_pipe : can't find $1" ;  return ; fi

	res1_42sh="${obj_dir}/res1_42sh_${diff_tried}"
	res2_42sh="${obj_dir}/res2_42sh_${diff_tried}"
	res1_bash="${obj_dir}/res1_bash_${diff_tried}"
	res2_bash="${obj_dir}/res2_bash_${diff_tried}"
	buffer="${obj_dir}/${diff_tried}"
	logging_file="${log_dir}/${diff_tried}"

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

	rm "${res1_42sh}" "${res2_42sh}" "${res1_bash}" "${res2_bash}" "${buffer}"
}
