#include <iostream>
#include <string.h>
#include <stdio.h>
#ifndef STACKH
#include "stack.h"
#endif
using namespace std;

string infix_parens(string exp) {
	int open=-1;
	while(exp.find("(")!=string::npos) {
		for(int i=0; i<exp.size(); i++) {
			char c = exp[i];
			if(c==')') {
				if(open==-1) {
					exp = string("\%no matching parentheses")
					return exp;
				}
				exp = exp.substr(0,open)+infix_mult(exp.substr(open+1,i-open-1))+exp.substr(i,exp.size());
			if(c=='(') open = c;
		}
	}
}

string infix_mult(string exp) {

}

string infix_add(string exp) {

}
