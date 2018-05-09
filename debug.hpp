#ifndef _DEBUG_H
#define _DEBUG_H

#define DEBUG

#include <iostream>
#include <fstream>

using std::ofstream;
using std::endl;
using std::cout;

template <class T>
void write2log(T ch) {
	ofstream log_file;
	log_file.open("log.txt");
	log_file << ch << endl;
}

#endif // !_DEBUG_H
