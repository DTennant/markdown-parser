#ifndef _AST_H
#define _AST_H

#include <string>
#include <vector>

using std::vector;
using std::string;

enum Ast_type{
	TOP_AST, // special type : it's the tree at the top
	HEAD_AST, //T_HEADER
	DASH_AST, //T_DASH
	SPLITS_AST, //T_SPLITS
	QUOTE_AST, //T_QUOTE
	ORDER_AST, //T_ORDER
	IMG_AST, //T_NOT
	URL_AST, //T_BL
	RAW_AST, //T_RAW
};

class Ast{
private:
	Ast_type tree_type;
	vector<int> child;
	vector<string> contents;
public:
	Ast(Ast_type _tree_type)
		: tree_type(_tree_type){}
	Ast(Ast_type _tree_type,
		vector<string> _contents)
		: tree_type(_tree_type),
			contents(_contens){}
	~Ast();
	string eval();
	void add_child(int);
};

vector<Ast> tree_list;

int add_ast(Ast);

//#include "ast.cc"

#endif
