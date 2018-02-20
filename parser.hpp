#ifndef _PARSER_H
#define _PARSER_H

#include "token.hpp"
#include "ast.hpp"
#include <vector>

using std::vector;

class Parser{
private:
	vector<Token> Token_list;
	vector<Token>::iterator Token_list_iter;
	Token peek(void);
	bool eat_token(void);
	Ast parse_everything(void);
	void parse_header(Ast&);
	void parse_splits(Ast&);
	void parse_quote(Ast&);
	void parse_order(Ast&);
	void parse_img(Ast&);
	void parse_url(Ast&);
	void parse_raw(Ast&);
public:
	Parser(vector<Token> _Token_list)
			: Token_list(_Token_list){
				Token_list_iter = Token_list.begin();
			}
	~Parser(){}
	
	Ast run(void);
};

#endif
