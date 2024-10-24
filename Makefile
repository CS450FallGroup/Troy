a.exe: main.o
	g++ -std=c++20 main.o SymbolTable.o SourceReader.o StringParser.o Scanner.o -o a.exe

main.o: main.cpp Scanner.o
	g++ -c -std=c++20 main.cpp -o main.o

SymbolTable.o: SymbolTable.cpp SymbolTable.hpp StringParser.o
	g++ -c -std=c++20 SymbolTable.cpp -o SymbolTable.o

SourceReader.o: SourceReader.cpp SourceReader.h StringParser.o
	g++ -c -std=c++20 SourceReader.cpp -o SourceReader.o

StringParser.o: StringParser.cpp StringParser.h
	g++ -c -std=c++20 StringParser.cpp -o StringParser.o

Scanner.o: Scanner/Scanner.hpp Scanner/Scanner.cpp SourceReader.o
	g++ -c -std=c++20 Scanner/Scanner.cpp -o Scanner.o

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