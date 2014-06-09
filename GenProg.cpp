#include <iostream>
#include <cmath>
using namespace std;

class vertice{
public:
    double x,y;
};

void polyArea(vertice v[], int n){
    double area=0;
    for (int i=0; i<n; i++) {
        area += ((v[i].x)*(v[(i+1)%n].y) - (v[(i+1)%n].x)*(v[i].y))/2;
    }
    cout << "The area of the po;ygon is " << ((area>=0)?area:(-1*area)) << endl;
}

void primes(int n){
    int primes[n+1];
    for (int i=0; i<=n; i++) {
        primes[i]=1;
    }
    primes[0] = primes[1] = 0;
    for (int i=2; i<=sqrt(n); i++) {
        for (int j=i+i; j<=n; j=j+i) {
            primes[j] = 0;
        }
    }
    cout << primes[3] << endl;
    cout << "The prime numbers till n are \n";
    for (int i=0; i<=n; i++) {
        if (primes[i]==1) {
            cout << i << "\t";
        }
    }
    cout << endl;
}

void factors(int n){
    int m = n/2;
    int factors[m];
    int j=0;
    for (int i=1; i<=sqrt(n); i++) {
        if (n%i==0) {
            factors[j++] = i;
            if (i!=sqrt(n)) {
                factors[j++] = n/i;
            }
        }
    }
    factors[j] = -1;
    cout << "The factors are\n";
    for (int i=0; factors[i]!=-1; i++) {
        cout << factors[i] << "\t";
    }
    cout << endl;
}

void gcd(int a, int b){
    if (b==0) {
        cout << "The HCF of the two numbers is " << a << endl;
        return;
    }
    gcd(b,a%b);
}

void primeFactors(int n){
    for (int i=2; i<=sqrt(n); i++) {
        int ctr = 0;
        while (n%i==0) {
            ctr++;
            n/=i;
        }
        if (ctr>0) {
            cout << i << "^" << ctr << endl;
        }
    }
    if (n!=1) {
        cout << n << "^" << 1 << endl;
    }
}

int main()
{
    int ch;
    cout << "Make a choice \n";
    cout << " 1.Area of Polygon\n";
    cout << " 2.Factors of a number\n";
    cout << " 3.Prime numbers till n\n";
    cout << " 4.HCF of two numbers\n";
    cout << " 5.Prime factorisation of a number\n";
    cin >> ch;
    switch (ch) {
        case 1:
        {
            int n;
            cout << "Enter the number of vertices\n";
            cin >> n;
            vertice v[n];
            cout << "Enter the coordinates of vertices\n";
            for (int i=0; i<n; i++) {
                cin >> v[i].x;
                cin >> v[i].y;
            }
            polyArea(v,n);
        }
            break;
        case 2:
        {
            int n;
            cout << "Enter the number\n";
            cin >> n;
            factors(n);
        }
            break;
        case 3:
        {
            int n;
            cout << "Enter n\n";
            cin >> n;
            primes(n);
        }
            break;
        case 4:
        {
            int a,b;
            cout << "Enter the two numbers a and b\n";
            cin >> a >> b;
            gcd(a, b);
        }
            break;
        case 5:
        {
            int n;
            cout << "Enter n\n";
            cin >>n;
            primeFactors(n);
        }
            break;
        default:
            break;
    }
    return 0;
}

