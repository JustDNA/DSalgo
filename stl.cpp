#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

void vectorSTL(){
    vector<int> v;
    for (int i=10; i>0; i--) {
        v.push_back(rand()%10);
    }
    cout << v.front() << endl;
    cout << v.back() << endl;
    for (int i=0; i<v.size(); i++) {
        cout << v[i] << "\t";
    }
    cout << endl;
    sort(v.begin(), v.end());
    for (int i=0; i<v.size(); i++) {
        cout << v[i] << "\t";
    }
    cout << endl;
    vector<int>::iterator it = v.begin();
    while (it!=v.end()) {
        cout << *it << "\t";
        it++;
    }
    cout << endl;
    random_shuffle(v.begin(), v.end());
    while (v.size()>0) {
        cout << v.back();
        v.pop_back();
        cout << "\t";
    }
}

void listSTL(){         // sort, random, etc are not supported for lists(doubly linked)
    list<int> l;
    for (int i=0; i<10; i++) {
        l.push_back(i);
        l.push_front(i+10);
    }
    while (l.size()>0) {
        cout << l.back() << "\t";
        l.pop_back();
    }
    cout << endl;
    for (int i=0; i<10; i++) {
        l.push_back(i);
        l.push_front(i+10);
    }
    while (l.size()>0) {
        cout << l.front() << "\t";
        l.pop_front();
    }
    cout << endl;
}

void deQuSTL(){     // double ended queue - can be used as list+vector
    deque<int> d;
    for (int i=0; i<10; i++) {
        d.push_back(i);
        d.push_front(i+10);
    }
    while (d.size()>0) {
        cout << d.back() << "\t";
        d.pop_back();
    }
    cout << endl;
    for (int i=0; i<10; i++) {
        d.push_back(i);
        d.push_front(i+10);
    }
    while (d.size()>0) {
        cout << d.front() << "\t";
        d.pop_front();
    }
    cout << endl;
    for (int i=0; i<10; i++) {
        d.push_back(i);
        d.push_front(i+10);
    }
    for(int i=0;i<d.size();i++) {
        cout << d[i] << "\t";
    }
    cout << endl;
    sort(d.begin(), d.end());
    for(int i=0;i<d.size();i++) {
        cout << d[i] << "\t";
    }
    cout << endl;
}

void setSTL(){
    set<int> s;     // equivalent to set <int , greater <int>> s;
    multiset<int> s3;
    set <int , greater <int>> s2;
    for (int i=0; i<10; i++) {
        s.insert(rand()%10);
        s2.insert(rand()%10);
        s3.insert(rand()%10);
    }
    set<int>::iterator it = s.begin();
    while (it!=s.end()) {
        cout << *it << "\t";
        it++;
    }
    cout << endl;
    set<int>::iterator it3 = s3.begin();
    while (it3!=s3.end()) {
        cout << *it3 << "\t";
        it3++;
    }
    cout << endl;set<int>::iterator it2 = s2.begin();
    while (it2!=s2.end()) {
        cout << *it2 << "\t";
        it2++;
    }
    cout << endl;
}

struct node{
    int data1;
    int data2;
};

void HashMap()
{
    map<string, long> hash;
    char buf[256];
    int n=5;
    while (n-- && cin >> buf)
    {
        hash[buf]++;
    }
    map<string, long, less<string> >::iterator it = hash.begin();
    while (it != hash.end()) {
        cout << (*it).first << " " << (*it).second << endl;
        it++;
    }
    cout << endl;
    /*      DOES NOT WORK
    map<node, long> hash2;
    node nd[10];
    for (int i=0; i<10; i++) {
        nd[i].data1 = rand()%3;
        nd[i].data2 = rand()%3;
        hash2[nd[i]]++;
    }
    map<node, long>::iterator it2 = hash2.begin();
    while (it2 != hash2.end()) {
        cout << ((*it2).first).data1 << " " << ((*it2).first).data2 << " " << (*it2).second << endl;
        it2++;
    }
    cout << endl;
     */
}

int main()
{
    int ch;
    cout << "Choose one of the below" << endl;
    cout << " 1. Vector" << endl;
    cout << " 2. List" << endl;
    cout << " 3. Deque" << endl;
    cout << " 4. Set" << endl;
    cout << " 5. Hash Map" << endl;
    cin >> ch;
    switch (ch) {
        case 1:
            vectorSTL();
            break;
        case 2:
            listSTL();
            break;
        case 3:
            deQuSTL();
            break;
        case 4:
            setSTL();
            break;
        case 5:
            HashMap();
            break;
        default:
            break;
    }
    return 0;
}

