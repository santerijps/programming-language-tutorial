CC = tcc -o bin/pltc.exe
LINK = src/lex.c src/stream.c src/token.c src/validators.c

build: bin
	$(CC) src/pltc.c $(LINK)

init:
	mkdir bin
