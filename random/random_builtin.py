#!/usr/local/bin/python3

import	random
import	os
from signal import signal, SIGINT
from sys import exit

def log_cmd():
	os.system("cat buffer >> failed_commands")

def random_token(tokens, lenght=1):
	index = random.randint(0, len(tokens) - 1)
	return (tokens[index])

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

tokens_type_args = [ "-a", "-t", "-t", "--", "cd", "exit", "set", "cp", "ls", "mv", "brew", "brew", "bash" ]
tokens_export_args = [ "-p", "--", "-E", "--Q" , "var", "var=name", "_ok", "_ok=tamer", "2invalidname", "2invalid=ok"]
tokens_unset_args = [ "-p", "--", "-E", "--Q" , "PATH", "TERM", "TERM=", "\"?\"", "2inval", "novar", "PWD", "\"\""]
tokens_set_args = [ "-p", "--", "-E", "--Q" ]

def line_random_type(length):
	line = "hash ls bash ; type "
	for l in range(length):
		line += " " + random_token(tokens_type_args, length) + " "
	return (line)

def line_random_export(length):
	line = "unset _ SHELL SHLVL OLDPWD PWD ; export "
	for l in range(length):
		line += " " + random_token(tokens_export_args, length) + " "
	line += " | sort ; echo $? ; export"
	return (line)

def line_random_unset(length):
	line = "unset _ SHELL SHLVL OLDPWD PWD ; unset "
	for l in range(length):
		line += " " + random_token(tokens_export_args, length) + " "
	line += " | sort ; echo $? ; export"
	return (line)

def cd_tests():
	;

# def line_random_set(length):
# 	line = "unset _ ; export "
# 	for l in range(length):
# 		line += " " + random_token(tokens_export_args, length) + " "
# 	line += " ; echo $? ; export"
# 	return (line)

def launch_test(line_generation_func, max_range=10, repetition=30, filename="buffer", stop_on_error=STOP_ON_ERROR):
	success = 0
	for r in range(1, max_range):
		for rep in range(repetition):
			fdw = open(filename, 'w')
			fdw.write(line_generation_func(r) + "\n")
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
	# launch_test(line_random_type, 20, 10)
	launch_test(line_random_export, 20, 10)
	launch_test(line_random_unset, 20, 10)
