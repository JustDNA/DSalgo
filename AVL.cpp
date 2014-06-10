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
    if (!X->left || !X->left->right) {
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
    if (!X->right || !X->right->left) {
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

int main()
{
    
    return 0;
}