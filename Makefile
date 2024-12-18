a.exe: main.o
	g++ -std=c++20 main.o SourceReader.o StringParser.o Scanner.o SymbolTable.o DescentParser.o Tools.o CodeNode.o PostFixEvaluator.o -o a.exe

main.o: main.cpp DescentParser.o SymbolTable.o
	g++ -c -std=c++20 main.cpp -o main.o

SourceReader.o: SourceReader.cpp SourceReader.h StringParser.o
	g++ -c -std=c++20 SourceReader.cpp -o SourceReader.o

StringParser.o: StringParser.cpp StringParser.h
	g++ -c -std=c++20 StringParser.cpp -o StringParser.o

Scanner.o: Scanner.hpp Scanner.cpp SourceReader.o
	g++ -c -std=c++20 Scanner.cpp -o Scanner.o

DescentParser.o: DescentParser.hpp DescentParser.cpp Scanner.o SymbolTable.o CodeNode.o PostFixEvaluator.o
	g++ -c -std=c++20 DescentParser.cpp -o DescentParser.o
	
SymbolTable.o: SymbolTable.hpp SymbolTable.cpp Tools.o 
	g++ -c -std=c++20 SymbolTable.cpp -o SymbolTable.o

Tools.o: Tools.cpp Tools.hpp
	g++ -c -std=c++20 Tools.cpp -o Tools.o

CodeNode.o: CodeNode.cpp CodeNode.hpp
	g++ -c -std=c++20 CodeNode.cpp -o CodeNode.o

PostFixEvaluator.o: PostFixEvaluator.cpp PostFixEvaluator.hpp Scanner.o
	g++ -c -std=c++20 PostFixEvaluator.cpp -o PostFixEvaluator.o

clean: 
	rm -rf *.o a.exe

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

TestAST:
	make -f tests/AbstractSyntaxTree/Makefile

assignment4:
	make -f deliverables/assignment4/Makefile