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
	fdw = open(filename, 'w')
	for str in tab:
		fdw.write(str + '\n')
	fdw.close()

# all_patterns()

tokens = [ "&&", "||", "+", "-", "/", "%", "*", "<", ">", "<=", ">=", "==", "!=" , "++", "--" , "var", "a", "b","12", "-7", "-8569", "42", "$VARIABLE", "${a}", "novar", "68", "-85", "-127", "12", "69","-12","-2147483648", "-2147483649", "2147483647","2147483648"]

def full_random_str(lenght):
	str = ""
	for i in range(lenght):
		str += random_token(tokens)
	return str

def clean_table(tab):
	count = 0
	for i in range(len(tab)):
		for j in reversed(range(len(tab) - i)):
			if (i != j and tab[i] == tab[j]):
				del tab[j]
				count += 1
	print("deleted : " + str(count))

def all_patterns_full_random(filename="../tests_scripts/tests/random_expansions_artithmetic.sh", lenght=100, repetition=50):
	tab = []
	for l in range(1 , lenght):
		for a in range(repetition):
			tab.append(full_random_str(l))
	clean_table(tab)
	for key in range(len(tab)):
		str = 'test_launch '
		str += '\'a=12 b=-54 var=100000 ;'
		str += 'echo $(('
		str += tab[key]
		str += ')) ; echo $?\' '
		str += '\'echo $?\''
		tab[key] = str
	fdw = open(filename, 'w')
	for str in tab:
		fdw.write(str + '\n')
	fdw.close()

all_patterns_full_random()
