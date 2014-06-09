#include <iostream>
using namespace std;

class stack{
    int top;
    int capacity;
    int * arr;
public:
    stack(int size){
        this->capacity = size;
        arr = new int[size];
        top = -1;
    }
    void push(int a);
    int pop();
};

void stack::push(int a){
    if (top+1 == capacity) {
        cout << "Stack Full\n";
        return;
    }
    arr[++top] = a;
}

int stack::pop(){
    if (top==-1) {
        cout << "Stack Empty\n";
        return NULL;
    }
    return arr[top--];
}

int main()
{
    int s;
    cout << "Enter size of stack\n";
    cin >> s;
    stack st(s);
    while(1){
     cout << "Enter your option " << endl;
    cout << " 1.Push element to the stack " << endl;
    cout << " 2.Pop from stack " << endl;
    int ch;
    cin >> ch;
    switch (ch) {
        case 1:
            cout << "Enter the element\n";
            int n;
            cin >> n;
            st.push(n);
            break;
        case 2:
            cout << st.pop() << endl;
            break;
        default:
            break;
    }
    }
    return 0;
}