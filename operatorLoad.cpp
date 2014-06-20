#include <iostream>
using namespace std;

class node{
public:
    int x,y;
    node(int a, int b){
        x=a;
        y=b;
    }
    node operator+(node n){
        node temp(0,0);
        temp.x = x+n.x;
        temp.y = y+n.y;
        return temp;
    }
};

int main()
{
    node n1(3,4);
    node n2(6,7);
    node ans = n1 + n2;
    cout << ans.x << "\t" << ans.y << endl;
}