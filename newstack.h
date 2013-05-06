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
};

template <class T>
int stack<T>::operator[](const int index) {
    node<T> *test = stack<T>::top;
    if(test==NULL) return 0;
    for(int n=0; n<stack<T>::size()-index; n++) test = test -> prev;
    return test -> data;
}
template <class T>
int stack<T>::size() {
    node<T> *test = stack<T>::top;
    if(test==NULL) return 0;
    int n=1;
    while(test -> prev != NULL) {
        test = test -> prev;
        n++;
    }
    return n;
}
template <class T>
void stack<T>::push(T item) {
    if(stack<T>::top==NULL) {
        top = new node<T>;
        top -> data = item;
        return;
    } 
    node<T> *newnode = new node<T>;
    newnode -> prev = stack<T>::top;
    newnode -> data = item;
    stack<T>::top -> next = newnode;
    stack<T>::top = stack<T>::top->next;
}

template <class T>
void stack<T>::clear() {
    stack<T>::top = NULL;
}

template <class T>
T stack<T>::pop() {
    T out = stack<T>::top -> data;
    stack<T>::top = stack<T>::top -> prev;
    stack<T>::top -> next = NULL;
    return out;
}

template <class T>
T stack<T>::peek() {
    if(stack<T>::top==NULL) return NULL;
    return stack<T>::top -> data;
}

template <class T>
const char* stack<T>::str() {
    node<T> *test = stack<T>::top;
    if(test==NULL) return string("[]").c_str();
    string out("]");
    while(test->prev!=NULL) {
        stringstream item("");
        item << test -> data;
        out = string(", ") + item.str() + out;
        test = test -> prev;
    } 
    stringstream item("");
    item << test -> data;
    out = string("[") + item.str() + out;
    return out.c_str();
}

template <class T>
std::ostream &operator<<(std::ostream &strm, stack<T> stck) {
    strm << stck.str();
}
