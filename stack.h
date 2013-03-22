#define STACKH
#include <iostream>
#include <sstream>
using namespace std;

#define DEFAULT_ADJUST 5

template <class T>
class stack {
	T *array;
	int top;
	public:
		stack<T>() {
			array = new T[DEFAULT_ADJUST];
			top = -1;
		}
		void push(T item);
		T pop();
		T peek();
        const char* str();
		int size();
		int &operator[](const int index) { return array[index]; }
	private:
		int get_true_size();
		void adjust();
		void adjust(int amt);
};

template <class T>
void stack<T>::push(T item) {
	if(top==get_true_size()-1) adjust();
	array[++top] = item;
}

template <class T>
T stack<T>::peek() {
	if(stack<T>::size()==0) return 0;
	return stack<T>::array[stack<T>::size()-1];
}

template <class T>
T stack<T>::pop() {
	if(top==-1) return 0;
	T out = stack<T>::array[stack<T>::size()-1];
	stack<T>::top--;
	if(stack<T>::get_true_size()-top>DEFAULT_ADJUST) stack<T>::adjust(-DEFAULT_ADJUST);
	return out;
}

template <class T>
int stack<T>::get_true_size() {
	return sizeof(stack<T>::array)/sizeof(stack<T>::array[0]);
}

template <class T>
int stack<T>::size() { return stack<T>::top+1; }

template <class T>
void stack<T>::adjust() { adjust(DEFAULT_ADJUST); }

template <class T>
void stack<T>::adjust(const int amt) {
	T *newarr = new T[stack<T>::get_true_size()+amt];
	for(int i=0; i<min(get_true_size(),get_true_size()+amt); i++) {
		newarr[i] = stack<T>::array[i];
	}
	stack<T>::array = newarr;
}

template <class T>
std::ostream &operator<<(std::ostream &strm, stack<T> stck) {
    strm << stck.str();
}

template <class T>
const char* stack<T>::str() {
    stringstream strm(""); 
    strm << "[";
	for(int i=0; i<stack<T>::size(); i++) {
		strm << stack<T>::array[i] << (i<stack<T>::size()-1 ? ", " : "");
	}
	strm << "]";
	strm << '\0';
    string out;
    getline(strm,out);
    return out.c_str();
}
