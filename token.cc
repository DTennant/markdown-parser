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
	if (FILE *fp = fopen("filename", "r")){
		char buf[1024];
		while (size_t len = fread(buf, 1, sizeof(buf), fp))
			v.insert(v.end(), buf, buf + len);
		fclose(fp);
	}
	return v;
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

vector<Token> Toker::run(void){
	vector<char> contents = this->readfile();
	this->init_map();
	for(auto iter = contents.begin(); iter != contents.end();){
		switch(this->check(*iter)){
			case SINGLE_TOKEN:
			{
				Token_list.push_back(Token(this->token_map[*iter], char2string(*iter++)));
				break;
			}
			case MULT_TOKEN:
			{
				if(*iter == '-'){
					if(*(iter + 1) == '-'){
						string raw;
						while(*iter == '-')raw += *iter++;
						Token_list.push_back(Token(T_SPLITS, raw));
					}else{
						Token_list.push_back(Token(T_RAW, char2string(*iter++)));
					}
				}else if(*iter == '#'){
					int cnt = 1;
					string sharp_string;
					while(*(++iter) == '#'){
						sharp_string += '#';
					}
					Token_list.push_back(Token(cnt <= 6 ? T_HEADER : T_RAW, sharp_string));
				}
				break;
			}
			case ELSE:
			default:// raw
			{
				string raw;
				raw += *iter;
				while(this->israw(*(++iter)))raw += *iter;
				Token_list.push_back(Token(T_RAW, raw));
			}
		}
	}
	return Token_list;
}