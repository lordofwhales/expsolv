#define NEWSTACKH
#include <iostream>
#include <sstream>
using namespace std;


template <class T>
class stack {
    struct node {
        T data;
        node *prev;
        node *next;
    };

    node *top;
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
};

template <class T>
void stack<T>::push(T item) {
    if(stack<T>::top==NULL) {
        top = new node;
        top -> data = item;
        return;
    } 
    node newnode = new node;
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
    return stack<T>::top -> data;
}

template <class T>
const char* stack<T>::str();
    node test = stack<T>::top;
    stringstream item("");
    string out("]");
    while(test->prev!=NULL) {
        item.clear();
        item << test -> data;
        out = string(", ") + item + out;
        test = test-> prev;
    } item << test -> data;
    out = string("[") + item + out;
    return out.c_str();
}
