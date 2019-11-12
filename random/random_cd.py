import	os
import	random

cd_tokens = [".", "/", "..", "tmp", "./", "/.", "/../", "/./", "/..", "../"]

def random_token(tokens):
	index = random.randint(0, len(tokens) - 1)
	return (tokens[index])

def random_str(lenght):
	str = ""
	for i in range(lenght):
		str += random_token(cd_tokens) + '/'
	return (str)

def clean_table(tab):
	count = 0
	for i in range(len(tab)):
		for j in reversed(range(len(tab) - i)):
			if (i != j and tab[i] == tab[j]):
				del tab[j]
				count += 1
	print("deleted : " + str(count))

def all_patterns(filename="all_test_builtin_cd.sh", lenght=10, repetition=2000):
	tab = []
	for l in range(lenght):
		for a in range(repetition):
			str = 'test_launch \'cd '
			str += random_str(l)
			str += '\' \'echo $?\' \'pwd\' '
			tab.append(str)
			print(str)

	clean_table(tab)

	fdw = open(filename, 'w')
	for str in tab:
		fdw.write(str + '\n')
	fdw.close()

all_patterns()
