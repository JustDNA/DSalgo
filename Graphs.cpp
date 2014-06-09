#include <iostream>
#include <list>
#include <stack>
using namespace std;

class edge{
    int src;
    int des;
    int len;        //incoming length to edge a
public:
    edge(int src, int des, int b=1){
        this->src=src;
        this->des = des;
        this->len=b;
    }
    int source(){
        return src;
    }
    int destination(){
        return des;
    }
    int length(){
        return len;
    }
};

struct Heap{
    edge *array;
    int count;
    int capacity;
    int heap_type;      //0 for min, 1 for max]
};

struct Heap* createHeap(int capacity=5, int heaptype = 0){
    struct Heap* h = (struct Heap*)malloc(sizeof(struct Heap));
    if (!h) {
        cout << "Memory error!\n";
        return NULL;
    }
    h->heap_type = heaptype;
    h->count=0;
    h->capacity = capacity;
    h->array = (edge *)malloc(h->capacity*sizeof(edge));
    if (!h->array) {
        cout << "Memory error";
        return NULL;
    }
    return h;
}

int parentHeap(struct Heap*h, int pos){
    if (pos<=0 || pos>=h->count) {
        return -1;
    }
    int parent = (pos - 1)/2;
    
    return parent;
}

int LeftChildHeap(struct Heap*h, int pos){
    int left = 2*pos + 1;
    if (left>=h->count) {
        return -1;
    }
    return left;
}

int RightChildHeap(struct Heap*h, int pos){
    int right = 2*pos + 2;
    if (right>=h->count) {
        return -1;
    }
    return right;
}

void ResizeHeap(struct Heap **h1){
    struct Heap* h = (*h1);
    edge *arrOld;
    arrOld = (edge *)malloc(h->capacity*sizeof(edge));
    for (int i=0; i<h->capacity; i++) {
        arrOld[i] = h->array[i];
    }
    h->array = (edge *)malloc(2*h->capacity*sizeof(edge));
    if (!h->array) {
        cout << "Memory Error\n";
        return;
    }
    for (int i=0; i<h->capacity; i++) {
        h->array[i] = arrOld[i];
    }
    h->capacity *= 2;
    free((edge *)arrOld);
}

void percolateDown(struct Heap **h1, int pos){
    struct Heap* h = (*h1);
    int l=0,r=0,min;
    
    l = LeftChildHeap(h, pos);
    r = RightChildHeap(h, pos);
    
    if (l!=-1 && (h->array[l].length() < h->array[pos].length())) {
        min = l;
    }else{
        min = pos;
    }
    
    if (r!=-1 && (h->array[r].length() < h->array[min].length())) {
        min = r;
    }
    
    if (min != pos) {
        
        edge temp = h->array[pos];
        h->array[pos] = h->array[min];
        h->array[min] = temp;
        percolateDown(&h, min);
    }
}

edge delMinInHeap(struct Heap **h1){
    struct Heap* h = (*h1);
    if (h->count==0) {
   //     return NULL;
    }
    edge data = h->array[0];
    h->array[0] = h->array[h->count-1];
    h->count--;
    percolateDown(&h, 0);
    return data;
}

void InsertInHeap(struct Heap **h1, edge data){
    struct Heap *h = (*h1);
    if (h->count == h->capacity) {
        ResizeHeap(h1);
    }
    int pos = h->count;
    while (h->array[(pos - 1)/2].length() > data.length() && pos>0) {
        h->array[pos] = h->array[(pos - 1)/2];
        pos = (pos-1)/2;
    }
    h->array[pos] = data;
    h->count++;
}


class Graph
{
    int V;
    list<edge> *adj;     //pointer to an array of lists
    int *InMST;
    void DFSutil(int v, bool visited[]);
    void BFSutil(int v, bool visited[]);
    void BFSpathUtil(int a, int b, bool visited[]);
    void topoSortUtil(int v, bool visited[], stack<int> &stack);
public:
    struct Heap* edgeHeap;
    Graph(int V);
    void addEdge(int v, int w, int len);
    void DFS();
    void DFS(int v);
    void BFS();
    void BFS(int v);
    void BFSpath(int a, int b);
    int vertices();
    void topoSort();
    void shortPath(int a, int b);
    void shortPathWeight(int a, int b);
    int IsInMST(int a, int b);
    void AddInMST(int a, int b);
};

int Graph::IsInMST(int a, int b){
    int t = InMST[a];
    while (t!=a) {
        a = t;
        t=InMST[a];
    }

    int t2 = InMST[b];
    while (t2!=b) {
        b = t2;
        t2=InMST[b];
    }

    if (t==t2) {
        return 1;
    }else{
        return 0;
    }
}

void Graph::AddInMST(int a, int b){
    if (IsInMST(a, b)) {
        return;
    }
    
    int t = InMST[a];
    int len=0;
    while (t!=a) {
        a = t;
        t=InMST[a];
        len++;
    }
    int t2 = InMST[b];
    int len2=0;
    while (t2!=b) {
        b = t2;
        t2=InMST[b];
        len2++;
    }

    
    if (len>len2) {
        InMST[t2] = t;
    }else{
        InMST[t] = t2;
    }
}

int Graph::vertices(){
    return this->V;
}

Graph::Graph(int V){
    this->V = V;
    adj = new list<edge>[V];
    edgeHeap = createHeap();
    InMST = (int *)malloc(V*sizeof(int));
    for (int i=0; i<V; i++) {
        InMST[i]=i;
    }
}

void Graph::addEdge(int v, int w, int len=1){
    edge e1(v,w,len);
    edge e2(w,v,len);
    adj[v].push_back(e1);       //adding w to v's list
    adj[w].push_back(e2);       //adding v to w's list
    InsertInHeap(&edgeHeap, e1);
    InsertInHeap(&edgeHeap, e2);
}

void Graph::DFSutil(int v, bool visited[]){
    visited[v] = true;
    cout << v << " ";
    list<edge>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i) {
        if (!visited[(*i).destination()]) {
            DFSutil((*i).destination(), visited);
        }
    }
}

void Graph::DFS(){
    bool *visited;
    visited = new bool[V];
    for (int i=0; i<V; i++) {
        visited[i] = false;
    }
    for (int i=0; i<V; i++) {
        if (visited[i] == false) {
            DFSutil(i, visited);
        }
    }
}

void Graph::DFS(int v){
    bool *visited;
    visited = new bool[V];
    for (int i=0; i<V; i++) {
        visited[i] = false;
    }
    DFSutil(v, visited);
}

void Graph::BFSutil(int v, bool visited[]){
    list<int> q;
    list<edge>::iterator itr;
    q.push_back(v);
    visited[v]=true;
    while (!q.empty()) {
        v = q.front();
        q.pop_front();
        cout << v << " ";
        for (itr=adj[v].begin(); itr!=adj[v].end(); itr++) {
            if (!visited[(*itr).destination()]) {
                q.push_back((*itr).destination());
                visited[(*itr).destination()] = true;
            }
        }
    }
    
}

void Graph::BFS(int v){
    bool *visited;
    visited = new bool[V];
    for (int i=0; i<V; i++) {
        visited[i] = false;
    }
    BFSutil(v, visited);
}

void Graph::BFS(){
    bool *visited;
    visited = new bool[V];
    for (int i=0; i<V; i++) {
        visited[i] = false;
    }
    for (int i=0; i<V; i++) {
        if (visited[i] == false) {
            BFSutil(i, visited);
        }
    }
    
}

void Graph::BFSpathUtil(int a, int b, bool visited[]){
    list<int> q;
    list<edge>::iterator itr;
    q.push_back(a);
    visited[a]=true;
    if(a==b){
        cout << "Path found\n";
        return;
    }
    while (!q.empty()) {
        a = q.front();
        if(a==b){
            cout << "Path found\n";
            return;
        }
        q.pop_front();
        for (itr=adj[a].begin(); itr!=adj[a].end(); itr++) {
            if (!visited[(*itr).destination()]) {
                q.push_back((*itr).destination());
                visited[(*itr).destination()] = true;
            }
        }
    }
    cout << "Path not found\n";
}

void Graph::BFSpath(int a, int b){
    bool *visited;
    visited = new bool[V];
    for (int i=0; i<V; i++) {
        visited[i] = false;
    }
    BFSpathUtil(a, b, visited);
}

void Graph::topoSortUtil(int v, bool *visited, stack<int> &stack){
    visited[v] = true;
    list<edge>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i) {
        if (!visited[(*i).destination()]) {
            topoSortUtil((*i).destination(), visited, stack);
        }
    }
    stack.push(v);      //its like post order traversal of tree
}

void Graph::topoSort(){
    stack<int> stack;
    bool *visited;
    visited = new bool[V];
    for (int i=0; i<V; i++) {
        visited[i] = false;
    }
    for (int i=0; i<V; i++) {
        if (visited[i] == false) {
            topoSortUtil(i, visited, stack);
        }
    }
    while (!stack.empty()) {
        cout << stack.top() << "\t";
        stack.pop();
    }
}

void Graph::shortPath(int a, int b){
    int dist[V];
    int prev[V];
    for (int i=0; i<V; i++) {
        prev[i]=dist[i]=-1;
    }
    dist[a]=0;
    list<int> q;
    list<edge>::iterator it;
    q.push_back(a);
    int x;
    while (!q.empty()) {
        x = q.front();
        q.pop_front();
        for (it=adj[x].begin(); it!=adj[x].end(); it++) {
            if (dist[(*it).destination()]==-1) {
                dist[(*it).destination()]=dist[x]+1;
                prev[(*it).destination()]=x;
                q.push_back((*it).destination());
            }
        }
    }
    
    if (dist[b]==-1) {
        cout << "No path\n";
        return;
    }
    
    cout << "The distance from " << a << " to " << b << " is " << dist[b] << " hops.\nThe path is:\n";
    stack<int> stack;
    for (int i=b; i!=a; i=prev[i]) {
        stack.push(i);
    }
    cout << a << "\t";
    while (!stack.empty()) {
        cout << stack.top() << "\t";
        stack.pop();
    }
}

void Graph::shortPathWeight(int a, int b){
    int dist[V];
    int prev[V];
    for (int i=0; i<V; i++) {
        prev[i]=dist[i]=-1;
    }
    dist[a]=0;
    list<int> q;
    list<edge>::iterator it;
    q.push_back(a);
    int x;
    while (!q.empty()) {
        x = q.front();
        q.pop_front();
        for (it=adj[x].begin(); it!=adj[x].end(); it++) {
            if (dist[(*it).destination()]==-1) {
                dist[(*it).destination()]=dist[x]+(*it).length();
                prev[(*it).destination()]=x;
                q.push_back((*it).destination());
            }
            if (dist[(*it).destination()]>=dist[x]+(*it).length()) {
                dist[(*it).destination()]=dist[x]+(*it).length();
                prev[(*it).destination()]=x;
                list<int>::iterator i;
                q.push_back((*it).destination());
            }
        }
    }
    
    if (dist[b]==-1) {
        cout << "No path\n";
        return;
    }
    
    cout << "The distance from " << a << " to " << b << " is " << dist[b] << " units.\nThe path is:\n";
    stack<int> stack;
    for (int i=b; i!=a; i=prev[i]) {
        stack.push(i);
    }
    cout << a << "\t";
    while (!stack.empty()) {
        cout << stack.top() << "\t";
        stack.pop();
    }
}

void generateGraph(Graph g){
    
    g.addEdge(0, 5, 3);
    g.addEdge(1, 3, 2);
    g.addEdge(3, 0, 7);
    g.addEdge(3, 2, 3);
    g.addEdge(2, 0, 2);
    g.addEdge(0, 4, 2);
    g.addEdge(4, 2, 3);
    g.addEdge(6, 1, 4);
    g.addEdge(8, 6, 3);
    g.addEdge(3, 8, 4);
    g.addEdge(8, 7, 5);
    g.addEdge(2, 7, 2);
    g.addEdge(7, 4, 5);
    g.addEdge(4, 9, 3);
    g.addEdge(5, 1, 2);
    g.addEdge(7, 9, 4);
    g.addEdge(2, 5, 7);
    
    g.addEdge(15, 3, 200);
    g.addEdge(2, 14, 250);
    
    g.addEdge(10, 16, 7);
    g.addEdge(16, 19, 7);
    g.addEdge(19, 15, 4);
    g.addEdge(15, 10, 2);
    g.addEdge(16, 15, 3);
    g.addEdge(18, 19, 4);
    g.addEdge(18, 14, 3);
    g.addEdge(15, 18, 5);
    g.addEdge(15, 14, 5);
    g.addEdge(10, 14, 5);
    g.addEdge(14, 12, 2);
    g.addEdge(17, 14, 5);
    g.addEdge(17, 18, 2);
    g.addEdge(14, 13, 10);
    g.addEdge(13, 17, 10);
    g.addEdge(12, 11, 15);
    g.addEdge(11, 13, 10);
    g.addEdge(12, 10, 1);

}

Graph createGraph(){
    char ch;
    cout << "Generate graph(y/n)? ";
    cin >> ch;
    if (ch=='y') {
        Graph g(20);
        generateGraph(g);
        return g;
    }
    int n;
    cout << "Build the graph\nEnter no of edges : ";
    cin >> n;
    Graph g(n);
    int k;
    cout << "1.Unweighted\n2.Weighted";
    cin >> k;
    switch (k) {
        case 1:
            cout << "Enter the edges(-1 to stop adding):\n" << endl;
            cout << "Source->Destination" << endl;
            while (1) {
                int a,b;
                cin >> a;
                if(a==-1){
                    break;
                }cin >>b;
                if((a==-1)||(b==-1)){
                    break;
                }
                if((a>=n)||(b>=n)){
                    cout << "Invalid entry\n";
                }else
                {
                    g.addEdge(a, b);
                }
            }
            break;
        case 2:
            cout << "Enter the edges(-1 to stop adding):\n" << endl;
            cout << "Source->Destination Distance" << endl;
            while (1) {
                int a,b,c;
                cin >> a;
                if(a==-1){
                    break;
                }
                cin >>b;
                if((a==-1)||(b==-1)){
                    break;
                }
                cin >> c;
                if((a>=n)||(b>=n)){
                    cout << "Invalid entry\n";
                }else
                {
                    g.addEdge(a, b, c);
                }
            }
            break;
            
        default:
            break;
    }
    return g;
    
}

int main()
{
    Graph g = createGraph();
    int ch;
    while (1) {
        cout << "\nEnter a choice:\n";
        cout << "1.Make DFS from a edge\n";
        cout << "2.Show all edges using DFS\n";
        cout << "3.Make BFS from a edge\n";
        cout << "4.Show all edges using BFS\n";
        cout << "5.Find if there is path between 2 edges\n";
        cout << "6.Topological sort\n";
        cout << "7.Find shortest unweighted path between two edges\n";
        cout << "8.Find shortest weighted path between two edges\n";
        cout << "9.Create Kruskal's MST\n";
        cout << "Other:Exit\n";
        cin >> ch;
        switch (ch) {
            case 1:
                cout << "Enter edge:";
                int n;
                cin >> n;
                if(g.vertices()>n && n>=0){
                    cout << endl;
                    g.DFS(n);
                    cout << endl;
                }else{
                    cout << "Invalid entry\n";
                }
                break;
            case 2:
                cout << endl;
                g.DFS();
                cout << endl;
                break;
            case 3:
                cout << "Enter edge:";
                cin >> n;
                if(g.vertices()>n && n>=0){
                    cout << endl;
                    g.BFS(n);
                    cout << endl;
                }else{
                    cout << "Invalid entry\n";
                }break;
            case 4:
                cout << endl;
                g.BFS();
                cout << endl;
                break;
            case 5:
                cout << "Enter source and destination edges\n";
                int a,b;
                cin >> a >> b;
                if(g.vertices()>a && a>=0 && g.vertices()>b && b>=0){
                    cout << endl;
                    g.BFSpath(a, b);
                    cout << endl;
                }else{
                    cout << "Invalid entry\n";
                }break;
            case 6:
                cout << endl;
                g.topoSort();
                cout << endl;
                break;
            case 7:
                cout << "Enter source and destination edges\n";
                int x,y;
                cin >> x >> y;
                cout << endl;
                g.shortPath(x, y);
                cout << endl;
                break;
            case 8:
                cout << "Enter source and destination edges\n";
                int l,m;
                cin >> l >> m;
                cout << endl;
                g.shortPathWeight(l, m);
                cout << endl;
                break;
            case 9:
            {
                Graph mst(g.vertices());
                int count = 0;
                
                cout << endl;
                while (g.edgeHeap->count>0) {
                    edge e = delMinInHeap(&g.edgeHeap);
                    if (!mst.IsInMST(e.source(), e.destination())) {
                        mst.AddInMST(e.source(), e.destination());
                        mst.addEdge(e.source(), e.destination(),e.length());
                    cout << e.source() << "\t<->\t\t"<< e.destination() << "\t\t" <<e.length() << endl;
                          count++;
                    }
                    if (count == g.vertices()-1) {
                        break;
                    }
                }
                cout << endl;
                cout << "Enter source and destination edges\n";
                int l,m;
                cin >> l >> m;
                cout << endl;
                mst.shortPathWeight(l, m);
                cout << endl;
                return 0;
            }
                break;
                
            default:
                cout << endl;
                return 0;
                break;
        }
    }
    cout << endl;
    return 0;
}