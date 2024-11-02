a.exe: main.o
	g++ -std=c++20 main.o SourceReader.o StringParser.o Scanner.o -o a.exe

main.o: deliverables/assignment2/main.cpp Scanner.o
	g++ -c -std=c++20 deliverables/assignment2/main.cpp -o main.o

SourceReader.o: SourceReader.cpp SourceReader.h StringParser.o
	g++ -c -std=c++20 SourceReader.cpp -o SourceReader.o

StringParser.o: StringParser.cpp StringParser.h
	g++ -c -std=c++20 StringParser.cpp -o StringParser.o

Scanner.o: Scanner.hpp Scanner.cpp SourceReader.o
	g++ -c -std=c++20 Scanner.cpp -o Scanner.o