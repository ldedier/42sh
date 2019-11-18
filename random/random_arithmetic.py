import	os
import	random

tokens = [ "&&", "||", "+", "-", "/", "%", "*", "<", ">", "<=", ">=", "==", "!="] ##, "++", "--" ]

def random_nbr(lenght):
	nbr = ""
	for i in range(lenght):
		nbr += str(random.randint(0, 9))
	return (nbr)

def random_token(tokens):
	index = random.randint(0, len(tokens) - 1)
	return (tokens[index])

def random_str(lenght, op_nbr):
	str = random_nbr(lenght)
	for i in range(op_nbr):
		index = random.randint(0, len(str) - 1)
		t_index = random.randint(0, len(tokens) - 1)
		str = str[:index] + tokens[t_index] + str[index:]
	return (str)

def all_patterns(filename="../tests_scripts/tests/all_test_expansions_artithmetic.sh", lenght=100, repetition=20):
	tab = []
	for l in range(1 , lenght):
		for a in range(repetition):
			str = 'test_launch \'echo $(('
			str += random_str(l, l // 3)
			str += '))\' \'echo $?\''
			tab.append(str)
			# print(str)
	# clean_table(tab)

	fdw = open(filename, 'w')
	for str in tab:
		fdw.write(str + '\n')
	fdw.close()

all_patterns()
