#include <iostream>
using namespace std;

void swap(int *a,int *b){
    int t;
    t=*a;
    *a=*b;
    *b=t;
}

void bubble(int A[], int n){            // O(n^2) O(n) O(1) Stable
    int swapped=1;
    for (int i=n-1; i>=0 && swapped; i--) {           // n-1 passes
        swapped = 0;
        for (int j=0; j<i; j++) {
            if (A[j] > A[j+1]) {
                swap(&A[j], &A[j+1]);
                swapped = 1;
            }
        }
    }
}

void selection(int A[], int n){  // O(n^2) O(n^2) O(1) Stability depends on implementation(Unstable here)
    int min;
    for (int i=0; i<n-1; i++) {                 // <B> <b> <a> <c>
        min=i;                                  // <a> <b> <B> <c>       That's y unstable
        for (int j=i+1; j<n; j++) {             // Can be made stable by inserting and pushing back
            if (A[j]<A[min]) {                  // Linked lists can be used for that
                min = j;
            }
        }
        swap(&A[min], &A[i]);
    }
}

void insertion(int A[], int n){                 // O(n^2) O(n) O(1) Stable
    int temp;                                   // actually O(n+d) where d=no of inversions
    for (int i=1; i<n; i++) {
        int j=i-1;
        temp = A[i];
        while (A[j]>temp && j>=0) {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = temp;
    }
}

void shell(int A[], int n){                     // O(n^2) O(nlog(n)) O(1) Stable
    int gap, temp;                              // Avg case depends on gap
    for (gap = 1; gap<(n/9); gap = gap*3 + 1);
    for (; gap>0; gap=gap/3) {
        cout << gap << endl;
        for (int i=gap; i<n; i++) {
            int j=i-gap;
            temp = A[i];
            while (A[j]>temp && j>=0) {
                A[j+gap] = A[j];
                j-=gap;
            }
            A[j+gap] = temp;
        }
    }
}

void merge(int A[], int left, int mid, int right, int temp[]){
    int l=left;
    int r=mid;
    int i=left;
    while (l<mid && r<=right) {
        if (A[l]<A[r]) {
            temp[i] = A[l];
            l++;
            i++;
        }else{
            temp[i] = A[r];
            r++;
            i++;
        }
    }
        while (l<mid) {         // copy left over elements if any
            temp[i] = A[l];
            l++;i++;
        }
        while (r<=right) {      // copy left over elements if any
            temp[i] = A[r];
            r++;i++;
        }
    for (int i=left; i<=right; i++) {
        A[i] = temp[i];
    }
}

void mergeSort(int A[], int n, int left, int right, int temp[]){ // O(nlog(n)) O(nlog(n)) O(n) Stable
    int mid;
    if (right>left) {
        mid = (left+right)/2;
        mergeSort(A,n,left,mid,temp);
        mergeSort(A,n,mid+1,right,temp);
        merge(A,left,mid+1,right,temp);
    }
}

// Heap sort O(n) to build heap and O(nlog(n)) for heap sort. i.e, After building heap remove one by one from heap ; Usntable ; O(1) space

int partition(int A[], int low, int high){
    int pivot = low + rand()%(high - low);
    swap(&A[pivot], &A[low]);
    int pivEle = A[low];
    int i=low,j=high;
    while(j>i)
    {
        while (A[j]>pivEle) {
                j--;
            }
        while (A[i]<=pivEle) {
                i++;
            }
        if (j>i) {
            swap(&A[i], &A[j]);
        }
    }
    A[low] = A[j];
    A[j] = pivEle;              // At the end, j will be just to the left of i
    return j;
}

void quick(int A[], int low, int high){
    int pivot;             // O(nlog(n)) O(n^2) O(log(n))->for stack ; Stability depends on pivot handling
    if (low<high) {
        pivot = partition(A, low, high);
        quick(A, low, pivot-1);
        quick(A, pivot+1, high);
    }
}

// Tree sort O(nlog(n)) O(n^2) O(n) Stability depends

void count(int A[], int n){     // O(n) iff max = O(n)
    int min = A[0];
    int max = A[0];
    for (int i=0; i<n; i++) {
        if (A[i] < min) {
            min = A[i];
        }
        if (A[i] > max) {
            max = A[i];
        }
    }
    int scale = -1*min;
    for (int i=0; i<n; i++) {
        A[i] = A[i] + scale;
    }
    max = max+scale+1;
    int B[n],C[max];
    for (int i=0; i<max; i++) {
        C[i] = 0;
    }
    for (int i=0; i<n; i++) {
        B[i] = 0;
    }
    for (int i=0; i<n; i++) {
        C[A[i]]++;
    }
    for (int i=1; i<max; i++) {
        C[i] = C[i] + C[i-1];
    }
    for (int i=n-1; i>=0; i--) {
        B[C[A[i]]-1] = A[i];
        C[A[i]]--;
    }
    for (int i=0; i<n; i++) {
        A[i] = B[i] - scale;
    }

}

void radix(int A[], int n){     // O(n)
    int min = A[0];
    int max = A[0];
    for (int i=0; i<n; i++) {
        if (A[i] < min) {
            min = A[i];
        }
        if (A[i] > max) {
            max = A[i];
        }
    }
    int scale = -1*min;
    for (int i=0; i<n; i++) {
        A[i] = A[i] + scale;
    }
    max = max+scale;
    int digits=0;
    while (max/10) {
        digits++;
        max/=10;
    }
    digits++;
    
    int B[n],C[10];
    
    for (int d=1; d<=digits; d++) {
        int div;
        div=1;
        for (int i=1; i<d; i++) {
            div*=10;
        }
    for (int i=0; i<10; i++) {
        C[i] = 0;
    }
    for (int i=0; i<n; i++) {
        B[i] = 0;
    }
    for (int i=0; i<n; i++) {
        C[(A[i]/div)%10]++;
    }
    for (int i=1; i<10; i++) {
        C[i] = C[i] + C[i-1];
    }
    for (int i=n-1; i>=0; i--) {
        B[C[(A[i]/div)%10]-1] = A[i];
        C[(A[i]/div)%10]--;
    }
   
    for (int i=0; i<n; i++) {
        A[i] = B[i];
    }
        
    }
    for (int i=0; i<n; i++) {
        A[i] = A[i] - scale;
    }
    
}

int main()
{
    int n;
    cout << "Enter the size of input array \n";
    cin >> n;
    int *A;
    A = new int[n];
    cout << "Enter the elements \n" ;
    for (int i=0; i<n; i++) {
        cin >> A[i];
    }
    int ch;
    cout << "Enter your choice\n";
    cout << " 1. Bubble sort\n";
    cout << " 2. Selection sort\n";
    cout << " 3. Insertion sort\n";
    cout << " 4. Shell sort\n";
    cout << " 5. Merge sort\n";
    cout << " 6. Quick sort\n";
    cout << " 7. Count sort\n";
    cout << " 8. Radix sort\n";
    cin >> ch;
    switch (ch) {
        case 1:
            bubble(A,n);
            break;
        case 2:
            selection(A, n);
            break;
        case 3:
            insertion(A,n);
            break;
        case 4:
            shell(A,n);
            break;
        case 5:
        {
            int temp[n];
            mergeSort(A,n,0,n-1,temp);
            free(temp);
        }
            break;
        case 6:
            quick(A, 0, n-1);
            break;
        case 7:
            count(A,n);
            break;
        case 8:
            radix(A,n);
            break;
        default:
            break;
    }
    cout << "The sorted elements are \n" ;
    for (int i=0; i<n; i++) {
        cout << A[i] << "\t";
    }
    free(A);
    cout << endl;
    return 0;
}

