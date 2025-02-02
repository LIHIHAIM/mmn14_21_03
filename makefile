CC = gcc
CFLAGS = -Wall -pedantic -ansi

main: main.o compiler.o ineterface.h buildWord.o dataHandeling.o files.o instructionHandeling.o label.o line.o statmentType.o symbolTable.o util.o
	$(CC) -g $(CFLAGS) main.o compiler.o buildWord.o dataHandeling.o files.o instructionHandeling.o label.o line.o statmentType.o symbolTable.o util.o -o main
main.o: main.c ineterface.h
	$(CC) -c $(CFLAGS) main.c -o main.o
compiler.o: compiler.c ineterface.h files.h line.h util.h label.h instructionHandeling.h dataHandeling.h symbolTable.h statmentType.h
	$(CC) -c $(CFLAGS) compiler.c -o compiler.o
buildWord.o: buildWord.c buildWord.h
	$(CC) -c $(CFLAGS) buildWord.c -o buildWord.o
dataHandeling.o: dataHandeling.c util.h word.h label.h privateDataFuncs.h
	$(CC) -c $(CFLAGS) dataHandeling.c -o dataHandeling.o -lm
files.o: files.c files.h util.h privateDataFuncs.h privateInstFuncs.h privateSymTabFuncs.h
	$(CC) -c $(CFLAGS) files.c -o files.o
instructionHandeling.o: instructionHandeling.h label.h util.h word.h buildWord.h privateInstFuncs.h privateSymTabFuncs.h
	$(CC) -c $(CFLAGS) instructionHandeling.c -o instructionHandeling.o
label.o: label.c label.h
	$(CC) -c $(CFLAGS) label.c -o label.o
line.o: line.c line.h util.h label.h
	$(CC) -c $(CFLAGS) line.c -o line.o
statmentType.o: statmentType.c bool.h statmentType.h
	$(CC) -c $(CFLAGS) statmentType.c -o statmentType.o
symbolTable.o: symbolTable.c symbolTable.h util.h label.h privateSymTabFuncs.h
	$(CC) -c $(CFLAGS) symbolTable.c -o symbolTable.o
util.o: util.c util.h
	$(CC) -c $(CFLAGS) -ansi util.c -o util.o

clean:
	rm *.o main