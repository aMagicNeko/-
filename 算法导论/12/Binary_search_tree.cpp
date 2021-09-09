//
//  Binary_search_tree.cpp
//  算法导论
//
//  Created by Ekko on 2021/7/14.
//

#include "head.hpp"

using namespace std;

class binary_search_tree{
private:
    class node{
        public:
            int val;
            node* parent;
            node* rc;
            node* lc;
        node(){
            parent = rc = lc = NULL;
        }
    };
    node* root;
public:
    binary_search_tree(){
        root = NULL;
    }
    void transplant(node* u, node* v){
        if(root == u){
            root = v;
            return;
        }
        if(u == u -> parent -> lc)
            u -> parent -> lc = v;
        else
            u -> parent -> rc = v;
        if(v != NULL)
            v -> parent = u -> parent;
    }
    void insert(int key){
        node* p = new node;
        p -> val = key;
        if(root == NULL){
            root = p;
            return;
        }
        node* x = root;
        node* y;
        int flag;
        while(x != NULL){
            y = x;
            if(x -> val < key){
                flag = 0;
            }
            else if(x -> val > key){
                flag = 1;
            }
            else{
                flag = rand() % 2;
            }
            switch (flag) {
                case 0:
                    x = x -> rc;
                    break;
                case 1:
                    x = x -> lc;
                    break;
            }
        }
        switch (flag) {
            case 0:
                y -> rc = p;
                break;
            case 1:
                y -> lc = p;
                break;
        }
        p -> parent = y;
    }
    void del(node * p){
        if(p -> lc == NULL){
            transplant(p, p -> rc);
            return;
        }
        if(p -> rc == NULL){
            transplant(p, p -> lc);
            return;
        }
        node* x = p -> rc;
        node* y;
        while(x != NULL){
            y = x;
            x = x -> lc;
        }
        if(y != p -> rc){
            transplant(y, y -> rc);
            y -> rc = p -> rc;
            if(p -> rc != NULL)
                p -> rc -> parent = y;
        }
        transplant(p, y);
        y -> lc = p -> lc;
        y -> lc -> parent = y;
        delete p;
    }
    node* search(int key) const{
        node* x = root;
        while(x != NULL){
            if(x -> val < key)
                x = x -> rc;
            else if(x -> val > key)
                x = x -> lc;
            else
                return x;
        }
        return x;
    }
    void inorder_walk() const{
        Stack<node*> s;
        node* now = root;
        while(true){
            if(now != NULL){
                s.push(now);
                now = now -> lc;
            }
            else if(!s.isempty()){
                now = s.pop();
                cout << now -> val << endl;
                now = now -> rc;
            }
            else{
                break;
            }
        }
    }
    ~binary_search_tree(){
        int n = 0;
        Stack<node*> s;
        node* now = root;
        node* tmp;
        while(true){
            if(now != NULL){
                s.push(now);
                now = now -> lc;
            }
            else if(!s.isempty()){
                now = s.pop();
                tmp = now -> rc;
                delete now;
                now = tmp;
                n++;
            }
            else{
                break;
            }
        }
        cout << "delete " << n;
    }
    node* successor(node* p) const{
        if(p -> rc != NULL){
            node* x = p -> rc;
            node* y;
            while(x != NULL){
                y = x;
                x = x -> lc;
            }
            return y;
        }
        node* x = p -> parent;
        while(x != NULL && x -> lc != p){
            p = x;
            x = x -> parent;
        }
        return x;
    }
    friend ostream& operator<<(ostream& os, const binary_search_tree& t);
};
ostream& operator<<(ostream& os, const binary_search_tree& t){
    binary_search_tree::node* p = t.root;
    while(p -> lc != NULL)
        p = p -> lc;
    while(p != NULL){
        os << p -> val;
        p = t.successor(p);
    }
    return os;
}
/*
int main(){
    binary_search_tree t;
    int arr[12]{2,5,1,6,2,8,3,4,6,7,3,2};
    for(int i = 0;i < 12; i++)
        t.insert(arr[i]);
    t.inorder_walk();
    t.del(t.search(5));
    t.inorder_walk();
    cout << t;
}

*/
