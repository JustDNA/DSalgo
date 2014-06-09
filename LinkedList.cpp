#include <iostream>
using namespace std;

struct node{
    int data;
    struct node* next;
};

void insert(node ** head, int data){
    node * temp = new node;
    temp->data = data;
    temp->next = *head;
    *head = temp;
}

void del(node ** head, int data){
    node * current = new node;
    current = *head;
    if ((*head)->data==data) {
        (*head)=(*head)->next;
        free(current);
    }else{
        while (current->next != NULL && current->next->data!=data) {
            current = current->next;
        }
        if (!current->next && current->data!=data) {
            cout << "Element not found in the list\n";
        }else{
            node * temp = new node;
            temp = current->next;
            current->next = current->next->next;
            free(temp);
        }
    }
}

void traverse(node ** head){
    node * current = new node;
    current = *head;
    while (current->next!=NULL) {
        cout << current->data << "\t";
        current = current->next;
    }
    cout << current->data << endl;
    //free(current);   DONOT DO THIS
}

void reverse(node ** head){
    node * t1 = new node;
    node * t2 = new node;
    node * t3 = new node;
    if (!(*head)->next) {
        return;
    }else{
        t1 = *head;
        t2 = (*head)->next;
        t3 = (*head)->next->next;
        t1->next = NULL;
        while (t3) {
            t2->next = t1;
            t1 = t2;
            t2 = t3;
            t3 = t3->next;
        }
        t2->next = t1;
        *head = t2;
    }
}

void recurseRev(node ** head){
    if (!*head) {
        return;
    }
    node * first = *head;
    node * rest = (*head)->next;
    if (!rest) {
        return;
    }
    recurseRev(&rest);
    first->next->next = first;
    first->next = NULL;
    *head = rest;
}

node * isK(node * head, int k){
    int l=1;
    if (!head) {
        return NULL;
    }
    while (head->next && l<k) {
        head = head->next;
        l++;
    }
    return head;
}

void revChunk(node ** head, int k){
    if (k==0||k==1) {
        return;
    }
    node * t1 = new node;
    node * t2 = new node;
    node * t3 = new node;
    node * tem = *head;
    node * tem2;
    node * tem3;
    *head = isK(tem, k);
    while (tem) {
        tem2 = isK(tem, k);
        tem3 = tem2->next;
        tem2->next = NULL;
        if (!(tem)->next) {
            break;
        }else{
            t1 = tem;
            t2 = tem->next;
            t3 = tem->next->next;
            t1->next = NULL;
            while (t3) {
                t2->next = t1;
                t1 = t2;
                t2 = t3;
                t3 = t3->next;
            }
            t2->next = t1;
        }
        tem->next = isK(tem3, k);
        tem = tem3;
    }
}

void delList(node ** head){
    node * temp = *head;
    *head = (*head)->next;
    free(temp);
    while (*head) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *head = NULL;
}

int main()
{
    int ch;
    node * head = NULL;
    
    while (1) {
        
    cout << "Enter your choice" << endl;
    cout << " 1. Insert a node" << endl;
    cout << " 2. Delete a node" << endl;
    cout << " 3. Traverse the list" << endl;
    cout << " 4. Reverse the list" << endl;
    cout << " 5. Reverse the list recursively" << endl;
    cout << " 6. Delete the entire linked list" << endl;
    cout << " 7. Reverse in chunks of K" << endl;
    cin >> ch;
    switch (ch) {
        case 1:
        {
            cout << "Enter the data\n";
            int n;
            cin >> n;
            if (head) {
                insert(&head, n);
            }else{
                node * temp = new node;
                temp->data = n;
                head = temp;
                head->next=NULL;
            }
        }
            break;
        case 2:
        {
            cout << "Enter the node (data) to be deleted\n";
            int n;
            cin >> n;
            if (head) {
                del(&head, n);
            }else{
                cout << "List is empty" << endl;
            }
        }
            break;
        case 3:
        {
            if (head) {
                traverse(&head);
            }else{
                cout << "List is empty" << endl;
            }
        }
            break;
        case 4:
        {
            if (head) {
                reverse(&head);
            }else{
                cout << "List is empty" << endl;
            }
        }
            break;
        case 5:
        {
            if (head) {
                recurseRev(&head);
            }else{
                cout << "List is empty" << endl;
            }
        }
            break;
        case 6:
        {
            if (head) {
                delList(&head);
            }else{
                cout << "List is empty" << endl;
            }
        }
            break;
        case 7:
        {
            int k;
            cout << "Enter K\n";
            cin >> k;
            if (head) {
                revChunk(&head,k);
            }else{
                cout << "List is empty" << endl;
            }
        }
            break;
        default:
            exit(0);
            break;
        }
    }
    return 0;
}

