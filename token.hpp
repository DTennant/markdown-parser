#ifndef _TOKEN_H
#define _TOKEN_H

#include <fstream>
#include <vector>
#include <string>
#include "config.hpp"

using std::vector;
using std::ifstream;
using std::string;



class Token{
private:
	int token_type;
	string content;
public:
	Token(int type, string _content)
		: content(_content), 
			token_type(type){}
	~Token(){}
};

class Toker{
private:
	ifstream in_file;
	vector<Token> Token_list;
public:
	Toker(ifstream _in_file)
		: in_file(_in_file){}
	~Toker();
	vector<Token> run(void);
};

#endif
