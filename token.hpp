#ifndef _TOKEN_H
#define _TOKEN_H

#include <fstream>
#include <vector>
#include <string>
#include "config.hpp"
#include <cstdio>
#include <map>

using std::map;
using std::vector;
using std::ifstream;
using std::string;

enum Token_type{
	T_HEADER, // num of '#' bigger than 6 is T_RAW
	T_SPLITS,
	T_QUOTE,
	T_LIST,
	T_BL,
	T_BR,
	T_SL,
	T_SR,
	T_NOT,
	T_RAW,
	T_EOL
};

class Token{
private:
	Token_type token_type;
	string content;
public:
	Token(Token_type type, string _content)
		: content(_content), 
			token_type(type){}
	~Token(){}
};

class Toker{
private:
	ifstream in_file;
	vector<Token> Token_list;
	map<char, Token_type> token_map;
	void init_map(void);
	char check(char);
	bool israw(char ch){return (isalnum(ch) || (isspace(ch) && ch != '\n'));};
public:
	Toker(ifstream _in_file)
		: in_file(_in_file){}
	~Toker(){}
	vector<char> readfile();
	vector<Token> run(void);
};

#endif
