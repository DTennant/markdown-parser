#include "ast.hpp"
#include "debug.hpp"

vector<Ast> tree_list;

void Ast::add_child(Ast &tree){
	tree_list.push_back(tree);
	this->child.push_back(tree_list.size() - 1);
}

string Ast::eval(){
	string return_string;
	switch(this->tree_type){
		case HEAD_AST:
			return_string += eval_head(*this);
		break;
		case SPLITS_AST:
			return_string += eval_splits(*this);
		break;
		case QUOTE_AST:
			return_string += eval_quote(*this);
		break;
		case LIST_AST:
			return_string += eval_list(*this);
		break;
		case IMG_AST:
			return_string += eval_img(*this);
		break;
		case URL_AST:
			return_string += eval_url(*this);
		break;
		case RAW_AST:
			return_string += eval_raw(*this);
		break;
		case TOP_AST:
			for (auto i : this->child) {
				return_string += tree_list[i].eval();
			}
		break;
	}
	return return_string;
}

string eval_head(const Ast &tree){
	string before_string, after_string, return_string;
	before_string = "<h" + tree.contents[0] + ">"; // for header tree, contents[0] is the num of header
	after_string = "</h" + tree.contents[0] + ">";
	return_string += before_string + tree.contents[1] + after_string;
	//contents[1] is description of this header
	return return_string;
}

string eval_splits(const Ast &tree){
	return string("<hr />");
}

string eval_quote(const Ast &tree){
	string return_string("<blockquote>"), after_string("</blockquote>");
	for(auto i : tree.contents){
		return_string += i + string("<br />");
	}
	return return_string + after_string;
}

string eval_list(const Ast &tree){
	string return_string("<ul>"), after_string("</ul>");
	for(auto i : tree.contents){
		return_string += string("<li>") + i + string("</li>"); 
	}
	return return_string + after_string;
}

string eval_img(const Ast &tree){
	string return_string("<img src=\""), after_string("\" />");
	return_string += tree.contents[0] + string("\" alt=\"") + tree.contents[1] + after_string;
	// for img-tree contents[0] is src, contents[1] is description
	return return_string;
}

string eval_url(const Ast &tree){
	string return_string("<a href=\""), after_string("</a>");
	return_string += tree.contents[0] + string("\">") + tree.contents[1] + after_string;
	// for url-tree contents[0] is src, contents[1] is description
	return return_string;
}

string eval_raw(const Ast &tree){
	return tree.contents[0];
}