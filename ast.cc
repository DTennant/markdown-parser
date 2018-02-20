#include "ast.hpp"


void Ast::add_child(int i){
	this->child.push_back(i);
}

int add_ast(Ast tree){
	tree_list.push_back(tree);
	return tree_list.size() - 1;
}

string Ast::eval(){
	switch(this->tree_type){
		case TOP_AST:
		default:
			
	}
}