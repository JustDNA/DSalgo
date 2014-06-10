#include <iostream>
using namespace std;

double summationx(double **x,int c, int m){
    double sum = 0.0;
    for (int i=0; i<m; i++) {
        sum += x[i][c];
    }
    return sum;
}
double summationx2(double **x,int c1, int c2, int m){
    double sum = 0.0;
    for (int i=0; i<m; i++) {
        sum += x[i][c1] * x[i][c2];
    }
    return sum;
}
double summationy(double *y, int m){
    double sum = 0.0;
    for (int i=0; i<m; i++) {
        sum += y[i];
    }
    return sum;
}
double summationy2(double *y, double **x, int c, int m){
    double sum = 0.0;
    for (int i=0; i<m; i++) {
        sum += y[i] * x[i][c];
    }
    return sum;
}

void generate_array(double **array, double **x, double *y, int n, int m){
    array[0][0] = m;
    array[0][n] = summationy(y, m);
    for(int i=1; i<n; i++){
        array[i][0] = array[0][i] = summationx(x,i-1,m);
    }
    for (int i=1; i<n; i++) {
        for (int j=1; j<n; j++) {
            array[i][j] = summationx2(x, i-1, j-1, m);
        }
    }
    for(int i=1; i<n; i++){
        array[i][n] = summationy2(y, x, i-1, m);
    }
}


void matrix_transform(double **array, double *result, int n){
    
    double ratio = 0.0;
    
    for (int i=n-1; i>0; i--) {
        for (int j=i-1; j>=0; j--) {
            ratio = (array[j][i]/array[i][i]);
            for (int k=0; k<n+1; k++) {
                array[j][k] = array[j][k] - ratio*array[i][k];
            }
        }
    }
    
    for (int i=0; i<n-1; i++) {
        for (int j=i+1; j<=n-1; j++) {
            ratio = (array[j][i]/array[i][i]);
            for (int k=0; k<n+1; k++) {
                array[j][k] = array[j][k] - ratio*array[i][k];
            }
        }
    }
    
    for (int i=0; i<n; i++) {
        result[i] = array[i][n]/array[i][i];
    }
}


void display_result(double* result,int n){
    for (int i=0; i<n; i++) {
        cout << "Root " << i << " :  " <<result[i] << endl;
    }
}

int main(){
    int n,ch,m;
    cout << "HELLO" << endl << "Choose:\n1.Linear Regression\n2.Non Linear Regression" << endl;
    cin >> ch;
    switch (ch) {
        case 1:
            n=2;
            break;
        case 2:
            cout << "Give the number of independant variables:" << endl;
            cin >> n;
            n++;
            break;
            
        default:
            cout << "Give the number of independant variables:" << endl;
            cin >> n;
            n++;
            break;
    }
    double **array,result[n];
    array = (double **)malloc(n*sizeof(*array));
    for (int i=0; i<n+1; i++) {
        array[i] = (double *)malloc((n+1)*sizeof(*array[i]));
    }
    
    cout << "Enter the size of the Observation table" << endl;
    cin >> m;
    
    double **x,y[m];
    
    x = (double **)malloc(m*sizeof(*x));
    for (int i=0; i<m; i++) {
        x[i] = (double *)malloc((n-1)*sizeof(*x[i]));
    }
    
    for (int i=0; i < n-1; i++){
        cout << "x" << i+1 << "\t";
    }
    cout << "y" << endl;
    
    for (int i=0; i<m; i++) {
        for (int j=0; j<n-1; j++) {
            cin >> x[i][j];
        }
        cin >> y[i];
    }
    
    cout << endl;
    cout << endl;
    
    generate_array(array,x,y,n,m);
   matrix_transform((double **)array,result,n);
    cout << "\n\nThe equation of the best fit line for given observations is:\n\ty = ";
    cout << result[0];
    for (int i=1; i<n; i++) {
        if(result[i]>=0){
            cout << "+";
        }
        cout << " " << result[i] << "(x" << i << ")";
    }
    cout << endl << endl;
    return 0;
    }