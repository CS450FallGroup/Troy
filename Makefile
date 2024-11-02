a.exe: main.o
	g++ -std=c++20 main.o SourceReader.o StringParser.o Scanner.o -o a.exe

main.o: main.cpp Scanner.o
	g++ -c -std=c++20 main.cpp -o main.o

SourceReader.o: SourceReader.cpp SourceReader.h StringParser.o
	g++ -c -std=c++20 SourceReader.cpp -o SourceReader.o

StringParser.o: StringParser.cpp StringParser.h
	g++ -c -std=c++20 StringParser.cpp -o StringParser.o

Scanner.o: Scanner.hpp Scanner.cpp SourceReader.o
	g++ -c -std=c++20 Scanner.cpp -o Scanner.o

clean:
	rm -rf *.o

assignment1:
	make -f deliverables/assignment1/Makefile

assignment2:
	make -f deliverables/assignment2/Makefile
	
TestSourceReader:
	make -f tests/SourceReader/Makefile

TestScanner:
	make -f tests/Scanner/Makefile

TestExpressionConverter:
	make -f tests/ShuntingYard/Makefile

assignment3:
	make -f deliverables/assignment3/Makefile

TestSymbolTable:
	make -f tests/SymbolTable/Makefile

assignment4:
	make -f deliverables/assignment4/Makefile