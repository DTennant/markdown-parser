main: main.o token.o parser.o ast.o
	g++ -o main main.o token.o parser.o ast.o --std=c++11

main.o: main.cc token.hpp parser.hpp ast.hpp
	g++ -c main.cc --std=c++11

token.o: token.cc token.hpp
	g++ -c token.cc --std=c++11

parser.o: parser.cc parser.hpp
	g++ -c parser.cc --std=c++11

ast.o: ast.cc ast.hpp
	g++ -c ast.cc --std=c++11

.PHONY: clean
clean:
	rm *.o