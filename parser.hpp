#ifndef _PARSER_H
#define _PARSER_H

#include "token.hpp"
#include "ast.hpp"
#include <vector>

using std::vector;

class Parser{
private:
	vector<Token> Token_list;
public:
	Parser(vector<Token> _Token_list)
			: Token_list(_Token_list){}
	~Parser(){}
	
	Ast run(void);
};

#endif
