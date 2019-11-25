#!/usr/bin/python
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    header.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/09 18:08:45 by jmartel           #+#    #+#              #
#    Updated: 2019/06/09 18:08:45 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import re;

format = "^(void|int|char|t_*|unsigned int|long|unsigned long|pid_t)"

ignored_files=["sh_ar_grammar.c", "grammar.c", "vshortcuts.c", "main.c", "tests"]

## Activate or unactivate verbose mode, you can define verbose level between 1 and 3.
verbose = 0

def read_subdir(dir, subdir, files):
    path = os.path.join(dir, subdir)
    for filename in os.listdir(path):
        if (os.path.isdir(os.path.join(path, filename)) == True):
            files = read_subdir(path, os.path.join(path, filename), files)
            continue
        if (os.path.isfile(os.path.join(path, filename)) == False):
            continue
        if (filename in ignored_files):
            continue
        if (filename[-2] != '.' or filename[-1] != 'c'):
            continue
        files.append(os.path.join(subdir, filename))
    return (files)

## read_dir(filename):
##      open every files in dir argument, if file is valid it's extracts prototypes
##      using regex. it stocked in a dictionnary using filenames as keys, every value
##      is a dictionnary with keys "type"  :int, char, void, ...
##      and prototype foo(bar, foo)

def read_dir(dir):
    res = {}
    files = []
    for filename in os.listdir(dir):
        if (filename in ignored_files):
            continue
        if (os.path.isdir(os.path.join(dir, filename)) == True):
            files = read_subdir(dir, filename, files)
            continue
        if (os.path.isfile(os.path.join(dir, filename)) == False):
            continue
        if (filename[-2] != '.' or filename[-1] != 'c'):
            continue
        files.append(filename)
    files.sort()
    for filename in files:
        if (verbose >= 2):
            print(filename)
        fd = open(os.path.join(dir, filename))
        line1 = fd.readline()
        content = []
        while (line1 != ""):
            if (re.search(format, line1) != None):
                prototype = line1.rstrip()
                if (verbose >= 2):
                    print("\t" + prototype)
                while (prototype[-1] != ")"):
                    buffer = fd.readline()
                    buffer = buffer.strip()
                    prototype += " " + buffer
                prototype = prototype.split('\t')
                prototype = [i for i in prototype if (i != "")]
                buffer = {"type" : prototype[0], "name" : prototype[1]}
                content.append(buffer)
            line1 = fd.readline()
        res[filename] = content
    return (res)

## format_dir_datas
##      create from formated string, ready to print in header, read_dir datas
##		Added condition to ignore global variable declaration than could create problems
##			Now any function starting by g_ is ignored, but a message is prompted.
def format_dir_datas(dir_data, tab_offset):
    res = ""
    max_tabs = tab_offset
    if (max_tabs == 0):
        max_tabs = 2
    ## Determine maximum number of tabs to add
    for file in sorted(dir_data.keys()):
        for function in dir_data[file]:
            length = len(function["type"])
            tabs = length // 4
            if (length % 4):
                tabs += 1
            if (tabs > max_tabs):
                max_tabs = tabs

    ## Create every file list of prototypes
    tabs = "\t" * max_tabs
    for file in sorted(dir_data.keys()):
        res += "/*\n** " + file + "\n*/\n"
        for function in dir_data[file]:
            str = function["type"]
            str += "\t" * (max_tabs - (len(function["type"]) // 4))
            if (function["name"][0] == "g" and function["name"][1] == '_'):
                print("Global var declaration found and ignored : " + function["name"])
                continue ;
            str += function["name"]
            str += ";\n"
            if (len(str) + 3 * max_tabs >= 80):
                str = function["type"]
                str += "\t" * (max_tabs - (len(function["type"]) // 4))
                str += function["name"].split("(", 1)[0]
                str += "(\n\t"
                # str += function["name"].split("(", 1)[1].strip()
                buff = function["name"].split("(", 1)[1].strip()
                if (len(buff) + 3 * max_tabs >= 80):
                    for a in buff.split(","):
                        str += a.strip()
                        if (a.strip()[-1] == ')'):
                            str += ";\n"
                        else :
                            str += ",\n\t"
                else :
                    str += buff + ";\n"
            res += str
        res += "\n"
    return res

def create_header(header, datas):
    # Open header in reading mode
    fd_header = open(header, 'r')
    header_content = ""
    line = fd_header.readline()

    # Read file until header delimitation or end of file
    while (line != ""):
        header_content += line
        if (line.strip() == "*" * 80):
            header_content += "*/\n\n"
            break
        line = fd_header.readline()

    # Add header delimitation if do not exists
    if (line == ""):
        header_content += "/*\n"
        header_content += "*" * 80 + "\n"
        header_content += "*/\n\n"

    # Add datas to content
    header_content += datas
    header_content += "#endif\n"
    return header_content


## Write header is now checking that content to write is different of current header
## content to avoid Makefile relinking by modifying files for nothing same things in files
def write_header(header, content):
    fdr = open(header, 'r')
    initial_content = fdr.read()
    fdr.close()
    if (initial_content == content):
    	return
    fd_header = open(header, "w")
    fd_header.write(content)
    fd_header.close()
    print("Updated : " + header)

def automatic_header(dir, header, tab_offset):
    if (verbose):
        print("dir : " + dir + " || file : " + header)
    dir_data = read_dir(dir)
    res = format_dir_datas(dir_data, tab_offset)
    header_content = create_header(header, res)
    # print(header_content)
    write_header(header, header_content)

automatic_header("./srcs/lexer",                        "./includes/sh_lexer.h", 5)
automatic_header("./srcs/expansions",           "./includes/sh_expansions.h", 5)
automatic_header("./srcs/globbing",           "./includes/sh_globbing.h", 7)
automatic_header("./srcs/traverse_tools",       "./includes/sh_traverse_tools.h", 0)
automatic_header("./srcs/vars",                         "./includes/sh_vars.h", 0)
automatic_header("./srcs/arithmetic",                     "./includes/sh_arithmetic.h", 0)
automatic_header("./srcs/traverse",                     "./includes/sh_traverse.h", 5)
automatic_header("./srcs/builtin",                      "./includes/sh_builtin.h", 0)
automatic_header("./srcs/exec",                         "./includes/sh_exec.h", 5)
automatic_header("./srcs/perror",                       "./includes/sh_perror.h", 0)
automatic_header("./srcs/grammar",              "./includes/sh_grammar.h", 6)
automatic_header("./srcs/parser/productions","./includes/sh_productions.h", 0)
automatic_header("./srcs/parser",                       "./includes/sh_parser.h", 5)
automatic_header("./srcs/command_line/shortcuts",                       "./includes/sh_shortcuts.h", 6)
#automatic_header("./srcs/command_line", "./includes/sh_command_line.h", 5)
automatic_header("./srcs/command_line/autocomplete", "./includes/sh_autocompletion.h", 5)
automatic_header("./srcs/common",                       "./includes/sh_21.h", 5)
automatic_header("./srcs/redirection",                       "./includes/sh_redirection.h", 6)
automatic_header("./srcs/job_control",				"./includes/sh_job_control.h", 5)
######automatic_header("./srcs/parser", "./includes/sh_tokens.h", 0)



# automatic_header("./test", "./header.h", 0)
