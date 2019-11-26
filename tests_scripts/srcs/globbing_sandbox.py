import os

min_char = 33
max_char = 126

max_subdir = 3

max_len = 10

def touch(file):
	open(file, 'a').close()


try :
	os.mkdir("./sandbox")
except :
	pass
os.chdir("./sandbox")

for char in range(min_char, max_char + 1, 1):
	for len in range(1, max_len):
		if (char % 2 == 0):
			try :
				path = chr(char) * len
				os.mkdir(path)
				for subdir in range (1, max_subdir):
					path = path + "/" + chr(char) * len
					os.mkdir(path)
					open(path + "/" + chr(char - 1), 'a').close()
					os.symlink("..", path + "/" + "link")
			except :
				pass
		else :
			try :
				open(chr(char) * len, 'a').close()
			except :
				pass
		touch("." + len * str(char))
	#try : os.symlink(chr(char), "link_" + str(char))
	#except : pass


touch("filefilefile")
touch("ababab")
touch("abcabcabc")
touch("ABABABAB")
touch("ABCABCABC")
touch(".ababab")
touch(".abcabcabc")
touch(".o")
