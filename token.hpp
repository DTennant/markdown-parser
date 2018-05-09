#ifndef _TOKEN_H
#define _TOKEN_H

#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <vector>
#include <string>
#include "config.hpp"
#include <iostream>
#include <cstdio>
#include <map>

using std::map;
using std::vector;
using std::ifstream;
using std::string;
using std::cout;
using std::endl;

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
public:
	Token_type token_type;
	string content;
	Token(Token_type type, string _content): content(_content), token_type(type){}
	~Token(){}
};

class Toker{
private:
	string file_name_;
	ifstream in_file;
	vector<Token> Token_list;
	map<char, Token_type> token_map;
	void init_map(void);
	char check(char);
	bool israw(char ch){return (isalnum(ch) || (isspace(ch) && ch != '\n'));};
public:
	Toker(const char *file_name)
		//: in_file(_in_file){}
	{
		in_file.open(file_name);
		this->file_name_ = string(file_name);
		cout << "Processing: " << this->file_name_ << endl;
	}
	~Toker(){}
	vector<char> readfile();
	vector<Token> run(void);
};

#endif
