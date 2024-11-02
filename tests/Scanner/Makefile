a.exe: main.o
	g++ -std=c++20 main.o SourceReader.o StringParser.o Scanner.o -o a.exe

main.o: tests/Scanner/main.cpp Scanner.o
	g++ -c -std=c++20 tests/Scanner/main.cpp

SourceReader.o: SourceReader.cpp SourceReader.h StringParser.o
	g++ -c -std=c++20 SourceReader.cpp -o SourceReader.o

StringParser.o: StringParser.cpp StringParser.h
	g++ -c -std=c++20 StringParser.cpp -o StringParser.o

Scanner.o: Scanner.hpp Scanner.cpp SourceReader.o
	g++ -c -std=c++20 Scanner.cpp -o Scanner.o
