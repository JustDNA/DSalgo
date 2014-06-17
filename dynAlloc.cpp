#include <iostream>
using namespace std;

void display(int ** a){
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            cout << a[i][j] << "\t";
        }
        cout << endl;
    }
}

int main()
{
    int ** arr;
    //*arr = new int[5];
    //for (int i=0; i<5; i++) {
    //    arr[i] = new int[5];
    // }
    arr = (int **)malloc(5*sizeof(*arr));
    for (int i=0; i<5+1; i++) {
        arr[i] = (int *)malloc((5+1)*sizeof(*arr[i]));
    }
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            arr[i][j] = i+j;
        }
    }
    display(arr);
    for (int i=0; i<5; i++) {
        free(arr[i]);
    }
    return 0;
}