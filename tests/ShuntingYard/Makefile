a.exe: main.o
	g++ -std=c++20 main.o SourceReader.o StringParser.o Scanner.o PostFixEvaluator.o -o a.exe

main.o: tests/ShuntingYard/main.cpp PostFixEvaluator.o
	g++ -c -std=c++20 tests/ShuntingYard/main.cpp -o main.o

Scanner.o: Scanner.hpp Scanner.cpp SourceReader.o
	g++ -c -std=c++20 Scanner.cpp -o Scanner.o

PostFixEvaluator.o: Scanner.o PostFixEvaluator.hpp PostFixEvaluator.cpp
	g++ -c -std=c++20 PostFixEvaluator.cpp -o PostFixEvaluator.o

SourceReader.o: SourceReader.cpp SourceReader.h StringParser.o
	g++ -c -std=c++20 SourceReader.cpp -o SourceReader.o

StringParser.o: StringParser.cpp StringParser.h
	g++ -c -std=c++20 StringParser.cpp -o StringParser.o
