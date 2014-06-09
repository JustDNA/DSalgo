#include <iostream>
#include <list>
using namespace std;

struct node{
    int data;
    node * left = NULL;
    node * right = NULL;
};

void insert(node ** rt, node * n){
    node * root = *rt;
    if (!rt) {
        return;
    }
    list<node *> l;
    l.push_back(root);
    while (l.front()) {
        node * temp = l.front();
        l.pop_front();
        if (!temp->left) {
            temp->left = n;
            return;
        }else{
            l.push_back(temp->left);
        }
        if (!temp->right) {
            temp->right = n;
            return;
        }else{
            l.push_back(temp->right);
        }
    }
}

void inorder(node * root){
    if (!root) {
        return;
    }
    inorder(root->left);
    cout << root->data << "\t";
    inorder(root->right);
}

void preorder(node * root){
    if (!root) {
        return;
    }
    cout << root->data << "\t";
    preorder(root->left);
    preorder(root->right);
}

void postorder(node * root){
    if (!root) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->data << "\t";
}

void InorderIter(node * root){
    list<node *> l;
    while (1) {
        while (root) {
            l.push_front(root);
            root = root->left;
        }
        if (l.empty()) {
            return;
        }
        root = l.front();
        l.pop_front();
        cout << root->data << "\t";
        root = root->right;
    }
}

void preorderIter(node * root){
    list<node *> l;
    while (1) {
        while (root) {
            cout << root->data << "\t";
            l.push_front(root);
            root = root->left;
        }
        if (l.empty()) {
            return;
        }
        root = l.front();
        l.pop_front();
        root = root->right;
    }
}

void preorderIter2(node * root){
    list<node *> l;
    l.push_front(root);
    while (l.front()) {
            root = l.front();
            l.pop_front();
            cout << root->data << "\t";
            if(root->right)
                l.push_front(root->right);
            if(root->left)
                l.push_front(root->left);
        }
        if (l.empty()) {
            return;
        }
}

void postorderIter(node * root){
    list<node*> l,l2;
    l.push_front(root);
    while (1) {
        while (l.front()) {
            root = l.front();
            l.pop_front();
            l2.push_front(root);
            if(root->left){
                l.push_front(root->left);
            }
            if(root->right){
                l.push_front(root->right);
            }
        }
        if (l2.empty()) {
            return;
        }
        while (l2.front()) {
            cout << l2.front()->data << "\t";
            l2.pop_front();
        }
    }
}

void postorderIter2(node * root){
    list<node *> l,l2;
    while (1) {
        while (root) {
            l2.push_front(root);
            l.push_front(root);
            root = root->right;
        }
        if (l.empty()) {
            break;
        }
        root = l.front();
        l.pop_front();
        root = root->left;
    }
    if (l2.empty()) {
        return;
    }
    while (l2.front()) {
        cout << l2.front()->data << "\t";
        l2.pop_front();
    }
}

node * maxLeft(node * n){
    if (!n->left) {
        return NULL;
    }
    n=n->left;
    while (n->right) {
        n=n->right;
    }
    return n;
}

node * maxRight(node * n){
    if (!n->right) {
        return NULL;
    }
    n=n->right;
    while (n->left) {
        n=n->left;
    }
    return n;
}

bool isBST(node * root){
    if (!root) {
        return true;
    }
    if (root->left != NULL && root->data < maxLeft(root)->data) {
        return false;
    }
    if (root->right != NULL && root->data > maxRight(root)->data) {
        return false;
    }
    return (isBST(root->left) && isBST(root->right));
}

bool find(node * root, int data){     // preorder variant
    
    if (root) {
        if (root->data == data) {
            return true;
        }
        bool status = false;
        status = find(root->left, data);
        if(status) {
            return status;
        }
        return find(root->right, data);
    }
    return false;
}

void delTree(node ** root){
    if (!*root) {
        return;
    }
    delTree(&((*root)->left));
    delTree(&((*root)->right));
    *root=NULL;
    free(*root);
}

int max(int a, int b){
    return ((a>b)?a:b);
}

int height(node * root){
    if (!root) {
        return 0;
    }
    return 1+max(height(root->left),height(root->right));
}

int heightIter(node * root){
    if (!root) {
        return 0;
    }
    int height = 0;
    list<node *> l;
    l.push_back(root);
    l.push_back(NULL);
    while (!l.empty()) {
        node * temp = l.front();
        l.pop_front();
        if (!temp) {
            height++;
            if(!l.empty())
                l.push_back(NULL);
        }else{
            if (temp->left) {
                l.push_back(temp->left);
            }
            if (temp->right) {
                l.push_back(temp->right);
            }
        }
    }
    return height;
}

int diameter(node * root, int * dia){
    if (!root) {
        return 0;
    }
    int left=0, right=0;
    left = diameter(root->left, dia);
    right = diameter(root->right, dia);
    if (left + right > *dia) {
        *dia = left+right;
    }
    return max(left, right) + 1;
}

void print(int A[], int len){
    for (int i=0; i<len; i++) {
        cout << A[i] << "\t";
    }
    cout << endl;
}

void pathToLeaf(node * root, int path[], int len){
    if (!root) {
        return;
    }
    path[len++] = root->data;
    if (root->left == NULL && root->right == NULL) {
        print(path, len);
    }
    pathToLeaf(root->left, path, len);
    pathToLeaf(root->right, path, len);
}

void pathsum(node * root, int path[], int sum, int len){
    if (!root) {
        return;
    }
    path[len++] = root->data;
    if (sum-root->data == 0) {
        print(path, len);
    }
    pathsum(root->left, path, sum-root->data, len);
    pathsum(root->right, path, sum-root->data, len);
}

void mirror(node ** rt){
    node * root = *rt;
    if (!root) {
        return;
    }
    if (root->left == NULL && root->right == NULL) {
        return;
    }
    if (root->left)
        mirror(&(root->left));
    if (root->right)
        mirror(&(root->right));
    node * temp = NULL;
    temp = root->right;
    root->right = root->left;
    root->left = temp;
}

node * buidTree(int inorder[], int preorder[], int start, int end){
    if (start>end) {
        return NULL;
    }
    node * root = new node;
    root->left = root->right = NULL;
    if (!root) {
        cout << "Memory error\n";
        return NULL;
    }
    root->data = preorder[0];
    int i=start;
    while (inorder[i]!=root->data) {
        i++;
    }
    if (i>end) {
        cout << "error!" << endl;
        return NULL;
    }
    root->left = buidTree(inorder, preorder+1, start, i-1);
    root->right = buidTree(inorder, preorder+1+i, i+1, end);
    
    return root;
}

bool printAncestors(node * root, int data){
    if (!root) {
        return false;
    }
    if (root->data==data) {
        return true;
    }
    bool b = printAncestors(root->left, data);
    if(!b)
        b = printAncestors(root->right, data);
    if(b)
        cout << root->data << "\t";
    return b;
}

node * LCA(node * root, int a, int b){
    if (!root) {
        return NULL;
    }
    if (root->data == a || root->data == b) {
        return root;
    }
    node * x = LCA(root->left, a, b);
    node * y = LCA(root->right, a, b);
    if (x&&y) {
        return root;
    }
    return (x)?x:y;
}

void zigzag(node * root){
    int ltr=-1;
    list<node*> current,temp,next;
    current.push_back(root);
    while (1) {
    while (!current.empty()) {
        node * n = current.back();
        current.pop_back();
        cout << n->data << "\t";
        if(ltr>0){
            if(n->right)
                next.push_back(n->right);
            if(n->left)
                next.push_back(n->left);
        }else{
            if(n->left)
                next.push_back(n->left);
            if(n->right)
                next.push_back(n->right);
        }
    }
        if (next.empty()) {
            break;
        }
        ltr = -1*ltr;
        temp = current;
        current = next;
        next = temp;
    }
}

node * tree2dll(node * root, int l){
    if (!root) {
        return NULL;
    }
    node * temp1 = tree2dll(root->left, -1);
    node * temp2 = tree2dll(root->right, 1);
    
    root->left = temp1;
    
    if(temp1)
        temp1->right = root;
    
    root->right = temp2;
    
    if(temp2)
        temp2->left = root;
    
    if (l==1) {
        while (root->left) {
            root=root->left;
        }
    }else{
        while (root->right) {
            root=root->right;
        }
    }
    return root;
}

node * LLmid(node * root){
    node * temp = root;
    while (root) {
        if (root->right) {
            root=root->right->right;
            temp=temp->right;
        }else{
            break;
        }
    }
    return temp;
}

node * Dll2tree(node * head){
    if (!head) {
        return NULL;
    }
    if (!head->left && !head->right){
        return head;
    }
    node * root = LLmid(head);
    node * temp = head;
    if (temp->right) {
        while (temp->right!=root) {
        temp=temp->right;
        }
    }
    temp->right = NULL;
    if (root->right) {
        root->right->left=NULL;
    }
    root->left = NULL;
    root->left = Dll2tree(head);
    root->right = Dll2tree(root->right);
    return root;
}

void del(node ** rt, int data){     // not working!
    node * root = *rt;
    list<node *> l;
    l.push_back(root);
    while (l.front()) {
        node * temp = l.front();
        l.pop_front();
        if (data == temp->data) {
            node * temp2 = temp;
            while (l.front()) {
            temp2 = l.front();
            l.pop_front();
                if (temp2->left) {
                    l.push_back(temp2->left);
                }
                if (temp2->right) {
                    l.push_back(temp2->right);
                }
            }
            temp->data = temp2->data;
            return;
        }
        if (temp->left) {
            l.push_back(temp->left);
        }
        if (temp->right) {
            l.push_back(temp->right);
        }
    }}

int main()
{
    node * root = NULL;
    while (1) {
        cout << "Make a choice" << endl;
        cout << " 1. Insert" << endl;
        cout << " 2. Delete" << endl;
        cout << " 3. Inorder Recursive" << endl;
        cout << " 4. Inorder Iterative" << endl;
        cout << " 5. Preorder Recursive" << endl;
        cout << " 6. Preorder Iterative" << endl;
        cout << " 7. Postorder Recursive" << endl;
        cout << " 8. Postorder Iterative" << endl;
        cout << " 9. Is BST?" << endl;
        cout << " 10. Find element" << endl;
        cout << " 11. Delete Tree" << endl;
        cout << " 12. Height of Tree" << endl;
        cout << " 13. Diameter of Tree" << endl;
        cout << " 14. Paths to leaves" << endl;
        cout << " 15. Paths for a sum" << endl;
        cout << " 16. Mirror-ify tree" << endl;
        cout << " 17. Build tree" << endl;
        cout << " 18. Print the ancestors of a given node" << endl;
        cout << " 19. LCA" << endl;
        cout << " 20. Zigzag traversal" << endl;
        cout << " 21. BT to DLL to BT" << endl;
        
        int ch;
        cin >> ch;
        switch (ch) {
        case 1:
        {
            cout << "Enter data\n";
            int data;
            cin >> data;
            if (root) {
                node * n = new node;
                n->data = data;
                n->left=n->right=NULL;
                insert(&root, n);
            }else{
                root = new node;
                root->data = data;
                root->left = NULL;
                root->right = NULL;
            }
        }
            break;
            
        case 2:
        {
            cout << "Enter the element\n";
            int data;
            cin >> data;
            del(&root, data);
        }
            break;
        
        case 3:
        {
            if (root) {
                inorder(root);
                cout << endl;
            }else{
                cout << "Tree empty\n";
            }
        }
            break;
            
        case 4:
        {
            if (root) {
                InorderIter(root);
                cout << endl;
            }else{
                cout << "Tree empty\n";
            }
        }
            break;
            
        case 5:
        {
            if (root) {
                preorder(root);
                cout << endl;
            }else{
                cout << "Tree empty\n";
            }
        }
            break;
            
        case 6:
        {
            if (root) {
                preorderIter(root);
                cout << endl;
                preorderIter2(root);
                cout << endl;
            }else{
                cout << "Tree empty\n";
            }
        }
            break;
            
        case 7:
        {
            if (root) {
                postorder(root);
                cout << endl;
            }else{
                cout << "Tree empty\n";
            }
        }
            break;
            
        case 8:
        {
            if (root) {
                postorderIter(root);
                cout << endl;
                postorderIter2(root);
                cout << endl;
            }else{
                cout << "Tree empty\n";
            }
        }
            break;
            
        case 9:
        {
            if(isBST(root)){
                cout << "It is BST\n";
            }else{
                cout << "Not BST\n";
            }
        }
            break;
            
        case 10:
        {
            int data;
            cout << "Enter element to find \n";
            cin >> data;
            
            if (find(root, data)) {
                cout << "Found\n";
            }else{
                cout << "Not found\n";
            }
        }
            break;
            
        case 11:
        {
            delTree(&root);
        }
            break;
            
        case 12:
        {
            cout << height(root) << endl;
            cout << heightIter(root) << endl;
        }
            break;
            
        case 13:
        {
            int dia = 0;
            diameter(root, &dia);
            cout << dia << endl;
        }
            break;
            
        case 14:
        {
            int path[100];
            pathToLeaf(root, path, 0);
        }
            break;
            
        case 15:
        {
            int sum;
            int path[100];
            cout << "Enter sum value\n";
            cin >> sum;
            pathsum(root,path,sum,0);
        }
            break;
            
        case 16:
        {
            mirror(&root);
        }
            break;
            
        case 17:
        {
            int preorder[100],inorder[100];
            int n=0;
            cout << "Enter size\n";
            cin >> n;
            cout << "Enter preorder and inorder\n";
            for (int i=0; i<n; i++) {
                cin >> preorder[i];
            }
            for (int i=0; i<n; i++) {
                cin >> inorder[i];
            }
            root = buidTree(inorder, preorder, 0, n-1);
        }
            break;
            
        case 18:
        {
            cout << "Enter value";
            int val;
            cin >> val;
            printAncestors(root, val);
            cout << endl;
        }
            break;
            
        case 19:
        {
            int a,b;
            cout << "Enter the nodes values\n";
            cin >> a >> b;
            node * temp = LCA(root, a, b);
            if (temp) {
                cout << "LCA is " << temp->data << endl;
            }else{
                cout << "No LCA\n";
            }
        }
            break;
         
        case 20:
        {
            if (root) {
                zigzag(root);
                cout << endl;
            }else{
                cout << "Tree empty\n";
            }
        }
            break;
                
        case 21:
            {
                if(root)
                {
                root = tree2dll(root, 1);
                node * ptr = root;
                while (ptr->right) {
                    cout << ptr->data << "\t";
                    ptr=ptr->right;
                }
                cout << ptr->data << "\t";
                cout << endl;
                while (ptr) {
                    cout << ptr->data << "\t";
                    ptr=ptr->left;
                }
                cout << endl;
                }
                    //root = NULL;
                    //free(root);
                root = Dll2tree(root);
                }
                break;
                
        default:
            return 0;
            break;
    }
    }
    return 0;
}