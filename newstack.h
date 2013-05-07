#define STACKH
#include <iostream>
#include <sstream>
using namespace std;

template <class T>
struct node {
    T data;
    node *prev;
    node *next;
};
template <class T>
class stack {
	public:
		stack<T>() {
            top = NULL;
            t_size=0;
		}
		void push(T item);
        void clear();
		T pop();
		T peek();
        const char* str();
		int size();
        int operator[](const int index); 
    private: 
        node<T> *top;
        int t_size;
};

template <class T>
int stack<T>::operator[](const int index) {
    cout << "in operator" << endl;
    node<T> *test = stack<T>::top;
    if(test==NULL) return 0;
    for(int n=0; n<stack<T>::size()-index; n++) test = test -> prev;
    cout << "out operator" << endl;
    return test -> data;
}
template <class T>
int stack<T>::size() {
    cout<<"in size/outsize" << endl;
    return stack<T>::t_size;
}
template <class T>
void stack<T>::push(T item) {
    cout << "in push" << endl;
    if(stack<T>::top==NULL) {
        stack<T>::top = new node<T>;
        stack<T>::top -> data = item;
        stack<T>::t_size+=1;
        cout << "out push" << endl;
        return;
    } 
    node<T> *newnode = new node<T>;
    newnode -> prev = stack<T>::top;
    newnode -> data = item;
    stack<T>::top -> next = newnode;
    stack<T>::top = stack<T>::top->next;
    stack<T>::t_size += 1;
    cout << "Pu" << stack<T>::t_size << endl;
    cout << "out puush" << endl;
}

template <class T>
void stack<T>::clear() {
    cout << "in clear/outclear" << endl;
    stack<T>::top = NULL;
}

template <class T>
T stack<T>::pop() {
    cout << "in pop" << endl;
    if(stack<T>::top==NULL) return 0;
    T out = stack<T>::top -> data;
    stack<T>::top = stack<T>::top -> prev;
    if(stack<T>::top != NULL) stack<T>::top -> next = NULL;
    stack<T>::t_size -= 1;
    cout << "Po" << stack<T>::t_size << "||" << out << endl;
    cout << "out pop" << endl;
    return out;
}

template <class T>
T stack<T>::peek() {
    cout << "in peek" << endl;
    if(stack<T>::top==NULL) return 0;
    cout << "outpeek" << endl;
    return stack<T>::top -> data;
}

template <class T>
const char* stack<T>::str() {
    cout << "instr" << endl;
    node<T> *test = stack<T>::top;
    cout << "*1" << endl;
    if(test==NULL) {cout << "outstr" << endl;return string("[]").c_str();}
    cout << "*2" << endl;
    string out("]");
    cout << "*3" << endl;
    while(test->prev!=NULL) {
        cout << "*L" << test -> prev << endl;
        stringstream item("");
        item << test -> data;
        out = string(", ") + item.str() + out;
        test = test -> prev;
    }
    cout << "*8" << endl;
    stringstream item("");
    cout << "*9" << endl;
    item << test -> data;
    cout << "*a" << endl;
    out = string("[") + item.str() + out;
    cout << "*b" << endl;
    cout << "outstrr" << endl;
    cout << "*c" << endl;
    return out.c_str();
}

template <class T>
std::ostream &operator<<(std::ostream &strm, stack<T> stck) {
    strm << stck.str();
}
