#include <iostream>
#include <stdlib.h>
using namespace std;

double ** get_in(double **arr,int n){
    for (int i=0; i<n; i++) {
        for (int j=0; j<n+1; j++) {
            cin >> arr[i][j];
        }
    }
    return arr;
}

void show_arr(double **arr,int n){
    for (int i=0; i<n; i++) {
        for (int j=0; j<n+1; j++) {
            if((arr[i][j]>0.00001) || (arr[i][j]<-0.00001)){
                cout << arr[i][j] << "\t";
            }else{
                cout << "0" << "\t";
            }
        }
        cout << endl;
    }
}


void process(double **arr, double *result, int n){
    
    double ratio = 0.0;
    
    for (int i=0; i<n-1; i++) {
        for (int j=i+1; j<=n-1; j++) {
            ratio = (arr[j][i]/arr[i][i]);
            for (int k=0; k<n+1; k++) {
                arr[j][k] = arr[j][k] - ratio*arr[i][k];
            }
        }
    }
    
    cout << "The formed matrix after triangularisation is: \n" << endl;
    show_arr(arr, n);
    cout << endl;
    
    result[n-1] = arr[n-1][n]/arr[n-1][n-1];
    
    for (int i = n-2; i>=0; i--) {
        double temp=arr[i][n];
        for (int j=i+1; j<=n-1; j++) {
            temp = temp-arr[i][j]*result[j];
        }
        result[i] = temp/arr[i][i];
    }
}


void show_result(double* result,int n){
    cout << "The solution by gauss elimination method:\n";
    for (int i=0; i<n; i++) {
        if((result[i]<0.00001) && (result[i]>-0.00001)){
            result[i] = 0;
        }
        cout << (char)(i+97) << " :  " <<result[i] << endl;
    }
}

int main(){
    int n;
    cout << "*****WELCOME******" << endl << "Enter the number of unknowns:" << endl;
    cin >> n;
    double **arr,result[n];
    arr = (double **)malloc(n*sizeof(*arr));
    for (int i=0; i<n+1; i++) {
        arr[i] = (double *)malloc((n+1)*sizeof(*arr[i]));
    }
    
    cout << "Equation format is: ";
    cout << "k1(a)";
    for(int i = 98;i<(97+n);i++){
        cout << " + " << "k" << i-96 << "(" <<(char)i<< ")";
    }
    cout << " = value" << endl;
    
    cout << "\n" << "a,b,c...: variables\nk1,k2,k3...: constants/coefficients\n\nEnter the coefficients and value\n\n";
    
    for(int i = 97;i<(97+n);i++){
        cout << 'k' << i-96 << "\t";
    }
    cout << "value" << endl;
    
    arr = get_in((double **)arr,n);
    process((double **)arr,result,n);
    show_result(result,n);
    return 0;
}
