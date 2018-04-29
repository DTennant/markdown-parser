// Created by Tennant 
// 18/01/19

#include <iostream>
#include <fstream>
#include "config.hpp"
#include "parser.hpp"
#include "token.hpp"
#include "ast.hpp"

using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;

void Usage(char const *s){
	cerr << "Uasge: " << s << " input_file.md " << "output_file.html" << endl;
}

int main(int argc, char const *argv[]){
	if(argc < 3){
		Usage(argv[0]);
		return 1;
	}
	ifstream in_file;
	ofstream out_file;
	in_file.open(argv[1]);
	out_file.open(argv[2]);

	Toker t(argv[1]);
	Parser p(t.run());
	Ast tree(p.run());

	out_file << tree.eval() << endl;

	in_file.close();
	out_file.close();

	return 0;
}
