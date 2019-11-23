import os
import	random
import shutil

filename_chars = "ABCDEFHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\"\\\'?$%&*"

def random_filename(lenght):
	name = ""
	for i in range(lenght):
		index = random.randint(0, len(filename_chars))
		name += filename_chars[index]
	return (name)

def create_random_files():
	number_of_file = 100
	max_lenght = 20
	for i in range(1, number_of_file):
		for j in range(1, max_lenght):
			try : open(random_filename(j), 'a').close()
			except : pass

def create_random_directories():
	number_of_file = 100
	max_lenght = 20
	max_subdir = 5
	subfiles = 7
	for i in range(1, number_of_file):
		for j in range(1, max_lenght):
			pwd = os.getcwd()
			for sub in range (max_subdir):
				try :
					dirname = random_filename(j)
					os.makedirs(dirname)
					os.chdir(dirname)
					for files in range(subfiles):
						open(random_filename(files), 'a').close()
				except : pass
			os.chdir(pwd)

def create_sandbox():
	min_char = 33
	max_char = 126
	max_subdir = 3
	max_len = 10

	if (os.path.exists("sandbox")):
		return
		shutil.rmtree("./sandbox")
	os.makedirs("./sandbox")
	os.chdir("./sandbox")

	for char in range(min_char, max_char + 1, 1):
		for len in range(1, max_len):
			if (char % 2 == 0):
				try :
					path = chr(char) * len
					os.makedirs(path)
					for subdir in range (1, max_subdir):
						path = path + "/" + chr(char) * len
						os.makedirs(path)
						open(path + "/" + chr(char - 1), 'a').close()
						os.symlink("..", path + "/" + "link")
				except :
					pass
			else :
				try :
					open(chr(char) * len, 'a').close()
				except :
					pass
		try : os.symlink(chr(char), "link_" + str(char))
		except : pass
	create_random_files()
	create_random_directories()

# brace_patterns = ["[]", "[a-A]", "[!a-A]", "[a-bc]", "abc", "[!!asd]", ""]
# stars_patterns = ["*", "*/", "*/*", "*/*/"]
# str_patterns = ["", "a", "b", "c", "d", "A", "B", "X", '"', "'", "\\", "\\\\", '""', '""', "AAA", "BBB"]
# quest_patterns = ["?", "??", "???", "????", "\?\???", "\?", "'??'", '"??"']

brace_patterns = ["[a-A]", "[!a-A]", "[a-bc]", "", "/"]
stars_patterns = ["*", "*/", "*/*", "*/*/", "/"]
str_patterns = ["", "a", "B", '"', "\\", '""', '""', "AA", "/"]
quest_patterns = ["?", "??", "\?", "/"]

patterns = brace_patterns + stars_patterns + str_patterns + quest_patterns

def random_token(tokens, lenght=1):
	index = random.randint(0, len(tokens) - 1)
	return (tokens[index])

def all_patterns(filename="all_test_globbing.sh"):
	lenght = len(patterns)
	fdw = open(filename, 'w')
	for a in range(lenght):
		for b in range(lenght):
			for c in range(lenght):
				str = 'test_launch \'echo '
				str += patterns[a] + patterns[b] + patterns[c]
				str += '\''
				# print(str)
				fdw.write(str + '\n')
	fdw.close()

create_sandbox()
all_patterns()
