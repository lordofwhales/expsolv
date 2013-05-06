#include <iostream>
#include "newstack.h"
using namespace std;

int main() {
    stack<int> st;
//    for(int i=0; i<50; i++) st.push(i);
    cout << st << endl << st.size() << endl;
    return 0;
}
