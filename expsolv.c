#include <iostream>
#include <string.h>
#include <stdio.h>
#include "stack.h"
using namespace std;

#define INFIX 0
#define PREFIX 1
#define POSTFIX 2

int glob_mode;
string pre_to_pos(string exp);
string inf_to_pos(string exp);
int handle_expression(string exp) {
	if(glob_mode==PREFIX) exp = pre_to_pos(exp);
	if(glob_mode==INFIX) exp= inf_to_pos(exp);
	stack<int> /*oper*/ands;
	int current = 0;
	bool num = false;
	for(int i=0; i<strlen(exp.c_str()); i++) {
		char c = exp[i];
		if((c==' ' || c=='|')&&num) {
			num = false;
			ands.push(current);
			current = 0;
		} else if(string("1234567890").find(c)!=string::npos) {
			current = current*10+(c-'0');
			num = true;
		} else if(string("+-*/^").find(c)!=string::npos) {
			if(num) {
				ands.push(current);
				current = 0;
				num = false;
			}
			if(ands.size()<2) {
				cout << "Error: not enough operands for '"<<c<<"' at pos "<<i<<": " << ands << endl;
				return 1;
			}
			int b = ands.pop();
			int a = ands.pop();
			switch(c) {
				case '+' : ands.push(a+b); break;
				case '-' : ands.push(a-b); break;
				case '*' : ands.push(a*b); break;
				case '/' : ands.push(a/b); break;
				case '^' : 
					int out = 1;
					for(int i=0; i<b; i++) out*=a;
					ands.push(out); break;
			}
		}
	}
    if(ands.size()==0) ands.push(0);
	if(ands.size()!=1) {
		cout << "Error: too many leftovers: "<<ands << endl;
		return 1;
	}
	cout << ands.pop() << endl;
	return 0;
}

int main(int argc, char** argv) {
	if(argc>1) {
		string exp = "";
		for(int i=0; i<argc; i++) {
			char* arg = argv[i];
			for(int i=0; i<strlen(arg); i++) {
				char c = arg[i];
				exp += c;
				exp += " ";
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


string pre_to_pos(string exp) {
    return exp;
}

string inf_to_pos(string exp) {
	return exp;
}
