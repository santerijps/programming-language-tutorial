TCC = tcc -o bin/pltc.exe
GCC = gcc -o bin/pltc.gcc.exe
LINK = src/lex.c src/stream.c src/token.c src/validators.c

tcc: bin
	$(TCC) src/pltc.c $(LINK)

gcc: bin
	$(GCC) src/pltc.c $(LINK)

bin:
	mkdir bin
