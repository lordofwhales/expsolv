#include <iostream>
#include <string.h>
#include <stdio.h>
#ifndef STACKH
#include "stack.h"
#endif
#include "infix.h"
using namespace std;

int get_result(int a, int b, char oper) {
	switch(oper) {
		case '+' : return a+b;
		case '-' : return a-b;
		case '*' : return a*b;
		case '/' : return a/b;
		case '^' : 
			int out = 1;
			for(int i=0; i<b; i++) out*=a;
			return out;
	}
}

int eval_infix(string exp) {
	exp = infix_parens(exp);
	exp = infix_mult(exp);
	exp = infix_add(exp);
	if(exp.find("%")==0) {
		cout << "Error: " << exp.substr(1,exp.size()) << endl;
		return 1;
	}
	cout << exp << endl;
	return 0;
}

int eval_prefix(string exp) {
	stack<int> /*oper*/ators;
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
			ators.push(c);
			if(num) {
				num = false;
				ands.push(current);
				current=0;
			}
		}

		while(ands.size()>=2) {
			int b = ands.pop();
			int a = ands.pop();
			ands.push(get_result(a,b,ators.pop()));
		}
	}
	if(num) {
		num = false;
		ands.push(current);
		current = 0;
	}
	while(ands.size()>=2) {
			int b = ands.pop();
			int a = ands.pop();
			ands.push(get_result(a,b,ators.pop()));
		}
	if(ators.size()>0) {
		cout << "Error: not enough operands for "<<ators<<endl;
		return 1;
	}
	if(ands.size()==0) ands.push(0);
	if(ands.size()!=1) {
		cout << "Error: too many leftovers: "<<ands << endl;
		return 1;
	}
	cout << ands.pop() << endl;
	return 0;
}

int eval_postfix(string exp) {
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
			ands.push(get_result(a,b,c));
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
