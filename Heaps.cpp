#include <iostream>
using namespace std;

struct Heap{
    int *array;
    int count;
    int capacity;
    int heap_type;      //0 for min, 1 for max
};

void swap(int *a, int *b){
    int temp;
    temp = *a;
    *b = *a;
    *a = temp;
}

struct Heap* createHeap(int capacity, int heaptype = 0){
    struct Heap* h = (struct Heap*)malloc(sizeof(struct Heap));
    if (!h) {
        cout << "Memory error!\n";
        return NULL;
    }
    h->heap_type = heaptype;
    h->count=0;
    h->capacity = capacity;
    h->array = (int *)malloc(h->capacity*sizeof(int));
    if (!h->array) {
        cout << "Memory error";
        return NULL;
    }
    return h;
}

int parent(struct Heap*h, int pos){
    if (pos<=0 || pos>=h->count) {
        return -1;
    }
    int parent = (pos - 1)/2;
    
    return parent;
}

int LeftChild(struct Heap*h, int pos){
    int left = 2*pos + 1;
    if (left>=h->count) {
        return -1;
    }
    return left;
}

int RightChild(struct Heap*h, int pos){
    int right = 2*pos + 2;
    if (right>=h->count) {
        return -1;
    }
    return right;
}

int GetMin(Heap *h){
    if (h->count==0) {
        return -1;
    }
    return h->array[0];
}

void ResizeHeap(struct Heap **h1){
    struct Heap* h = (*h1);
    int *arrOld;
    arrOld = (int *)malloc(h->capacity*sizeof(int));
    for (int i=0; i<h->capacity; i++) {
        arrOld[i] = h->array[i];
    }
    h->array = (int *)malloc(2*h->capacity*sizeof(int));
    if (!h->array) {
        cout << "Memory Error\n";
        return;
    }
    for (int i=0; i<h->capacity; i++) {
        h->array[i] = arrOld[i];
    }
    h->capacity *= 2;
    free((int *)arrOld);
}

void percolateDown(struct Heap **h1, int pos){
    struct Heap* h = (*h1);
    int l=0,r=0,min,temp;
    
    l = LeftChild(h, pos);
    r = RightChild(h, pos);
    
    if (l!=-1 && (h->array[l] < h->array[pos])) {
        min = l;
    }else{
        min = pos;
    }
    
    if (r!=-1 && (h->array[r] < h->array[min])) {
        min = r;
    }
    
    if (min != pos) {
        
        temp = h->array[pos];
        h->array[pos] = h->array[min];
        h->array[min] = temp;
        percolateDown(&h, min);
    }
}

int deleteMin(struct Heap **h1){
    struct Heap* h = (*h1);
    int data;
    if (h->count==0) {
        return -1;
    }
    data = h->array[0];
    h->array[0] = h->array[h->count-1];
    h->count--;
    percolateDown(&h, 0);
    return data;
}

void Insert(struct Heap **h1, int data){
    struct Heap *h = (*h1);
    if (h->count == h->capacity) {
        ResizeHeap(h1);
    }
    int pos = h->count;
    while (h->array[(pos - 1)/2] > data && pos>0) {
        h->array[pos] = h->array[(pos - 1)/2];
        pos = (pos-1)/2;
    }
    h->array[pos] = data;
    h->count++;
}

void BuildHeap(struct Heap **h1, int A[], int n){   //O(n) sum of heights
    struct Heap *h=(*h1);
    if (!h) {
        return;
    }
    while (n >= h->capacity) {
        ResizeHeap(h1);
    }
        for (int i=0; i<n; i++) {
            h->array[i] = A[i];
        }
        h->count = n;
        for (int i=(n-1)/2; i>=0; i--) {
            percolateDown(&h, i);
        }
}

void HeapSort(struct Heap *h){
    int n = h->count;
    int n1=n;
    while(n>0) {
        int temp = h->array[n-1];
        h->array[n-1] = h->array[0];
        h->array[0] = temp;
        n--;
        h->count--;
        percolateDown(&h, 0);
    }
    h->count = n1;
}

int main()
{
    cout << "Enter heap size\n";
    int n;
    cin >> n;
    struct Heap* h = createHeap(n);
   int A[n];
    for (int i=0; i<n; i++) {
        cin >> A[i];
        Insert(&h, A[i]);
    }
    //BuildHeap(&h, (int *)A, n);
    
    for (int i=0; i<h->count; i++) {
        cout << h->array[i] << "\t";
    }
    
    HeapSort(h);
    
    cout << endl;
    
    for (int i=0; i<h->count; i++) {
        cout << h->array[i] << "\t";
    }
    
    return 0;
}

