#!/usr/bin/python
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    norm.py                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/09 18:08:45 by jmartel           #+#    #+#              #
#    Updated: 2019/06/09 18:08:45 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import re
import sys

## If True scritp check uncommented functions
option_check_comments=False

if (len(sys.argv) > 1):
	for arg in sys.argv:
		if (arg == "-c"):
			option_check_comments=True

## Regex used to detect functions prototype
format = "^(static|void|int|char|t_*)"

def recursive_list_dir(dirpath, filepaths):
	for filename in os.listdir(dirpath):
		filepath = os.path.join(dirpath, filename)
		if (os.path.isdir(filepath) == True):
			recursive_list_dir(filepath, filepaths)
		elif (os.path.isfile(filepath) == True):
			if (filename[-1] == 'c' and filename[-2] == '.'):
				filepaths.append(filepath)
	return (filepaths)

def get_file_names():
	dirname = []
	if (len(sys.argv) > 1):
		for i in range(1, len(sys.argv)):
			if (sys.argv[i][0] == '-'):
				continue
			dirname.append(sys.argv[i])
	else :
		dirname = ["."]
	filepaths = []
	for dir in dirname:
		if (os.path.isdir(dir)):
			recursive_list_dir(dir, filepaths)
		else :
			filepaths.append(dir)
	return (filepaths)

def read_file(filepath):
	content = []
	if (os.path.isfile(filepath) == False):
		return (content)
	fdr = open(filepath, 'r')
	line = fdr.readline()
	while (line != ""):
		content.append(line)
		line = fdr.readline()
	fdr.close()
	return (content)

def norminette_line_len(line):
	line_len = 0
	tab_len = 4
	for i in range(len(line)):
		if (line[i] == '\t'):
			line_len += tab_len
			tab_len = 4
		else :
			if (tab_len > 0):
				tab_len -= 1
			else :
				tab_len = 3
			line_len += 1
	return line_len

def norminette_functions(content, i, messages):
	prototype = content[i].rstrip()
	prototype = prototype.split('\t')
	prototype = [k for k in prototype if (k != "")]
	if (len(prototype) < 2):
		return
	funcname = prototype[1]
	funcname = funcname.split('(')[0]
	funclen = 0
	if (option_check_comments):
		if (content[i - 1] != "*/\n" and content[i - 2] != "*/\n"):
			messages.append("{:-3d}: {:s}: not commented function".format(i - 1, funcname))
	j = i + 1
	while (j < len(content)):
		if (content[j] == '{\n'):
			funclen = 0
		elif (content[j] == '}\n'):
			break
		elif (funclen >= 0):
			funclen += 1
		# if (content[int(j)].find('//') != -1):
		# 	messages.append("{:-3d}: c++ comment".format(j))
		first_char = content[j].lstrip("\t")[0]
		if (first_char == ' '):
			messages.append("{:d}: bad indentation".format(j + 1))
		j += 1

	if (j == len(content) and content[0] != '}'):
		messages.append("Bad format for function : {:s}".format(funcname))
	elif (funclen > 25):
		messages.append("{:-3d}: {:s}: {:d} lines".format(j - funclen - 1, funcname, funclen))


def norminette(filename, content):
	funclen = -1
	funcname = ""
	funcnumber = 0
	errors = 0
	messages = []
	for i in range(len(content)):
		## Multiple empty lines
		if (content[i] == content[i - 1] == "\n"):
			messages.append("{:-3d}: multiple empty lines".format(i + 1 ))
		## Line len
		line_len = norminette_line_len(content[i])
		if (line_len > 81):
			messages.append("{:-3d}: line is too long ({:d})".format(i + 1, line_len - 1)) ## -1 ??
		## Functions len and format
		if (re.search(format, content[i]) != None):
			funcnumber += 1
			norminette_functions(content, i, messages)

	if (funcnumber > 5):
		messages.append("{:d} functions in file".format(funcnumber))
	if (len(messages) > 0):
		print(filename)
		for msg in messages:
			print("\t" + msg)


def main():
	filepaths = get_file_names()
	for filepath in filepaths:
		if (filepath[-1] != 'c' or filepath[-2] != '.'):
			continue
		content = read_file(filepath)
		if (not content):
			continue
		norminette(filepath, content)

main()
