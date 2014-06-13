#include <iostream>
#include <vector>
#include <list>
#include <map>
using namespace std;

void shuffle2(int arr[],int size,int n){
    if(size<0){
        return;
    }
    if(size == 0){
        for (int i=0; i<n; i++) {
            cout << arr[i];
        }
        cout << endl;
        return;
    }
    
    arr[size-1] = 0;
    shuffle2(arr,size-1,n);
    arr[size-1] =1;
    shuffle2(arr,size-1,n);
}

bool isSetSum(int set[], int n, int sum){
    if(sum == 0)
    {
        return true;
    }
    if(n==0 && sum!=0)
    {
        return false;
    }
    if(set[n-1]>sum)
    {
        return isSetSum(set, n-1, sum);
    }
    
    return (isSetSum(set, n-1, sum) || isSetSum(set, n-1, sum-set[n-1]));
    return false;
}


void showSubSet(int set[], int n, int m, int bin[]){
    if(n == 0)
    {
        cout << endl;
        for (int i=0; i<m; i++) {
            if(bin[i] == 1){
                cout << set[i] << "\t";
            }
        }
        return;
    }
    
    bin[n-1] = 0;
    showSubSet(set, n-1, m, bin);
    bin[n-1] = 1;
    showSubSet(set, n-1, m, bin);
    return;
}

void showSetSum(int set[], int n, int m, int sum, int bin[]){
    if((n == 0) && (sum == 0))
    {
        cout << endl;
        for (int i=0; i<m; i++) {
            if(bin[i] == 1){
                cout << set[i] << "\t";
            }
        }
        return;
    }
    if(n==0 && sum!=0)
    {
        return;
    }
    
    bin[n-1] = 0;
    showSetSum(set, n-1, m, sum, bin);
    bin[n-1] = 1;
    showSetSum(set, n-1, m, sum-set[n-1], bin);
    return;
}

void swap(char *a, char *b){
    char temp;
    temp=*a;*a=*b;*b=temp;
}

void permute(char *a, int n, int i)
{
    int j;
    if(n==i){
        cout << a << endl;
        return;
    }
    for (j=i; j<n; j++) {
        swap(a[i],a[j]);
        permute(a, n, i+1);
        swap(a[i],a[j]);
    }
}

void paran(char arr[], int pos, int n, int o, int c){
    if((pos == n) && (o == c)){
        for (int i=0; i<n; i++) {
            cout << arr[i];
        }
        cout << endl;
        return;
    }
    if(o<(n/2)){
        o++;
        arr[pos] = '(';
        paran(arr, pos+1, n, o, c);
        o--;
    }
    if(o>c){
        c++;
        arr[pos] = ')';
        paran(arr, pos+1, n, o, c);
    }
}

int steps(int n){
    if(n<0){
        return 0;
    }
    if(n == 0){
        return 1;
    }
    return (steps(n-1) + steps(n-2) + steps(n-3));
}

int stepsUtilDP(int n,int arr[]){
    
    if(n<0){
        return 0;
    }
    if(n == 0){
        return 1;
    }
    if (arr[n]!=0) {
        return arr[n];
    }
    arr[n] = stepsUtilDP(n-1,arr) + stepsUtilDP(n-2,arr) + stepsUtilDP(n-3,arr);
    return arr[n];
}

int stepsDP(int n){
    n++;
    int arr[n];
    for (int i=0; i<n; i++) {
        arr[i]=0;
    }
    return stepsUtilDP(n-1, arr);
}

bool findWay(int **mat, int **path,int i, int j, int x, int y, int len){
    if( (i>=x) || (i<0) || (j>=y) || (j<0) || ((len) > x*y)){
        return false;
    }
    if((i==(x-1))&&(j==(y-1))){
        cout << len << endl;
        return true;
    }
    if(mat[i][j]){
        path[i][j]=0;
        path[i][j] = findWay(mat, path, i+1, j, x, y, len+1);
        if(!path[i][j]){
            path[i][j] = findWay(mat, path, i, j+1, x, y, len+1);
        }
        if(!path[i][j]){
            //         path[i][j] = findWay(mat, path, i-1, j, x, y, len+1);
        }
        if(!path[i][j]){
            //         path[i][j] = findWay(mat, path, i, j-1, x, y, len+1);
        }
        return(path[i][j]);
    }
    else{
        path[i][j]=0;
        return false;
    }
}

bool allPath(int **mat, int **path,int i, int j, int x, int y, int len, int cost, int **s){
    if( (i>=x) || (i<0) || (j>=y) || (j<0) ){
        return false;
    }
    static int sh=1000;
    if((i==(x-1))&&(j==(y-1))){
        for (int k=0; k<len; k++) {
            cout << "(" << path[k][0] << "," << path[k][1] << ")" << "\t";
        }
        cost = cost + mat[i][j];
        if(cost<=sh){
            int t;
            for (t=0; t<len; t++) {
                s[t][0] = path[t][0];
                s[t][1] = path[t][1];
                sh = cost;
            }
            s[t][0] = sh;
        }
        cout << cost << endl;
        return true;
    }
    if(mat[i][j])
    {
        bool found = false;
        
        path[len][0] = i+1;
        path[len][1] = j;
        
        
        found = allPath(mat, path, i+1, j, x, y, len+1, cost+mat[i][j], s);
        
        
        path[len][0] = i;
        path[len][1] = j+1;
        
        found = allPath(mat, path, i, j+1, x, y, len+1, cost+mat[i][j], s);
        
        return found;
    }
    else{
        return false;
    }
}

void partUtil(int n, list<int> v){
    if(n<0){
        return;
    }
    if(n==0){
        v.push_back(0);
        v.sort();
        list<int>::iterator itr;
        for (itr=v.begin(); itr!=v.end(); itr++) {
            cout << *itr << "\t";
        }
        cout << endl;
        return;
    }
    for (int i=1; i<=n; i++) {
        v.push_back(i);
        partUtil(n-i,v);
        v.pop_back();
    }
    return;
}

void partition(int n){
    list<int> v;
    partUtil(n,v);
}

void partitionProper(int n){
    int p[n];
    int k = 0;
    p[k] = n;
    while (1) {
        for (int i=0; i<k+1; i++) {
            cout << p[i] << " ";
        }
        cout << endl;
        int rem = 0;
        while (k>=0 && p[k]==1) {
            rem+=p[k];
            k--;
        }
        if (k<0) {
            return;
        }
        p[k]--;
        rem++;
        while (rem>p[k]) {
            p[k+1]=p[k];
            rem=rem-p[k];
            k++;
        }
        p[k+1]=rem;
        k++;
    }
}

/* LOGIC: geeksforgeeks.org
 We are given current partition in p[] and its size. We need to update p[] to store next partition. Values in p[] must be sorted in non-increasing order.
 
 1) Find the rightmost non-one value in p[] and store the count of 1′s encountered before a non-one value in a variable rem_val (It indicates sum of values on right side to be updated). Let the index of non-one value be k.
 
 2) Decrease the value of p[k] by 1 and increase rem_val by 1. Now there may be two cases:
 a) If p[k] is more than or equal to rem_val. This is a simple case (we have the sorted order in new partition). Put rem_val at p[k+1] and p[0...k+1] is our new partition.
 b) Else (This is a interesting case, take initial p[] as {3, 1, 1, 1}, p[k] is decreased from 3 to 2, rem_val is increased from 3 to 4, the next partition should be {2, 2, 2}).
 Copy p[k] to next position, increment k and reduce count by p[k] while p[k] is less than rem_val. Finally, put rem_val at p[k+1] and p[0...k+1] is our new partition. This step is like dividing rem_val in terms of p[k] (4 is divided in 2′s).
 */

void basinSizeDFS(int **region, int *size, int x, int y, int i, int j, int val, int **visited){
    if(region[i][j]!=val || i>x || j>y || i<0 || j<0){
        return;
    }
    visited[i][j]=1;
    
    (*size)++;
    if(i+1<x){
        if (!visited[i+1][j]) {
            basinSizeDFS(region, size, x, y, i+1, j, val, visited);
        }
    }
    if(j+1<y){
        if (!visited[i][j+1]) {
            basinSizeDFS(region, size, x, y, i, j+1, val, visited);
        }
    }
    if(i-1>=0){
        if (!visited[i-1][j]) {
            basinSizeDFS(region, size, x, y, i-1, j, val, visited);
        }
    }
    if(j-1>=0){
        if (!visited[i][j-1]) {
            basinSizeDFS(region, size, x, y, i, j-1, val, visited);
        }
    }
}

class point{
    int x,y;
public:
    point(int a, int b){
        this->x=a;this->y=b;
    }
    int getx(){
        return x;
    }
    int gety(){
        return y;
    }
};

int basinSizeBFS(int **region, int **visited, int x, int y, int i, int j){
    if(i>x || j>y || i<0 || j<0){
        return 0;
    }
    int val = region[i][j];
    int size=0;
    visited[i][j]=1;
    size++;
    list<point> q;
    point p(i,j);
    q.push_back(p);
    while (!q.empty()) {
        point p = q.front();
        q.pop_front();
        i=p.getx();
        j=p.gety();
        if (i+1<x) {
            if (!visited[i+1][j] && region[i+1][j]==val) {
                size++;
                visited[i+1][j]=1;
                point p(i+1,j);
                q.push_back(p);
            }
        }
        if (j+1<y) {
            if (!visited[i][j+1] && region[i][j+1]==val) {
                size++;
                visited[i][j+1]=1;
                point p(i,j+1);
                q.push_back(p);
            }
        }
        if (i-1>=0) {
            if (!visited[i-1][j] && region[i-1][j]==val) {
                size++;
                visited[i-1][j]=1;
                point p(i-1,j);
                q.push_back(p);
            }
        }
        if (j-1>=0) {
            if (!visited[i][j-1] && region[i][j-1]==val) {
                size++;
                visited[i][j-1]=1;
                point p(i,j-1);
                q.push_back(p);
            }
        }
    }
    
    return size;
}

point move(int x, int y, int i){
    switch (i) {
        case 1:
            x=x+2;y++;
            break;
        case 2:
            y=y+2;x--;
            break;
        case 3:
            x=x-2;y--;
            break;
        case 4:
            y=y-2;x++;
            break;
        case 5:
            x=x+2;y--;
            break;
        case 6:
            y=y+2;x++;
            break;
        case 7:
            x=x-2;y++;
            break;
        case 8:
            y=y-2;x--;
            break;
            
        default:
            break;
    }
    point p(x,y);
    return p;
}

bool tour(int board[8][8],point posNew,int step){
    int x = posNew.getx();
    int y = posNew.gety();
    
    if (step==64) {
        return true;
    }
    bool result;
    for (int k=0; k<8; k++) {
        point p = move(x,y,k+1);
        int x1,y1;
        x1 = p.getx();
        y1 = p.gety();
        if (x1<8 && x1>=0 && y1<8 && y1>=0 && board[x1][y1]==-1) {
            board[x1][y1] = step;
            result = tour(board, p, step+1);
            if (result) {
                return true;
            }else{
                board[x1][y1]=-1;
            }
        }
    }
    return false;
}

void solveKtour(){
    int board[8][8];
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            board[i][j]=-1;
        }
    }
    point position(0,0);
    board[0][0]=0;
    bool result = tour(board, position, 1);
    if (result) {
        for (int i=0; i<8; i++) {
            for (int j=0; j<8; j++) {
                cout << board[i][j] << "\t";
            }
            cout << endl;
        }
    }
}

bool Qsafe(int **board, int i, int j, int n){
    
    if (board[i][j]==1) {
        return false;
    }
    for (int x=0; x<n ; x++) {
        if (board[i][x]==1) {
            return false;
            
        }
        if (board[x][j]==1) {
            return false;
        }
    }
    int x,y;
    for (x=i+1,y=j+1; x>=0 && y>=0 && x<n && y<n; x++,y++) {
        if (board[x][y]==1) {
            return false;
        }
    }
    for (x=i-1,y=j-1; x>=0 && y>=0 && x<n && y<n; x--,y--) {
        if (board[x][y]==1) {
            return false;
        }
    }
    for (x=i-1,y=j+1; x>=0 && y>=0 && x<n && y<n; x--,y++) {
        if (board[x][y]==1) {
            return false;
        }
    }
    for (x=i+1,y=j-1; x>=0 && y>=0 && x<n && y<n; x++,y--) {
        if (board[x][y]==1) {
            return false;
        }
    }
    return true;
}

bool NQ(int **board, int col, int n){
    if (col>=n) {
        return true;
    }
    bool result;
    for (int k=0; k<n; k++) {       //trying each row for a given column
        if (Qsafe(board, k, col, n)) {
            board[k][col]=1;
            result = NQ(board, col+1, n);
        }
        if (result) {
            return true;
        }else{
            board[k][col]=0;
        }
    }
    
    return false;
}

void Nqueen(int n){
    int **board;
    board = (int **)malloc(n*sizeof(int*));
    for (int i=0; i<n; i++) {
        board[i]=(int *)malloc(n*sizeof(int));
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            board[i][j] = 0;
        }
    }
    if(NQ((int **)board, 0, n)){
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                cout << board[i][j] << "\t";
            }
            cout << endl;
        }
    };
}

bool isSubsetSum(int set[], int n, int sum){  //The value of subset[i][j] will be true if there is a subset of
    //set[0..j-1] with sum equal to i., otherwise false.
    bool subset[sum+1][n+1];
    for (int i=0; i<=n; i++) {
        subset[0][i]=true;
    }
    for (int i=1; i<=sum; i++) {
        subset[i][0]=false;
    }
    for (int i=0; i<=sum; i++) {
        for (int j=1; j<=n; j++) {
            subset[i][j] = subset[i][j-1];
            if (i >= set[j-1]) {
                subset[i][j] = subset[i][j] || subset[i-set[j-1]][j-1];
            }
        }
    }
    
    cout << "x\t";
    for (int j=0; j<n; j++) {
        cout << set[j] << "\t";
    }
    cout << endl;
    for (int i=0; i<=sum; i++) {
        cout << i << "\t";
        for (int j=0; j<=n; j++) {
            cout << subset[i][j] << "\t";
        }
        cout << endl;
    }
    return subset[sum][n];
}

int denomsUtil(int denoms[], int n, int amount, int index){
    if(amount==0){
        return 1;
    }
    if (amount<0) {
        return 0;
    }
    if (index==0) {
        return 1;
    }
    if (index<0) {
        return 0;
    }
    if (n<=0 && index>=1) {
        return 0;
    }
    return denomsUtil(denoms, n, amount, index-1) + denomsUtil(denoms, n, amount-denoms[index], index);
}

int denom(int denoms[], int n, int amount){
    int ways = denomsUtil(denoms, n, amount, n-1);
    return ways;
}

int LCS(char s1[1024], char s2[1024], int m, int n, int i, int j){
    if (m==0||n==0) {
        return 0;
    }
    if (i>m || j>n) {
        return 0;
    }
    if (s1[i]==s2[j]) {
        return 1+LCS(s1, s2, m, n, i+1, j+1);
    }
    else{
        return (LCS(s1, s2, m, n, i+1, j)>LCS(s1, s2, m, n, i, j+1))?LCS(s1, s2, m, n, i+1, j):LCS(s1, s2, m, n, i, j+1);
    }
}

int LcsDP(char s1[1024], char s2[1024], int m, int n){
    int lcsMat[1024][1024];
    for (int i=0; i<m; i++) {
        lcsMat[i][n] = 0;
    }
    for (int i=0; i<n; i++) {
        lcsMat[m][i] = 0;
    }
    for (int i=m-1; i>=0; i--) {
        for (int j=n-1; j>=0; j--) {
            lcsMat[i][j] = lcsMat[i+1][j+1];
            if (s1[i]==s2[j]) {
                lcsMat[i][j]++;
            }
            if (lcsMat[i+1][j]>lcsMat[i][j]) {
                lcsMat[i][j] = lcsMat[i+1][j];
            }
            if (lcsMat[i][j+1]>lcsMat[i][j]) {
                lcsMat[i][j] = lcsMat[i][j+1];
            }
        }
    }
    cout << endl;
    cout << " \t";
    for (int j=0; j<n; j++) {
        cout << s2[j] << "\t";
    }
    cout << endl;
    for (int i=0; i<m; i++) {
        cout << s1[i] << "\t";
        for (int j=0; j<n; j++) {
            cout << lcsMat[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
    
    return lcsMat[0][0];
}

void HanoiUtil(int n, char s, char d, char i){
    if (n==0) {
        return;
    }
    HanoiUtil(n-1, s, i, d);
    cout << "Move disk " << n << " from " << s << " to " << d <<  endl;
    HanoiUtil(n-1, i, d, s);
    
}

void Hanoi(int n){
    HanoiUtil(n, 'a', 'c', 'b');
}

int max(int a, int b){
    return (a>b)?a:b;
}

int LIS(int a[], int n1, int prev = -1000){
    if (n1 <= 0) {
        return 0;
    }
    if (*a >= prev) {
        prev = *a;
        return 1 + LIS(a+1,n1-1,prev);
    }
    prev = *a;
    return max(LIS(a+1, n1-1, prev), LIS(a+2, n1-2, prev));
}

int LISdp(int a[], int n){
    int b[n];
    for (int i=0; i<n; i++) {
        b[i] = 1;
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<i; j++) {
            if (a[j] < a[i] && b[i]+1 < b[j]) {
                b[j] = 1+b[i];
            }
        }
    }
    int max=0;
    for (int i=0; i<n; i++) {
        if (b[i]>max) {
            max = b[i];
        }
    }
    return max;
}

int main()
{
    int ch;
    {
        cout << "Enter choice\n" <<
        " 1.Generate Binary Matrix\n" <<
        " 2.See if there is subset for given sum\n" <<
        " 3.Show the subsets for given sum\n" <<
        " 4.Print all subsets of a set\n" <<
        " 5.Show all permutations of a string\n" <<
        " 6.Generate parantheses\n" <<
        " 7.Number of ways of climbing steps\n" <<
        " 8.Generate number partition\n" <<
        " 9.Find path in matrix\n" <<
        " 10.Find all paths and cost\n" <<
        " 11.Calculate basin size using DFS\n" <<
        " 12.Calculate basin size using BFS\n" <<
        " 13.Knight's tour\n" <<
        " 14.N queen problem\n" <<
        " 15.Subset sum using DP\n" <<
        " 16.Denomination problem\n" <<
        " 17.Towers of hanoi\n" <<
        " 18.Longest common subsequence\n" <<
        " 19.Longest increasing subsequence\n";
    }
    cin >> ch;
    switch (ch) {
        case 1:
        {
            int n;
            cout << "Enter size" << endl;
            cin >> n;
            int arr[n];
            for (int i=0; i<n; i++) {
                arr[i] = 0;
            }
            shuffle2(arr,n,n);
        }
            cout << endl;
            break;
        case 2:
        {
            int n;
            cout << "Enter the size of the matrix\n";
            cin >> n;
            int arr[n];
            cout << "Enter the elements of the set separated by a space\n";
            for (int i=0; i<n; i++) {
                cin >> arr[i];
            }
            bool found = false;
            int sum;
            cout << "Enter the sum\n";
            cin >> sum;
            found = isSetSum(arr, n, sum);
            if (found) {
                cout << "Subset with given sum is found\n";
            }else{
                cout << "Subset with given sum is not found\n";
            }
            cout << endl;
            break;
        }
        case 3:
        {
            int n;
            cout << "Enter the size of the matrix\n";
            cin >> n;
            int arr[n];
            int bin[n];
            for (int i=0; i<n; i++) {
                bin[i] = 0;
            }
            cout << "Enter the elements of the set separated by a space\n";
            for (int i=0; i<n; i++) {
                cin >> arr[i];
            }
            int sum;
            cout << "Enter the sum\n";
            cin >> sum;
            showSetSum(arr, n, n, sum, bin);
            cout << endl;
            break;
        }
        case 4:
        {
            int n;
            cout << "Enter the size of the matrix\n";
            cin >> n;
            int arr[n];
            int bin[n];
            for (int i=0; i<n; i++) {
                bin[i] = 0;
            }
            cout << "Enter the elements of the set separated by a space\n";
            for (int i=0; i<n; i++) {
                cin >> arr[i];
            }
            showSubSet(arr, n, n, bin);
            cout << endl;
            break;
        }
        case 5:
        {
            char a[100];
            cout << "Enter the string to permute\n";
            cin >> a;
            int i=0;
            while (a[i] != '\0') {
                i++;
            }
            permute(a,i,0);
        }
            cout << endl;
            break;
        case 6:
        {
            int n;
            cout << "Enter the size" << endl;
            cin >> n;
            n = 2*n;
            char arr[n];
            paran(arr, 0, n, 0, 0);
        }
            cout << endl;
            break;
        case 7:
        {
            int n;
            cout << "Enter the number of steps\n";
            cin >> n;
            n = stepsDP(n);
            cout << "\nThe steps can be climbed in " << n << " ways!" << endl;
        }
            break;
        case 8:
        {
            int n;
            cout << "Enter the number\n";
            cin >> n;
            partitionProper(n);
        }
            break;
        default:
            break;
        case 9:
        {
            int x,y;
            cout << "Enter the dimensions of the matrix separated by space\n";
            cin >> x >> y;
            int **mat;
            mat = (int **)malloc(x*sizeof(*mat));
            for (int i=0; i<x+1; i++) {
                mat[i] = (int *)malloc((y+1)*sizeof(*mat[i]));
            }
            int **path;
            path = (int **)malloc(x*sizeof(*path));
            for (int i=0; i<x+1; i++) {
                path[i] = (int *)malloc((y)*sizeof(*path[i]));
            }
            cout << "Enter the matrix values\n\t0 for block\n\t1 for path\n\n";
            for (int i=0; i<x; i++) {
                for (int j=0; j<y; j++) {
                    cin >> mat[i][j];
                }
            }
            path[0][0] = 1;
            mat[0][0] = 1;
            if(!findWay((int **)mat,(int **)path,0,0,y,x,0)){
                cout << "\nNo way!\n";
            }else{
                path[x-1][y-1] = 1;
                for (int i=0; i<x; i++) {
                    for (int j=0; j<y; j++) {
                        cout << path[i][j] << "\t";
                    }
                    cout << endl;
                }
                //cout << len;
            }
        }
            break;
        case 10:
        {
            int x,y;
            cout << "Enter the dimensions of the matrix separated by space\n";
            cin >> x >> y;
            int **mat;
            mat = (int **)malloc(x*sizeof(*mat));
            for (int i=0; i<x; i++) {
                mat[i] = (int *)malloc((y)*sizeof(*mat[i]));
            }
            int **path;
            path = (int **)malloc((x+y)*sizeof(*path));
            for (int i=0; i<(x+y); i++) {
                path[i] = (int *)malloc((2)*sizeof(*path[i]));
            }
            cout << "Enter the matrix values\n\t0 for block\n\tnumber for cost\n\n";
            for (int i=0; i<x; i++) {
                for (int j=0; j<y; j++) {
                    cin >> mat[i][j];
                }
            }
            path[0][0] = 0;
            path[0][1] = 0;
            int **s;
            s = (int **)malloc((x+y+1)*sizeof(*s));
            for (int i=0; i<(x+y+1); i++) {
                s[i] = (int *)malloc((2)*sizeof(*s[i]));
            }
            allPath(mat, path, 0, 0, x, y, 1, 0, s);
            cout << endl << endl << "The shortest path:" << endl;
            int t;
            for (t=0; t<(x+y-1); t++) {
                cout << "(" << s[t][0] << "," << s[t][1] << ")" << "\t";
            }
            cout << "COST: " << s[t][0] << endl;
            
        }
            break;
        case 11:
        {
            int **region,**visited;
            int x,y;
            cout << "Enter total region dimensions\n";
            cin >> x >> y;
            region = (int **)malloc(x*sizeof(int*));
            for (int i=0; i<x; i++) {
                region[i] = (int *)malloc(y*sizeof(int));
            }
            visited = (int **)malloc(x*sizeof(int*));
            for (int i=0; i<x; i++) {
                visited[i] = (int *)malloc(y*sizeof(int));
            }
            for (int i=0; i<x; i++) {
                for (int j=0; j<y; j++) {
                    visited[i][j] = 0;
                }
            }
            cout << "Enter the altitudes\n";
            for (int i=0; i<x; i++) {
                for (int j=0; j<y; j++) {
                    cin >> region[i][j];
                }
            }
            int size=0;
            int i,j;
            cout << "Enter the co ordinated to find basin size:";
            cin >> i >> j;
            visited[i][j] = 1;
            basinSizeDFS(region, &size, x, y, i, j, region[i][j], visited);
            cout << "\nBasin size for that altitude is " << size << endl;
            for (int i=0; i<x; i++) {
                for (int j=0; j<y; j++) {
                    cout << visited[i][j] << "\t";
                }
                cout << endl;
            }
        }
            break;
        case 12:
        {
            int **region,**visited;
            int x,y;
            cout << "Enter total region dimensions\n";
            cin >> x >> y;
            region = (int **)malloc(x*sizeof(int*));
            for (int i=0; i<x; i++) {
                region[i] = (int *)malloc(y*sizeof(int));
            }
            visited = (int **)malloc(x*sizeof(int*));
            for (int i=0; i<x; i++) {
                visited[i] = (int *)malloc(y*sizeof(int));
            }
            for (int i=0; i<x; i++) {
                for (int j=0; j<y; j++) {
                    visited[i][j] = 0;
                }
            }
            cout << "Enter the altitudes\n";
            for (int i=0; i<x; i++) {
                for (int j=0; j<y; j++) {
                    cin >> region[i][j];
                }
            }
            int size=0;
            int i,j;
            cout << "Enter the co ordinated to find basin size:";
            cin >> i >> j;
            size = basinSizeBFS(region, visited, x, y, i, j);
            cout << "\nBasin size for that altitude is " << size << endl;
            for (int i=0; i<x; i++) {
                for (int j=0; j<y; j++) {
                    cout << visited[i][j] << "\t";
                }
                cout << endl;
            }
        }
            break;
        case 13:
            solveKtour();
            break;
        case 14:
            int n;
            cout << "Enter n\n";
            cin >>n;
            Nqueen(n);
            break;
        case 15:
        {
            int n;
            cout << "Enter the size of the set\n";
            cin >> n;
            int arr[n];
            cout << "Enter the elements of the set separated by a space\n";
            for (int i=0; i<n; i++) {
                cin >> arr[i];
            }
            int sum;
            cout << "Enter the sum\n";
            cin >> sum;
            if(isSubsetSum(arr, n, sum))
            {
                cout << "sum found";
            }
            cout << endl;
        }
            break;
        case 16:
        {
            int denoms[9] = {1,2,5,10,20,50,100,500,1000};
            int amt;
            cout << "enter the amount\n";
            cin >> amt;
            cout << "The number of ways : " << denom(denoms, 3, amt);
            cout << endl;
            
        }
            break;
        case 17:
        {
            cout << "Enter n value" << endl;
            int n;
            cin >> n;
            Hanoi(n);
        }
            break;
        case 18:
        {
            char s1[1024];
            int m;
            char s2[1024];
            int n;
            cout << "Enter the size of 1st string\t" ;
            cin >> m;
            cout << "Enter the string\t";
            cin >> s1;
            cout << "Enter the size of 2nd string\t" ;
            cin >> n;
            cout << "Enter the string\t";
            cin >> s2;
            cout << LcsDP(s1, s2, m, n) << endl;
        }
            break;
        case 19:
        {
            int n1;
            cout << "Enter length of array\n";
            cin >> n1;
            int a[n1];
            cout << "Enter array contents\n";
            for (int i=0; i<n1; i++) {
                cin >> a[i];
            }
            cout << LISdp(a,n1) << endl;
        }
            break;
    }
    return 0;
}

