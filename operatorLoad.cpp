#include <iostream>
using namespace std;

class node{
public:
    int x,y;
    node(int a, int b){
        x=a;
        y=b;
    }
 /*   node operator+(node n){
        node temp(0,0);
        temp.x = x+n.x;
        temp.y = y+n.y;
        return temp;
    }  */
    friend node operator+(node n1, node n2);
    friend node operator+(node n1, int a);
};

node operator+(node n1,node n2){
    node temp(0,0);
    temp.x = n1.x+n2.x;
    temp.y = n1.y+n2.y;
    return temp;
}

node operator+(node n1,int a){
    node temp(0,0);
    temp.x = n1.x+a;
    temp.y = n1.y+a;
    return temp;
}

int main()
{
    node n1(3,4);
    node n2(6,7);
    node ans = n1 + n2;
    cout << ans.x << "\t" << ans.y << endl;
    ans = n1 + 10;
    cout << ans.x << "\t" << ans.y << endl;
}