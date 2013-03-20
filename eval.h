#include <iostream>
#include <string.h>
#include <stdio.h>
#ifndef STACKH
#include "stack.h"
#endif
using namespace std;

int get_result(int a, int b, char oper) {
	switch(oper) {
		case '+' : return a+b;
		case '-' : return a-b;
		case '*' : return a*b;
		case '/' : 
			if(b==0) {
				cout << "Error: divide by zero" << endl;
				return 0;
			} return a/b;
		case '^' : 
			int out = 1;
			for(int i=0; i<b; i++) out*=a;
			return out;
	}
}

int precedence(char c) {
	switch(c) {
		case '+': case '-': return 0;
		case '*': case '/': return 1;
		case '^': return 2;
		case '(': return -1;
	}
	return 0;
}
int eval_infix(string exp) {
	int open=0, close=0;
	for(int i=0; i<exp.size(); i++) {
		if(exp[i]=='(') open++;
		else if(exp[i]==')') close++;
	}
	if(open!=close) {
		cout << "Error: mismatched parentheses" << endl;
		return 0;
	}
	stack<int> /*oper*/ators;
	stack<int> /*oper*/ands;
	int current = 0;
	bool num = false;
	int neg = 1;
	for(int i=0; i<exp.size(); i++) {
		char c = exp[i];
		if(c=='-' && !num) {
			neg = -1;
			continue;
		}
		if(string("+-*/^() ").find(c)!=string::npos && num) {
			num = false;
			ands.push(current);
			current = 0;
			if(c=='(') num = true;
		}
		if(string("1234567890").find(c)!=string::npos) {
			if(ators.peek()==')') {
				ators.pop();
				ators.push('*');
			}
			current = current*10 + neg*(c-'0');
			num = true;
		} else if(string("+-*/^").find(c)!=string::npos) {
			if(ators.peek()==')') ators.pop();
			char last = ators.peek();
			while(last>0 && precedence(last)>=precedence(c)) {
				int b = ands.pop();
				int a = ands.pop();
				ands.push(get_result(a,b,ators.pop()));
				neg =1;
				last = ators.peek();
			}
			ators.push(c);
		} else if(c=='(') {
			if(num) {
				num = false;
				ators.push('*');
			} else if(ators.peek()==')') {
				ators.pop();
				ators.push('*');
			}
			ators.push(c);
		} else if(c==')') {
			if(ators.peek()==')') ators.pop();
			char last = ators.peek();
			while(last!='(') {
				int b = ands.pop();
				int a = ands.pop();
				ands.push(get_result(a,b,ators.pop()));
				neg =1;
				last = ators.peek();
			}
			ators.pop();
			ators.push(c);
		}
		cout << "Presently on <" << c << ">: " << ands << ", " << ators << ", neg is " << neg << endl;
	}
	if(ators.peek()==')') ators.pop();
	if(num) ands.push(current);
	while(ators.size()>0) {
		int b = ands.pop();
		int a = ands.pop();
		ands.push(get_result(a,b,ators.pop()));
	}
	cout << ands.pop() << endl;
	return 0;
}

int eval_prefix(string exp) {
	stack<int> /*oper*/ators;
	stack<int> /*oper*/ands;
	int current = 0;
	bool num = false;
	for(int i=0; i<strlen(exp.c_str()); i++) {
		char c = exp[i];
		if(num && string(" |+-*/").find(c)!=string::npos) {
			num = false;
			ands.push(current);
			current = 0;
		} 
		if(string("1234567890").find(c)!=string::npos) {
			current = current*10+(c-'0');
			num = true;
		} else if(string("+-*/^").find(c)!=string::npos) {
			ators.push(c);
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
		if(num && string(" |+-*/^").find(c)!=string::npos) {
			num = false;
			ands.push(current);
			current = 0;
		}
		if(string("1234567890").find(c)!=string::npos) {
			current = current*10+(c-'0');
			num = true;
		} else if(string("+-*/^").find(c)!=string::npos) {
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
