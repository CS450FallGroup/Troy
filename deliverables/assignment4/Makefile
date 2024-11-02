a.exe: main.o
	g++ -std=c++20 main.o SourceReader.o StringParser.o Scanner.o DescentParser.o SymbolTable.o -o a.exe

main.o: deliverables/assignment4/main.cpp Scanner.o DescentParser.o
	g++ -c -std=c++20 deliverables/assignment4/main.cpp -o main.o

SourceReader.o: SourceReader.cpp SourceReader.h StringParser.o
	g++ -c -std=c++20 SourceReader.cpp -o SourceReader.o

StringParser.o: StringParser.cpp StringParser.h
	g++ -c -std=c++20 StringParser.cpp -o StringParser.o

Scanner.o: Scanner.hpp Scanner.cpp SourceReader.o
	g++ -c -std=c++20 Scanner.cpp -o Scanner.o

DescentParser.o: DescentParser.hpp DescentParser.cpp SymbolTable.o
	g++ -c -std=c++20 DescentParser.cpp -o DescentParser.o

SymbolTable.o: SymbolTable.hpp SymbolTable.cpp
	g++ -c -std=c++20 SymbolTable.cpp -o SymbolTable.o