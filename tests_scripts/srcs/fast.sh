# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    fast.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/24 22:12:49 by jmartel           #+#    #+#              #
#    Updated: 2019/09/24 22:47:43 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


## Need to move this deifinition later
separator="%%%%%##################################################%%%%%"

get_test_nbr()
{
	if [ ${#test_nbr} -eq 1 ] ;  then echo "000${test_nbr}" ; fi
	if [ ${#test_nbr} -eq 2 ] ;  then echo "00${test_nbr}" ; fi
	if [ ${#test_nbr} -eq 3 ] ;  then echo "0${test_nbr}" ; fi
	if [ ${#test_nbr} -eq 4 ] ;  then echo "${test_nbr}" ; fi
}

test_launch()
{
	## Definition des variables locales
	dir=${obj_dir}/${current_path}/test_`get_test_nbr`
	script=${dir}/script
	## Creation des dossier / fichiers
	mkdir -p ${dir}
	touch ${script}

	## Ecriture du fichier script origianl
	echo "$1" > ${script}
	for i in "$2" "$3" "$4" "$5" "$6" "$7" "$8" "$9"
	do
		if [ -n "$i" ] ; then
			echo "${i}" >> ${script} ; fi;
	done

	## Ajout du script dans le buffer d'execution
	cat ${script} >> ${buffer}
	echo 'echo $?' >> ${buffer}
	echo "${separator}" >> ${buffer}
	echo "" >> ${buffer}

	## Mise a jour du compteur
	test_nbr=$((test_nbr+1))
}

test_launch_pipe()
{
	if [ ! -n "$1" ] ; then echo "test_launch_pipe : No file given" ; fi
	if [ ! -e "$1" ] ; then echo "test_launch_pipe : can't find $1" ;  return ; fi

	## Definition des variables locales
	dir=${obj_dir}/${current_path}/test_`get_test_nbr`
	script=${dir}/script
	## Creation des dossier / fichiers
	mkdir -p ${dir}
	cp "$1" ${script}
	## Ajout du script dans le buffer d'execution
	cat ${script} >> ${buffer}
	echo 'echo $?' >> ${buffer}
	echo "${separator}" >> ${buffer}
	echo "" >> ${buffer}

	## Mise a jour du compteur
	test_nbr=$((test_nbr+1))
}

launch()
{
	return
}

finish()
{
	return
}
