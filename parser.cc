#include "parser.hpp"
#include "ast.hpp"
#include "debug.hpp"
#undef DEBUG

#define ATTR_ITER(x) this->Token_list_iter->x

using std::to_string;

Token Parser::peek(void){
	return *this->Token_list_iter;
}

// TODO: Error handler
bool Parser::eat_token(void){
	this->Token_list_iter++;
	if(this->Token_list_iter == this->Token_list.end())return false;
	return true;
}

vector<string> Parser::get_url_des(){
	vector<string> contents;
	//if(this->peek().token_type != T_BL) Error
	eat_token();
	//if(this->peek().token_type != T_RAW) Error
	contents.push_back(ATTR_ITER(content));
	eat_token();
	//if(this->peek().token_type != T_BR) Error
	eat_token();
	//if(this->peek().token_type != T_SL) Error
	eat_token();
	//if(this->peek().token_type != T_RAW) Error
	contents.push_back(ATTR_ITER(content));
	eat_token();
	//if(this->peek().token_type != T_SR) Error
	eat_token();
	return contents;
}

//tree.contents[0] is the num of the header
//tree.contents[1] is the description of the header
void Parser::parse_header(Ast& tree){
	Ast_type tree_type = HEAD_AST;
	vector<string> contents;
	contents.push_back(to_string(ATTR_ITER(content.size())));
	eat_token();
	//if(this->peek().token_type != T_RAW) Error
	contents.push_back(ATTR_ITER(content));
	//if(this->peek().token_type != T_EOL) Error
	eat_token();
	Ast head_ast(HEAD_AST, contents);
#ifdef DEBUG
	cout << "ast tree_type: " << head_ast.tree_type << endl
		<< " tree contents[0]: " << head_ast.contents[0] << endl
		<< " tree contents[1]: " << head_ast.contents[1] << endl;
#endif // DEBUG

	tree.add_child(head_ast);
}

void Parser::parse_splits(Ast& tree){
	Ast splits_ast(SPLITS_AST);
#ifdef DEBUG
	cout << "ast tree_type: " << splits_ast.tree_type << endl;
#endif // DEBUG
	tree.add_child(splits_ast);
	eat_token();
}

//now this did not support recursive structure
//tree.contents is the items of the quote
//TODO: recursive structure
void Parser::parse_quote(Ast& tree){
	Ast_type tree_type = QUOTE_AST;
	vector<string> contents;
	for(;this->peek().token_type == T_QUOTE;){
		eat_token();
		//if(this->peek().token_type != T_RAW) Error
		contents.push_back(ATTR_ITER(content));
		eat_token();
	}
	Ast quote_ast(tree_type, contents);
#ifdef DEBUG
	cout << "ast tree_type: " << quote_ast.tree_type << endl;
	for (int i = 0; i < quote_ast.contents.size(); ++i) {
		cout << " tree contents[" << i << "]: " << quote_ast.contents[i] << endl;
	}
#endif // DEBUG

	tree.add_child(quote_ast);
}

//tree.contents is the items of the list
void Parser::parse_list(Ast& tree){
	Ast_type tree_type = LIST_AST;
	vector<string> contents;
	for(;this->peek().token_type == T_LIST;){
		eat_token();
		//if(this->peek().token_type != T_RAW) Error
		contents.push_back(ATTR_ITER(content));
		eat_token();
	}
	Ast list_ast(tree_type, contents);
#ifdef DEBUG
	cout << "ast tree_type: " << list_ast.tree_type << endl;
	for (int i = 0; i < list_ast.contents.size(); ++i) {
		cout << " tree contents[" << i << "]: " << list_ast.contents[i] << endl;
	}
#endif // DEBUG

	tree.add_child(list_ast);
}

void Parser::parse_raw(Ast& tree){
	Ast_type tree_type = RAW_AST;
	vector<string> contents;
	contents.push_back(ATTR_ITER(content));
	Ast raw_ast(RAW_AST, contents);
#ifdef DEBUG
	cout << "ast tree_type: " << raw_ast.tree_type << endl;
	for (int i = 0; i < raw_ast.contents.size(); ++i) {
		cout << " tree contents[" << i << "]: " << raw_ast.contents[i] << endl;
	}
#endif // DEBUG
	tree.add_child(raw_ast);
	eat_token();
}

//tree.contents[0] is src, tree.contents[1] is description
void Parser::parse_img(Ast& tree){
	eat_token();
	vector<string> contents = get_url_des();
	Ast_type tree_type = IMG_AST;
	Ast img_ast(IMG_AST, contents);
#ifdef DEBUG
	cout << "ast tree_type: " << img_ast.tree_type << endl;
	for (int i = 0; i < img_ast.contents.size(); ++i) {
		cout << " tree contents[" << i << "]: " << img_ast.contents[i] << endl;
	}
#endif // DEBUG
	tree.add_child(img_ast);
}

//tree.contents[0] is src, tree.contents[1] is description
void Parser::parse_url(Ast& tree){
	vector<string> contents = get_url_des();
	Ast_type tree_type = URL_AST;
	Ast url_ast(URL_AST, contents);
#ifdef DEBUG
	cout << "ast tree_type: " << url_ast.tree_type << endl;
	for (int i = 0; i < url_ast.contents.size(); ++i) {
		cout << " tree contents[" << i << "]: " << url_ast.contents[i] << endl;
	}
#endif // DEBUG
	tree.add_child(url_ast);
}

Ast Parser::parse_everything(void){
#ifdef DEBUG
	cout << "into parse_everything" << endl;
#endif
	Ast tree(TOP_AST);
	for(;this->Token_list_iter != this->Token_list.end();){
#ifdef DEBUG
		cout << "token_type: " << this->peek().token_type
			<< " contents: " << this->peek().content << endl;
#endif // DEBUG
		switch(this->peek().token_type){
			case T_HEADER:
			{
#ifdef DEBUG
				cout << "parse_header" << endl;
#endif // DEBUG
				this->parse_header(tree);
				break;
			}
			case T_SPLITS:
			{
#ifdef DEBUG
				cout << "parse_splits" << endl;
#endif // DEBUG
				this->parse_splits(tree);
				break;
			}
			case T_QUOTE:
			{
#ifdef DEBUG
				cout << "parse_quote" << endl;
#endif // DEBUG
				this->parse_quote(tree);
				break;
			}
			case T_LIST:
			{
#ifdef DEBUG
				cout << "parse_list" << endl;
#endif // DEBUG
				this->parse_list(tree);
				break;
			}
			case T_NOT:
			{
#ifdef DEBUG
				cout << "parse_img" << endl;
#endif // DEBUG
				this->parse_img(tree);
				break;
			}
			case T_BL:
			{
#ifdef DEBUG
				cout << "parse_url" << endl;
#endif // DEBUG
				this->parse_url(tree);
				break;
			}
			case T_EOL:
			{
#ifdef DEBUG
				cout << "parse_eol" << endl;
#endif // DEBUG
				this->eat_token();
				break;
			}
			case T_RAW:
			default:
			{
#ifdef DEBUG
				cout << "parse_raw" << endl;
#endif // DEBUG
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
		if(iter->token_type == T_NOT && (iter + 1)->token_type != T_BL){
			iter->token_type = T_RAW;
		}
	}
#undef DEBUG
#ifdef DEBUG
	for (vector<Token>::iterator i = Token_list.begin(); i != Token_list.end(); ++i) {
		cout << "token_type: " << i->token_type
			<< " contents: " << i->content << endl;
	}
#endif // DEBUG
	return this->parse_everything();
}