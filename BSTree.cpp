#include <iostream>
#include <list>
using namespace std;

struct node{
    int data;
    node * left = NULL;
    node * right = NULL;
};

void insertRandom(node ** rt, node * n){
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


node * inorderSuc(node * root){
    if (!root) {
        return NULL;
    }
    
    if(root->right)
    {
        root=root->right;
        while (root->left) {
            root=root->left;
        }
        return root;
    }
    return NULL;
}

node * inorderPre(node * root){
    if (!root) {
        return NULL;
    }
    
    if(root->left)
    {
     root=root->left;
        while (root->right) {
            root=root->right;
        }
        return root;
    }
    return NULL;
}

node * insert(node * root, int data){
    if (!root) {
        root = new node;
        root->data = data;
        root->left = root->right = NULL;
        return root;
    }
    if (root->data > data) {
        root->left = insert(root->left, data);
    }
    if (root->data < data) {
        root->right = insert(root->right, data);
    }
    return root;
}

node * del(node * root, int n){
    if (!root) {
        return NULL;
    }
    if (root->data == n) {
        if (root->right && root->left) {
            node * nd = inorderSuc(root);
            if (nd) {
                root->data = nd->data;
                root->right = del(root->right, nd->data);
            }
        }else if(root->right && !root->left)
        {
            node * temp = root->right;
            root = NULL;
            free(root);
            return temp;
        }else if(root->left && !root->right)
            {
                node * temp = root->left;
                root = NULL;
                free(root);
                return temp;
            }
        if (!root->left && !root->right) {
            root=NULL;
            free(root);
            }
        }
    else if (root->data > n){
        root->left = del(root->left, n);
    }else if (root->data < n){
        root->right = del(root->right, n);
    }
    return root;
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

node * LCA(node * root, int a, int b){
    node * n = root;
    if (!root) {
        return NULL;
    }
    if (root->data > a && root->data > b) {
        n = LCA(root->left, a, b);
    }else if(root->data < a && root->data < b){
        n = LCA(root->right, a, b);
    }
    return n;
}

node * LCAiter(node * root, int a, int b){
    while (1) {
        if (!root) {
            return NULL;
        }
        if (root->data > a && root->data > b) {
            root = root->left;
        }else if(root->data < a && root->data < b){
            root = root->right;
        }else{
            return root;
        }
    }
}

int config(int n, int a[]){
    if (n<=1) {
        return 1;
    }
    if (a[n]) {
        return a[n];
    }
    for (int i=1; i<=n; i++) {
        a[n] += config(n-i, a) * config(i-1, a);
    }
    return a[n];
}

bool isBSTbest(node * root, int * prev){
    if (!root) {
        return true;
    }
    bool b = isBSTbest(root->left, prev);
    if (b) {
        if (root->data > *prev) {
            b = true;
            *prev = root->data;
        }else{
            b = false;
        }
    }
    if (b) {
        b = isBSTbest(root->right, prev);
    }
    return b;
}

node * BST2dll(node * root, node **prev){
    if (!root) {
        return NULL;
    }
    BST2dll(root->left,prev);
    root->left = *prev;
    if (*prev) {
        (*prev)->right = root;
    }
    *prev = root;
    BST2dll(root->right,prev);
    return root;
}

node * BST2dlliter(node * root){
    node * prev = NULL;
    node * temp = root;
        list<node *> l;
        while (1) {
            while (root) {
                l.push_front(root);
                root = root->left;
            }
            if (l.empty()) {
                break;
            }
            root = l.front();
            l.pop_front();
            root->left = prev;
            if (prev) {
                prev->right = root;
            }
            prev = root;
            root = root->right;
        }
    if(temp){
    while (temp->left) {
        temp = temp->left;
    }
        return temp;
    }
    return NULL;
}

node * DLL2bstUtil(node ** head, int n){
    if (n<=0) {
        return NULL;
    }
    node * left = DLL2bstUtil(head, n/2);
    node * root = new node;
    root->data = (*head)->data;
    root->left = left;
    (*head) = (*head)->right;
    root->right = DLL2bstUtil(head, n-(n/2)-1);
    return root;
}

node * DLL2bst(node * temp){
    if (!temp) {
        return NULL;
    }
    int count = 1;
    node * head = temp;
    while (temp->right) {
        temp = temp->right;
        count++;
    }
    return DLL2bstUtil(&head, count);
}

node * floorNode(node * root, node ** prev, int data){
    if (!root) {
        return NULL;
    }
    node * floor = new node;
    floor = NULL;
    floor = floorNode(root->left,prev,data);
    if (!floor) {
        if (root->data > data) {
            floor = *prev;
        }else if(root->data == data){
            floor = root;
        }
    }
    *prev = root;
    if (!floor) {
        floor = floorNode(root->right,prev,data);
    }
    return floor;
}
/*
void range(node * root, int a, int b){
    if (!root) {
        return;
    }
    if (root->data > a && root->data < b) {
        cout << root->data << "\t";
        range(root->left, a, b);
        range(root->right, a, b);
    }else if (root->data < a){
        range(root->right, a, b);
    }else if (root->data > b){
        range(root->left, a, b);
    }
}
*/
void range(node * root, int a, int b){
    if (!root) {
        return;
    }
    if (root->data > a){
        range(root->left, a, b);
    }
    if (root->data > a && root->data < b) {
        cout << root->data << "\t";
    }
    if (root->data < b){
        range(root->right, a, b);
    }
}

int main()
{
    node * root = NULL;
    while (1) {
        cout << "Make a choice" << endl;
        cout << " 1. Insert" << endl;
        cout << " 2. Delete" << endl;
        cout << " 3. Inorder traversal" << endl;
        cout << " 4. Preorder trasversal" << endl;
        cout << " 5. Post traversal" << endl;
        cout << " 6. LCA" << endl;
        cout << " 7. Possible configs" << endl;
        cout << " 8. isBST" << endl;
        cout << " 9. BST to DLL" << endl;
        cout << " 10. BST to DLL iterative" << endl;
        cout << " 11. Floor" << endl;
        cout << " 12. Range print" << endl;
        int ch;
        cin >> ch;
        switch (ch) {
            case 1:
            {
                cout << "Enter data\n";
                int data;
                cin >> data;
                root = insert(root, data);
                break;
                
            case 2:
            {
                cout << "Enter the element\n";
                int data;
                cin >> data;
                root = del(root, data);
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
                        preorder(root);
                        cout << endl;
                    }else{
                        cout << "Tree empty\n";
                    }
                }
                break;
                
            case 5:
                {
                    if (root) {
                        postorder(root);
                        cout << endl;
                    }else{
                        cout << "Tree empty\n";
                    }
                }
                break;
                
            case 6:
                {
                    int a,b;
                    cout << "Enter a,b\n";
                    cin >> a >> b;
                    node * n = LCA(root, a, b);
                    if(n){
                        cout << "LCA is " << n->data << endl;
                    }else{
                        cout << "No LCA\n";
                    }
                    node * n2 = LCAiter(root, a, b);
                    if(n2){
                        cout << "LCAiter is " << n2->data << endl;
                    }else{
                        cout << "No LCA\n";
                        
                    }
                }
                break;
                
            case 7:
                {
                    int n;
                    cout << "Enter n\n";
                    cin >> n;
                    int a[n+1];
                    for (int i=0; i<=n; i++) {
                        a[i] = 0;
                    }
                    cout << config(n,a) << endl;
                }
                break;
                
            case 8:
                {
                    int * prev = new int;
                    *prev = -1000;
                    cout << "insert random node??\n";
                    int ch;
                    cin >> ch;
                    if (ch) {
                        cout << "Enter node val\n";
                        int data;
                        cin >> data;
                        node * n = new node;
                        n->data = data;
                        n->left = n ->right = NULL;
                        insertRandom(&root, n);
                    }
                    cout << isBSTbest(root, prev) << endl;
                }
                break;
                
            case 9:
                {
                    node * prev = new node;
                    prev = NULL;
                    root = BST2dll(root, &prev);
                    if (root) {
                        while (root->left) {
                            root = root->left;
                        }
                    }
                    if (root) {
                        while (root) {
                            cout << root->data << "\t" ;
                            root = root->right;
                        }
                        cout << endl;
                    }
                }
                break;
                
            case 10:
                {
                    root = BST2dlliter(root);
                    node * n = root;
                    if (root) {
                        while (root) {
                            cout << root->data << "\t" ;
                            root = root->right;
                        }
                        cout << endl;
                    }
                    root = DLL2bst(n);
                }
                break;
                
            case 11:
                {
                    int n;
                    node * prev = new node;
                    prev = NULL;
                    cout << "Enter n\n";
                    cin >> n;
                    node * nd = floorNode(root, &prev, n);
                    if (nd) {
                        cout << nd->data << endl;
                    }else{
                        cout << prev->data << endl;
                    }
                }
                break;
                
            case 12:
                {
                    int a,b;
                    cout << "Give the bounds\n";
                    cin >> a >> b;
                    range(root, a, b);
                    cout << endl;
                }
                break;
                
            default:
                return 0;
                break;
        }
    }
    }
    return 0;
}

