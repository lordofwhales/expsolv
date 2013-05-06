#include <iostream>
using namespace std;

#ifndef STACKH
#include "newstack.h"
#endif

int main() {
	stack<int> foo;

	cout << "==========" << endl;
	cout << "STACK TEST" << endl;
	cout << "==========" << endl << endl;
	cout << "Input a series of one-digit ints (spaces are fine), followed by a string of the following characters:" << endl;
	cout << "\tChar\tEffect" << endl;
	cout << "\tk\tpeek" << endl;
	cout << "\tp\tpop" << endl;
	cout << "\ts\tsize" << endl;
	cout << "\to\toutput stack" << endl;
	cout << "For example, \"357okopo\" without quotes." << endl;
	cout << "> ";
	string input;
	getline(cin, input);
	bool donepushing = false;
	for(int i = 0; i<input.size(); i++) {
		char c = input[i];
		if(c==' ') continue;
		if(donepushing) {
			switch(c) {
				case 'k' : cout << foo.peek() << endl; break;
				case 'p' : cout << foo.pop() << endl; break;
				case 's' : cout << foo.size() << endl; break;
				case 'o' : cout << foo << endl; break;
			}
			continue;
		} else {
			if(c=='k' || c=='p' || c=='s' || c=='o') {
				i--; donepushing = true;
				continue;					
			}
			else foo.push(c-'0');
		}
	}
	return 0;
}

