#include <iostream>
#include <math.h>
using namespace std;

double clac_func(double x, double coeff[], int n)
{
    double v = 0;
    for (int i = 0; i < n; i++) {
        v += pow(x, i) * coeff[i];
    }
    return v;
}

double derive(double x, double coeff[], int n)
{
    double d = 0;
    for (int i = 1; i < n; i++) {
     d += pow(x, i-1) * coeff[i] * i;
    }
    return d;
}

int main()
{
    int n = 0;
    double x1 = 0.1, x2 = x1;
    cout << "Enter the degree of the equation" << endl;
    cin >> n;
    double c[n+1];
    cout << "Enter the coffecients for the equation of the form y = c0 + c1x + c2x ^ 2 + ..." << endl << endl;
    
    for (int i=n; i>=0; i--) {
        cout << "Enter the coefficient c" << i << " : ";
        cin >> c[i];
        cout << endl;
    }
    
    //cout << "f(x) = " << func(2, c, n+1) << endl;
    //cout << "f'(x) = " << der(2, c, n+1) << endl;
    //return 0;
    int k = 500;
    double a1,b1;
    do{
        x1 = x2;
        x2 = x1 - (clac_func(x1, c, n+1)/derive(x1, c, n+1));
        int a =(int) (x1*100000);
        a1 = (double)a/100000;
        int b =(int) (x2*100000);
        b1 = (double)b/100000;
    }while(k-- && a1!=b1);
    
    if(k>0)
    {
    cout << endl << "One of the roots is : " << x1 <<endl;
    }else{
        cout << "No roots for the equation! Try again with better approxmiate value" << endl;
    }
    cout << endl << endl;
    return 0;
}

