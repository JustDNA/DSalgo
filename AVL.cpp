#include <iostream>
using namespace std;

struct node {
    node * left;
    node * right;
    int ht;
    int data;
};

int max(int a, int b){
    return ((a>b)?a:b);
}

int AVLht(node * root){
    if (!root) {
        return 0;
    }
    return root->ht;
}

node * rotateRight(node * X){
    if (!X) {
        return NULL;
    }
    if (!X->left) {
        return X;
    }
    node * Y = X->left;
    X->left = Y->right;
    Y->right = X;
    X->ht = max(AVLht(X->left),AVLht(X->right)) + 1;
    Y->ht = max(AVLht(Y->left),AVLht(Y->right)) + 1;
    return Y;
}

node * rotateLeft(node * X){
    if (!X) {
        return NULL;
    }
    if (!X->right) {
        return X;
    }
    node * Y = X->right;
    X->right = Y->left;
    Y->left = X;
    X->ht = max(AVLht(X->left),AVLht(X->right)) + 1;
    Y->ht = max(AVLht(Y->left),AVLht(Y->right)) + 1;
    return Y;
}

node * doubleRotateLeft(node * X){
    if (!X) {
        return NULL;
    }
    X->left = rotateLeft(X->left);
    return rotateRight(X);
}

node * doubleRotateRight(node * X){
    if (!X) {
        return NULL;
    }
    X->right = rotateRight(X->right);
    return rotateLeft(X);
}

node * insert(node * root, int data){
    if (!root) {
        root = new node;
        root->data = data;
        root->left = root->right = NULL;
        root->ht = 1;
        return root;
    }
    if (root->data > data) {
        root->left = insert(root->left, data);
        if (AVLht(root->left)-AVLht(root->right) == 2) {
            if (data > root->left->data) {
                root = doubleRotateLeft(root);
            }else if (data < root->left->data){
                root = rotateRight(root);
            }
        }
    }else if (root->data < data) {
        root->right = insert(root->right, data);
        if (AVLht(root->right)-AVLht(root->left) == 2) {
            if (data < root->right->data) {
                root = doubleRotateRight(root);
            }else if (data > root->right->data){
                root = rotateLeft(root);
            }
        }
    }
    root->ht = max(AVLht(root->left),AVLht(root->right)) + 1;
    return root;
}

node * fullBST(int n, int * count){
    node * root = new node;
    if (!n) {
        return NULL;
    }
    root->left = fullBST(n-1, count);
    root->data = (*count)++;
    root->right = fullBST(n-1, count);
    root->ht = max(AVLht(root->left),AVLht(root->right)) + 1;
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

int main()
{
    node * root = new node;
    root = NULL;
    while(1){
        cout << "Enter a choice" << endl;
        cout << " 1. Insert" << endl;
        cout << " 2. Delete" << endl;
        cout << " 3. Inorder traverse" << endl;
        cout << " 4. Preorder traverse" << endl;
        cout << " 5. Postorder traverse" << endl;
        cout << " 6. Build full tree" << endl;
        
        int ch;
        cin >> ch;
        switch (ch) {
            case 1:
            {
                cout << "Enter value\n";
                int data;
                cin >> data;
                root = insert(root, data);
            }
                break;
                
            case 2:
            {
                cout << "Facility not available yet\n";
            }
                break;
                
            case 3:
            {
                if (root) {
                    cout << "Height of tree: " << AVLht(root) << endl;
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
                
            case 6:
            {
                int ht,count=1;
                cout << "Enter height\n";
                cin >> ht;
                root = fullBST(ht, &count);
            }
                break;
                
                break;
            default:
                break;
        }
    }
    return 0;
}