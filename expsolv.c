#include <iostream>
#include <string.h>
#include <stdio.h>
#include "stack.h"
#include "eval.h"
using namespace std;

#define INFIX 0
#define PREFIX 1
#define POSTFIX 2

int glob_mode;
string pre_to_pos(string exp);
string inf_to_pos(string exp);
int handle_expression(string exp) {
	if(glob_mode==PREFIX)
		return eval_prefix(exp);
	if(glob_mode==INFIX)
		return eval_infix(exp);
	if(glob_mode==POSTFIX)
		return eval_postfix(exp);
	cout << "Error: can't." << endl;
	return 1;	
}

int main(int argc, char** argv) {
	if(argc>1) {
		string exp = "";
		for(int i=1; i<argc; i++) {
			char* arg = argv[i];
			for(int i=0; i<strlen(arg); i++) {
				char c = arg[i];
				exp += c;
			}
		}
		return handle_expression(exp);
	}
	cout << "Input one expression in infix per line.  Type 'mode' to switch between in/pre/post-fix." << endl;
	cout << "Input a blank line to finish.  Supported operators: +-*/^ always, () in infix, | or space separates numbers in pre and postfix." << endl;
	string input = "";
	do {
		cout << "> ";
		getline(cin,input);
		if(input=="") break;
		if(input=="mode") {
			cout << "If the next line starts with 'i' you'll be in infix; 'pr' to prefix; 'po' to postfix." << endl;
			cout << "Mode: ";
			getline(cin,input);
			if(!strncmp(input.c_str(),"i",1)) {
				cout << "Now in infix mode\n" << endl;
				glob_mode = INFIX;
			} else if(!strncmp(input.c_str(),"pr",2)) {
				cout << "Now in prefix mode\n" << endl;
				glob_mode = PREFIX;
			} else if(!strncmp(input.c_str(),"po",2)) {
				cout << "Now in postfix mode\n" << endl;
				glob_mode = POSTFIX;
			}
            continue;
		}
		int out = handle_expression(input);
		if(out!=0) return out;
	} while(input!="");
}
