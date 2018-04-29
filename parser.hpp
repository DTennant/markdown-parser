#ifndef _PARSER_H
#define _PARSER_H

#include "token.hpp"
#include "ast.hpp"
#include <vector>
#include <string>

using std::vector;
using std::string;

class Parser{
private:
	//data
	vector<Token> Token_list;
	vector<Token>::iterator Token_list_iter;
	//helper functions
	Token peek(void);
	bool eat_token(void);
	vector<string> get_url_des();
	
	Ast parse_everything(void);
	void parse_header(Ast&);
	void parse_splits(Ast&);
	void parse_quote(Ast&);
	void parse_order(Ast&);
	void parse_img(Ast&);
	void parse_url(Ast&);
	void parse_raw(Ast&);
	void parse_list(Ast&);
public:
	Parser(vector<Token> _Token_list)
			: Token_list(_Token_list){
				Token_list_iter = Token_list.begin();
			}
	~Parser(){}
	
	Ast run(void);
};


#endif
