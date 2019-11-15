import sys

class Symbol:

	def __init__(self, folder_path, name, first_prod):
		self.folder_path = folder_path
		self.name = name
		self.prods = []
		self.prods.append(first_prod)

	def __repr__(self):
		return "name : "+ self.name + "\n" +\
				"productions: " + repr(self.prods)

	@staticmethod	
	def writeHeader(fd, name):
		fd.write("/* ************************************************************************** */\n")
		fd.write("/*                                                                            */\n")
		fd.write("/*                                                        :::      ::::::::   */\n")
		fd.write("/*   "+ name)
		for i in range(51 - len(name)):
			fd.write(" ")
		fd.write(":+:      :+:    :+:   */\n")
		fd.write("/*                                                    +:+ +:+         +:+     */\n")
		fd.write("/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */\n")
		fd.write("/*                                                +#+#+#+#+#+   +#+           */\n")
		fd.write("/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */\n")
		fd.write("/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */\n")
		fd.write("/*                                                                            */\n")
		fd.write("/* ************************************************************************** */\n\n")

        def generateCodeSymbol(self):
		fd = open(self.folder_path + "/sh_ar_prod_" + self.name + ".c", "w")
		Symbol.writeHeader(fd, self.name + ".c")
		fd.write("#include \"sh_21.h\"")
		fd.write("\n")
		fd.write("\n")
		fd.write("int\t\tsh_ar_init_prod_" + self.name + "(t_cfg *cfg, t_symbol *symbol)\n")
		fd.write("{\n")
		for prod in self.prods:
                        print prod
			if prod[0] == "":
				prod = []
				fd.write("\tif (sh_add_prod(symbol, cfg, " + str(len(prod)))
			else:
				fd.write("\tif (sh_add_prod(symbol, cfg, " + str(len(prod)) + ",")
			for i in range(len(prod)):
				if i != len(prod) - 1:
					fd.write("\n\t\t" + prod[i] + ",")
				else:
					fd.write("\n\t\t"+ prod[i])
			##list all
			fd.write("))\n")
			fd.write("\t\treturn (1);\n")
		fd.write("\treturn (0);\n")
		fd.write("}\n")
		fd.close()

class CodeGenerator:
	
	#folder_path = "srcs/productions"
	folder_path = "srcs/arithmetic/productions"
	
	translations = {
		"&&" : "LEX_TOK_AR_AND",
		"||" : "LEX_TOK_AR_OR",
		"<" : "LEX_TOK_AR_LESS",
		">" : "LEX_TOK_AR_GREAT",
		"+" : "LEX_TOK_AR_PLUS",
		"-" : "LEX_TOK_AR_MINUS",
		"*" : "LEX_TOK_AR_MULTIPLY",
		"/" : "LEX_TOK_AR_DIVIDE",
		"%" : "LEX_TOK_AR_MODULO",
		"<=" : "LEX_TOK_AR_LESSEQ",
		">=" : "LEX_TOK_AR_GREATEQ",
		"==" : "LEX_TOK_AR_EQUAL",
		"!=" : "LEX_TOK_AR_NOT_EQUAL",
		"EPS" : "",
	}

	def __init__(self, path, fd):
		self.path = path
		self.fd = fd

	@staticmethod	
	def getTranslatedStr(str):
                print str
		try:
			return CodeGenerator.translations[str];
		except:
                        if str[0] == str[0].upper():
                                return "LEX_TOK_AR_" + str.upper()
                        else:
                                return str.upper() + "_AR"

	@classmethod
	def generateCode(self):
		grammar_file = open("srcs/grammar_2.c", "w")
		#header_file = open("includes/21_sh_2.h", "w")

		print("Processing code generation for grammar '%s'" % path)
		for line in fd:
			split = line.rstrip().split(" ")
			split = filter(None, split)
			print(split)
			for i, word in enumerate(split):
				if i > 0 and word != ":":
					split[i] = CodeGenerator.getTranslatedStr(word)
			if len(split) > 2 and split[1] == ":":
				currentSymbol = \
				Symbol(CodeGenerator.folder_path, split[0], split[2:])
			elif len(split) != 1:
				currentSymbol.prods.append(split[1:])
			elif len(split) == 1 and split[0] == ';':
				currentSymbol.generateCodeSymbol()

				grammar_file.write("{\"" + CodeGenerator.getTranslatedStr(currentSymbol.name)\
				 +"\", 0, 1, &sh_ar_init_prod_"+ currentSymbol.name + ", &sh_traverse_default, NULL},\n")

if len(sys.argv) >= 2:
	path = sys.argv[1]
else:
	sys.exit("you shall add a path of your grammar")
try:
  	fd = open(path, "r")
except:
	sys.exit("could not open %s" % path)

gen = CodeGenerator(path, fd)
gen.generateCode()
