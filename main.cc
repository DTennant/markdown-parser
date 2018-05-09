// Created by Tennant 
// 18/01/19

#include <iostream>
#include <fstream>
#include "config.hpp"
#include "parser.hpp"
#include "token.hpp"
#include "ast.hpp"
#include "debug.hpp"


using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;

void Usage(char const *s){
	cerr << "Uasge: " << s << " input_file.md " << "output_file.html" << endl;
}

int main(int argc, char const *argv[]){
	/*if(argc < 3){
		Usage(argv[0]);
		return 1;
	}*/
	ifstream in_file;
	ofstream out_file, log_file;
	/*in_file.open(argv[1]);
	out_file.open(argv[2]);*/

	in_file.open("test.md");
	out_file.open("test.html");
	log_file.open("log.txt");

	//Toker t(argv[1]);
	Toker t("D:\\project\\markdown-parser\\test.md");

	vector<Token> token_res = t.run();

	Parser p(token_res);
	Ast tree = p.run();
/*
	out_file << tree.eval() << endl;
*/
	in_file.close();
	out_file.close();

#ifdef DEBUG
	system("pause");
#endif
	return 0;
}