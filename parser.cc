#include "parser.hpp"
#include "ast.hpp"


Token Parser::peek(void){
	return *this->Token_list_iter;
}

bool Parser::eat_token(void){
	this->Token_list_iter++;
	if(this->Token_list_iter == this->Token_list.end())return false;
	return true;
}

void Parser::parse_header(Ast& tree){

}

void Parser::parse_splits(Ast& tree){

}

void Parser::parse_quote(Ast& tree){

}

void Parser::parse_order(Ast& tree){

}

void Parser::parse_img(Ast& tree){

}

void Parser::parse_url(Ast& tree){

}

void Parser::parse_raw(Ast& tree){
	
}

Ast Parser::parse_everything(void){
	Ast tree(TOP_AST);
	for(;this->Token_list_iter != this->Token_list.end();){
		switch(this->peek()->token_type){
			case T_HEADER:
			{
				this->parse_header(tree);
				break;
			}
			case T_SPLITS:
			{
				this->parse_splits(tree);
				break;
			}
			case T_QUOTE:
			{
				this->parse_quote(tree);
				break;
			}
			case T_ORDER:
			{
				this->parse_order(tree);
				break;
			}
			case T_NOT:
			{
				this->parse_img(tree);
				break;
			}
			case T_BL:
			{
				this->parse_url(tree);
				break;
			}
			case T_RAW:
			{
				this->parse_raw(tree);
				break;
			}
		}
	}
	return tree;
}

Ast Parser::run(void){
	//prework: change T_NOT(not followed by T_BL) to T_RAW
	for(vector<Token>::iterator iter = this->Token_list.begin();
		iter != this->Token_list.end();
		++iter){
		if(iter->token_type == T_NOT
			&& (iter + 1)->token_type != T_BL){
			iter->token_type = T_RAW;
		}
	}
	return this->parse_everything();
}
