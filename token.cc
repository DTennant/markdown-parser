#define _CRT_SECURE_NO_WARNINGS

#include "debug.hpp"
#include "token.hpp"
#include <fstream>
#include <vector>
#include <cstdio>
#include <map>
#include <algorithm>

#define PUSH_SINGLE_TOKEN_2_LIST(x) this->Token_list.push_back(Token((x), *iter))
#define MULT_TOKEN 0
#define SINGLE_TOKEN 1
#define ELSE 2

using std::map;
using std::make_pair;
using std::vector;
using std::ifstream;

vector<char> Toker::readfile(void){
	vector<char> v;
	if (FILE *fp = fopen(this->file_name_.c_str(), "r")){
		char buf[1024];
		while (size_t len = fread(buf, 1, sizeof(buf), fp))
			v.insert(v.end(), buf, buf + len);
		fclose(fp);
	}
/*#ifdef DEBUG
	for (auto i : v) {
		cout << i;
	}
#endif // DEBUG
	cout << endl;*/
	return v;
/*#ifdef _DEBUG
	cout << "in readfile()" << endl;
#endif // _DEBUG

	vector<char> v;
	//this->in_file.get();
	char ch;
	while ((ch = this->in_file.get()) != EOF) {
		v.push_back(ch);
	}
#ifdef _DEBUG
	cout << "in _DEBUG" << endl;
	for (auto i : v) {
		cout << i;
	}
#endif // _DEBUG

	return v;
*/
}

void Toker::init_map(void){
	token_map.insert(make_pair('>', T_QUOTE));
	token_map.insert(make_pair('*', T_LIST));
	token_map.insert(make_pair('[', T_BL));
	token_map.insert(make_pair(']', T_BR));
	token_map.insert(make_pair('(', T_SL));
	token_map.insert(make_pair(')', T_SR));
	token_map.insert(make_pair('!', T_NOT));
	token_map.insert(make_pair('\n', T_EOL));
}

char Toker::check(char ch){
	if(ch == '-' || ch == '#')return MULT_TOKEN;
	else if(israw(ch))return ELSE;
	else return SINGLE_TOKEN;
}

string char2string(char ch){
	string s;
	s += ch;
	return s;
}

#undef DEBUG

vector<Token> Toker::run(void){
	vector<Token> Token_list;
	vector<char> contents = this->readfile();
	this->init_map();
	for(auto iter = contents.begin(); iter != contents.end();){
		if ('\n' == *iter) {
			++iter;
			if (iter == contents.end())break;
			continue;
		}
#ifdef DEBUG
		cout << char2string(*iter) << " :   " << iter - contents.begin() << endl;
#endif // DEBUG
		switch(this->check(*iter)){
			case SINGLE_TOKEN:
			{
				Token_list.push_back(Token(this->token_map[*iter], char2string(*iter)));
				++iter;
#ifdef DEBUG
				cout << "case SINGLE_TOKEN" << endl;
				//system("pause");
#endif // DEBUG
				break;
			}
			case MULT_TOKEN:
			{
				if(*iter == '-'){
					if(*(iter + 1) == '-'){
						string raw;
						while(*iter == '-')raw += *iter++;
						Token_list.push_back(Token(T_SPLITS, raw));
#ifdef DEBUG
						cout << raw << " :    " << iter - contents.begin() << endl;
						cout << "case T_SPLITS" << endl;
						//system("pause");
#endif // DEBUG
					}else{
						Token_list.push_back(Token(T_RAW, char2string(*iter)));
						++iter;
#ifdef DEBUG
						cout << *(iter - 1) << " :    " << iter - contents.begin() - 1 << endl;
						cout << "case T_RAW" << endl;
						//system("pause");
#endif // DEBUG
					}
				}else if(*iter == '#'){
					int cnt = 1;
					string sharp_string;
					sharp_string += '#';
					while(*(++iter) == '#'){
						sharp_string += '#';
					}
					Token_list.push_back(Token(cnt <= 6 ? T_HEADER : T_RAW, sharp_string));
#ifdef DEBUG
					cout << sharp_string << " :    " << iter - contents.begin() << endl;
					cout << ((cnt <= 6) ? "case T_HEADER" : "case T_RAW") << endl;
					//system("pause");
#endif // DEBUG

				}
				break;
			}
			case ELSE:
			default:// raw
			{
				string raw;
				raw += *iter;
				while(this->israw(*(++iter)))raw += *iter;
#ifdef DEBUG
				cout << raw << " :    " << iter - contents.begin() << endl;
				cout << "case RAW" << endl;
				//system("pause");
#endif // DEBUG
				Token_list.push_back(Token(T_RAW, raw));
				break;
			}
		}
	}
//#define DEBUG
#ifdef DEBUG
	for (vector<Token>::iterator i = Token_list.begin(); i != Token_list.end(); ++i) {
		cout << "token_type: " << i->token_type
			<< " contents: " << i->content << endl;
	}
#endif // DEBUG
	this->Token_list = Token_list;
	return Token_list;
}