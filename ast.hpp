#ifndef _AST_H
#define _AST_H

#include <string>
#include <vector>

using std::vector;
using std::string;

enum Ast_type{
	TOP_AST, // special type : it's the tree at the top
	HEAD_AST, //T_HEADER
	SPLITS_AST, //T_SPLITS
	QUOTE_AST, //T_QUOTE
	LIST_AST, //T_ORDER
	IMG_AST, //T_NOT
	URL_AST, //T_BL
	RAW_AST, //T_RAW
};

class Ast{
//private:
public:
	Ast_type tree_type;
	vector<int> child;
	vector<string> contents;
public:
	Ast(Ast_type _tree_type)
		: tree_type(_tree_type){}
	Ast(Ast_type _tree_type,
		vector<string> _contents)
		: tree_type(_tree_type),
			contents(_contents){}
	~Ast(){};
	string eval();
	void add_child(Ast&);
};


int add_ast(Ast);


string eval_head(const Ast&);
string eval_splits(const Ast&);
string eval_quote(const Ast&);
string eval_list(const Ast&);
string eval_img(const Ast&);
string eval_url(const Ast&);
string eval_raw(const Ast&);

//#include "ast.cc"

#endif
