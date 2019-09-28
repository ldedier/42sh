#!/usr/local/bin/python3

import	random
import	os
from signal import signal, SIGINT
from sys import exit

VALGRIND = True
QUIET = True
TWO = False
RET = True

STOP_ON_ERROR = False
LOG_ERRORS = True

tokens_redir = ["|", "<", ">", "<<", ">>", ">&", ">&-", "<&", "<&-"]
chars_redir = "|<>&-"

tokens_quotes = ["\"", "\'"]

# tokens_cmd = ["ls", "echo", "cat", "pwd", "exit", "true", "false", "unknowncommand", "wc", "cd", "echo", "wc"]
tokens_cmd = ["ls", "echo okalmos speculos", "cat", "cd .. ; pwd", "exit", "true", "false", "unknowncommand", "ls | wc", "cd .. ; pwd", "echo okal", "ls | wc"]

tokens_filename = ["1", "2", "3", "4", "file1", "file2", "file3", "file4", "file5", "file6", "", "", "", "", "", ""]

tokens_and_or_list = ["&&", "||", ";"]


def log_cmd():
	os.system("cat buffer >> failed_commands")

def random_token(tokens, lenght=1):
	index = random.randint(0, len(tokens) - 1)
	return (tokens[index])

def random_cmd(lenght=1):
	return (random_token(tokens_cmd, 1))

def random_env_cmd(lenght=1):
	str = ""
	if (random.randint(1, 3) == 2):
		str = "env "
	str += random_token(tokens_cmd, 1)
	return (str)

def random_add_jump(string):
	index = random.randint(0, len(string) - 1)
	string = string[index:] + "\\\n" + string[:index]
	return (string)

def random_add_quotes(string):
	quote = random_token(tokens_quotes)
	index = random.randint(0, len(string) - 1)
	string = string[index:] + quote + string[:index]
	if (random.randint(0, 10) != 10):
		index = random.randint(0, len(string) - 1)
		string = string[index:] + quote + string[:index]
	return (string)

def line_random_pipe_sequence(lenght, cmd_generation_func=random_cmd):
	line = ""
	for l in range(lenght - 1):
		line += cmd_generation_func()
		line += " | "
	line += cmd_generation_func()
	return (line)

def line_random_redirection(redirect_nb, cmd_generation_func=random_cmd):
	line = cmd_generation_func() + " "
	filenames = []
	for redir in range(redirect_nb):
		buf = random_token(tokens_filename)
		if (buf != ""):
			filenames.append(buf)
		line += buf + " "
		line += random_token(tokens_redir) + " "
		buf = random_token(tokens_filename)
		filenames.append(buf)
		line += buf + " "
	for file in filenames:
		if (file != ""):
			line += " ; cat " + file
	line += "; rm -f "
	for file in filenames:
		if (file != ""):
			line += file + " "
	return (line)

def line_random_pipe_and_redir(lenght, cmd_generation_func=line_random_redirection):
	line = ""
	for l in range(lenght - 1):
		line += cmd_generation_func(5)
		line += " | "
	line += cmd_generation_func(5)
	return (line)

def line_random_and_or_list(lenght, cmd_generation_func=random_cmd):
	line = ""
	for l in range(lenght - 1):
		line += cmd_generation_func(1)
		line += " " + random_token(tokens_and_or_list) + " "
	line += cmd_generation_func(1)
	return (line)

def line_random_jump(lenght, cmd_generation_func=random_cmd):
	line = cmd_generation_func(lenght)
	jumps = lenght + 1
	for j in range(jumps):
		line = random_add_jump(line)
	return (line)

def line_random_quotes(lenght, cmd_generation_func=random_cmd):
	line = cmd_generation_func(lenght)
	quotes = lenght + 1
	for q in range(quotes):
		line = random_add_quotes(line)
	return (line)

# token_param_expansion_format = [":?", "?", ":+", "+", ":-", "-", ":=", "="]
token_param_expansion_format = ["#", "##", "%", "%%"]
token_param_expansion_param = ["param", "noparam", "", " ", "~"]
token_param_expansion_word = ["word", "noword", "$word", "\"$word\"", "\"word\"", "${word}", "${noword}", "${$word}", "", " ", "\$word", "\'word\'", "~"]

param_expansion_ignore=["-", ""]

def check_ignored(expansion):
	for ignored in param_expansion_ignore:
		if ( expansion == ignored):
			return (1)
	return (0)

def parameter_expansion(lenght, cmd_generation_func=random_cmd):
	print("launch random_param_exp")
	for format in token_param_expansion_format:
		for param in token_param_expansion_param:
			for word in token_param_expansion_word:
				line = "test_launch \'param=PARAMETER word=WORD\' "
				line += "\'${" + param + format + word + "}"
				line += " ; echo $? \'"
				if (check_ignored(param + format + word) == 0):
					print(line)

def launch_cmd(valgrind=False, quiet=False, two=False, ret=False):
	cmd = "./tester.sh "
	if (quiet):
		cmd += " -e "
	if (two):
		cmd += " -2 "
	if (ret):
		cmd += " -r "
	if (valgrind):
		cmd += " -v "
	return (os.system(cmd))

def launch_test(line_generation_func, max_range=10, repetition=30, cmd_generation_func=random_cmd, filename="buffer", stop_on_error=STOP_ON_ERROR):
	success = 0
	for r in range(1, max_range):
		for rep in range(repetition):
			fdw = open(filename, 'w')
			fdw.write(line_generation_func(r, cmd_generation_func) + "\n")
			fdw.close()
			ret = launch_cmd(valgrind=VALGRIND, quiet=QUIET, two=TWO, ret=RET)
			if (ret & 0xff == SIGINT):
				handler("", "")
			if (ret == 0):
				success += 1
			else :
				if (LOG_ERRORS):
					log_cmd()
				if (STOP_ON_ERROR):
					print(str(success) + " tests passed")
					return (success)
	print(str(success) + " tests passed")

def handler(signal_received, frame):
    # Handle any cleanup here
    print('STOP PROCESS')
    exit(0)

def main():
	signal(SIGINT, handler)
	os.system("./init.sh")
	launch_test(line_random_parameter_expansion, 10, 30)
	launch_test(line_random_pipe_sequence, 10, 30)
	launch_test(line_random_redirection, 10, 30)
	launch_test(line_random_pipe_and_redir, 5, 40, line_random_redirection)
	launch_test(line_random_and_or_list, 20, 10)
	launch_test(line_random_and_or_list, 20, 10, random_env_cmd)
	launch_test(line_random_and_or_list, 20, 10, line_random_pipe_sequence)

	launch_test(line_random_jump, 10, 50)
	launch_test(line_random_jump, 10, 50, line_random_pipe_sequence)
	launch_test(line_random_jump, 10, 50, line_random_and_or_list)

	launch_test(line_random_quotes, 10, 50)
	launch_test(line_random_quotes, 10, 50, line_random_pipe_sequence)
	launch_test(line_random_quotes, 10, 50, line_random_and_or_list)
	launch_test(line_random_jump, 10, 50, line_random_redirection)
# main()

parameter_expansion(0)