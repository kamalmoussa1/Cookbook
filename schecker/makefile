
bin/checker : main.o parser.o dictionary.o 
	g++ bin/parser.o bin/main.o bin/dictionary.o  -o bin/checker

main.o : src/main.cpp inc/parser.h inc/checkererror.h inc/dictionary.h
	g++ -I inc -c src/main.cpp -o bin/main.o

parser.o : src/parser.cpp inc/parser.h inc/checkererror.h
	g++ -I inc -c src/parser.cpp -o bin/parser.o

dictionary.o : src/dictionary.cpp inc/checkererror.h
	g++ -I inc -c src/dictionary.cpp -o bin/dictionary.o

csvreporter.o : src/csvreporter.pp inc/reporter.h 
	g++ -I inc -c src/csvreporter.cpp -o bin/csvreporter.o