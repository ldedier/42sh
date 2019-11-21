import os
import	random

format = ["%", "%%", "#", "##"]
param_value = ["param=Okalm", "param='Okalmos     Speculos'", "ls", "param=", "param='#####'", "param=", 'param=/one/two/three', "param=////////", "param=\["]
word_value = ["word=", "", "word='[a-Z]'", "word=[a-z]", "word=Okalm"]
word_patterns = ["word", "?", "??", "?*?", "[A-Z][!a-z]", "[A-Z][!a-z]?", "[A-Z][!a-z]?*", "", "*/", "/*", "?/", "?/", "one?", "th???", "*/*", "[\[]"]

def random_token(tokens, lenght=1):
	index = random.randint(0, len(tokens) - 1)
	return (tokens[index])

def all_patterns(filename="all_test_substring_removal.sh"):
	fdw = open(filename, 'w')
	for i_format in range(len(format)):
		for i_param in range(len(param_value)):
			for i_word in range(len(word_value)):
				for i_pattern in range(len(word_patterns)):
					str = "test_launch '"
					str += param_value[i_param] + "' "
					str += " '" + word_patterns[i_pattern] + "' "
					str += "'echo ${param" + format[i_format]
					str += word_value[i_word] + "}'"
					# print(str)
					fdw.write(str + '\n')
	fdw.close()

all_patterns()
