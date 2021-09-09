//
//  order_statistic_tree.cpp
//  算法导论
//
//  Created by Ekko on 2021/7/28.
//

#include "head.hpp"
using namespace std;
int pow(int n);
template <class T> class order_statistic_tree{
private:
    class node{
    public:
        node* parent;
        node* left;
        node* right;
        bool color;//0: red, 1: black
        T val;
        int size;
        node(){
            parent = left = right = NULL;
            color = 0;
        }
    };
    node* root;
    node* null;
    void left_rotate(node* p);
    void right_rotate(node* p);
    void transplant(node* u, node* v);
public:
    order_statistic_tree(){
        null = new node;
        root = null;
        null -> color = 1;
        null -> size = 0;
    }
    void insert(T key);
    void del(node* p);
    node* search(T key) const;
    void _inorder_walk(node* p, int depth, node* tree[][100], int n)const;
    node* successor(node* p)const{
        if(p -> rc != null){
            node* x = p -> right;
            node* y;
            while(x != null){
                y = x;
                x = x -> left;
            }
            return y;
        }
        node* x = p -> parent;
        while(x != null && x -> left != p){
            p = x;
            x = x -> parent;
        }
        return x;
    }
    node* max()const{
        if(root == null)
            return NULL;
        node* now = root;
        while(now -> right != null){
            now = now -> right;
        }
        return now;
    }
    node* min()const{
        if(root == null)
            return NULL;
        node* now = root;
        while(now -> left != null){
            now = now -> left;
        }
        return now;
    }
    node* precessor(node* p)const{
        if(p -> left != null){
            node* x = p -> left;
            node* y;
            while(x != null){
                y = x;
                x = x -> right;
            }
            return y;
        }
        node* x = p -> parent;
        while(x != null && x -> right != p){
            p = x;
            x = x -> parent;
        }
        return x;
    }
    void inorder_walk() const{
        node* x = root;
        int d = 0;
        while(x != null){
            x = x -> left;
            ++d;
        }
        if(2 * d > 100)throw("overflow");
        int max = pow(2 * d);
        node* tree[max][100];
        for(int i = 0; i < 100; i++){
            for(int j = 0; j < max; j++)
                tree[j][i] = NULL;
        }
        _inorder_walk(root, 0, tree, 0);
        for(int i = 0; i < 2 * d; i++){
            for(int j = 0; j < max; j++){
                if(tree[j][i] != NULL){
                    if(tree[j][i] != null)
                        cout << (tree[j][i]) -> val;
                    else
                        cout << "NULL";
                    if((tree[j][i]) -> color)
                        cout << "black";
                    else
                        cout << "red";
                    cout<< "size" << tree[j][i] -> size << "  ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }
    ~order_statistic_tree(){
        int n = 0;
        Stack<node*> s;
        node* now = root;
        node* tmp;
        while(true){
            if(now != null){
                s.push(now);
                now = now -> left;
            }
            else if(!s.isempty()){
                now = s.pop();
                tmp = now -> right;
                delete now;
                now = tmp;
                n++;
            }
            else{
                break;
            }
        }
        delete null;
        cout << "delete " << n << endl;
    }
    node* _select(node* x, int i)const;
    node* select(int i) const{//start from 1st
        return _select(root, i);
    }
    int rank(node* x)const;//start from 1st
};
template <class T> void order_statistic_tree<T>::transplant(node* u, node* v){
    if(root == u){
        root = v;
        return;
    }
    if(u == u -> parent -> left)
        u -> parent -> left = v;
    else
        u -> parent -> right = v;
    v -> parent = u -> parent;//here different from binary_tree, we should point null's parent.
    //fix up attribute size
    while(v != root){
        v = v -> parent;
        v -> size = v -> left -> size + v -> right -> size + 1;
    }
}

template <class T> void order_statistic_tree<T>::_inorder_walk(node* p, int depth, node* tree[][100], int n) const{
    if(p == NULL) return;
    _inorder_walk(p -> left, depth + 1, tree, 2 * n);
    tree[n][depth] = p;
    _inorder_walk(p -> right, depth + 1, tree, 2 * n + 1);
}
template <class T> typename order_statistic_tree<T>::node* order_statistic_tree<T>::search(T key)const{
    node* x = root;
    while(x != null){
        if(key == x -> val)
            return x;
        if(key < x -> val)
            x = x -> left;
        else
            x = x -> right;
    }
    return NULL;
}
template <class T> void  order_statistic_tree<T>::left_rotate(node *p){
    node* x = p -> right;
    if(p != root)
        if(p == p -> parent -> left)
            p -> parent -> left = x;
        else
            p -> parent -> right = x;
    else
        root = x;
    x -> parent = p -> parent;
    node* tmp = x -> left;
    x -> left = p;
    p -> parent = x;
    p -> right = tmp;
    if(tmp != null)
        tmp -> parent = p;//note here! Don't change the null's parent for del.
    //fix up attribute size
    x -> size = p -> size;
    p -> size = p -> left -> size + p -> right -> size + 1;
}
template <class T> void  order_statistic_tree<T>::right_rotate(node *p){
    node* x = p -> left;
    if(p != root)
        if(p == p -> parent -> left)
            p -> parent -> left = x;
        else
            p -> parent -> right = x;
    else
        root = x;
    x -> parent = p -> parent;
    node* tmp = x -> right;
    x -> right = p;
    p -> parent = x;
    p -> left = tmp;
    if(tmp != null)
        tmp -> parent = p;//note here! Don't change the null's parent for del.
    //fix up attribute size
    x -> size = p -> size;
    p -> size = p -> left -> size + p -> right -> size + 1;
}
template <class T> void  order_statistic_tree<T>::insert(T key){
    node* p = new node;
    p -> val = key;
    p -> size = 1;
    if(root == null){
        root = p;
        p -> left = null;
        p -> right = null;
        p -> color = 1;
        p -> parent = null;
        return;
    }
    node* x = root;
    node* y;
    int flag;
    while(x != null){
        x -> size += 1;
        y = x;
        if(key == x -> val){
            flag = rand() % 2;
        }
        else if(key < x -> val)
            flag = 0;
        else
            flag = 1;
        if(flag == 0)
            x = x -> left;
        else
            x = x -> right;
    }
    if(flag == 0)
        y -> left = p;
    else
        y -> right = p;
    p -> parent = y;
    p -> right = p -> left = null;
    //fix up
    while(y -> color == 0){
        if(y == y -> parent -> left){
            x = y -> parent -> right;
            if(x -> color == 0){
                y -> color = 1;
                x -> color =1;
                y -> parent -> color = 0;
                y = y -> parent -> parent;
                p = p -> parent -> parent;
            }
            else{
                if(p == y -> right){
                    left_rotate(y);
                    x = y;
                    y = p;
                    p = x;
                }
                y -> parent -> color = 0;
                y -> color = 1;
                right_rotate(y -> parent);
            }
        }
        else{
            x = y -> parent -> left;
            if(x -> color == 0){
                y -> color = 1;
                x -> color =1;
                y -> parent -> color = 0;
                y = y -> parent -> parent;
                p = p -> parent -> parent;
            }
            else{
                if(p == y -> left){
                    right_rotate(y);
                    x = y;
                    y = p;
                    p = x;
                }
                y -> parent -> color = 0;
                y -> color = 1;
                left_rotate(y -> parent);
            }
        }
    }
    root -> color = 1;
}

template<class T> void order_statistic_tree<T>::del(order_statistic_tree<T>::node* p){
    bool original_color = p -> color;
    node* x = p;
    if(p -> left == null){
        transplant(p, p -> right);
        x = p -> right;
    }
    else if(p -> right == null){
        transplant(p, p -> left);
        x = p -> left;
    }
    else{
        x = p -> right;
        node* y;
        while(x != null){
            y = x;
            x = x -> left;
        }
        original_color = y -> color;
        x = y -> right;
        if(y -> parent != p){
            transplant(y, x);
            y -> right = p -> right;
            y -> right -> parent = y;
        }
        else{
            x -> parent = y;//point null's parent to y!
        }
        y -> left = p -> left;
        y -> left -> parent = y;
        y -> size = y -> left -> size + y -> right -> size + 1;
        transplant(p, y);// note that transplant fix up nodes upon y, so size of y should be fixed up first.
        y -> color = p -> color;
        delete p;
    }
    if(original_color == 1){
        //fix up
        node* w;
        while(x != root && x -> color == 1){
            if(x == x -> parent -> left){
                w = x -> parent -> right;
                if(w -> color == 0){
                    w -> color = 1;
                    x -> parent -> color = 0;
                    left_rotate(x -> parent);
                    w = x -> parent -> right;
                }
                if(w -> right -> color == 1 && w -> left -> color == 1){
                    w -> color = 0;
                    x = x -> parent;
                }
                else{
                    if(w -> right -> color == 1){
                        w -> left -> color = 1;
                        w -> color = 0;
                        right_rotate(w);
                        w = x -> parent -> right;
                    }
                    w -> color = x -> parent -> color;
                    x -> parent -> color = 1;
                    w -> right -> color = 1;
                    left_rotate(x -> parent);
                    x = root;
                }
            }
            else{
                w = x -> parent -> left;
                if(w -> color == 0){
                    w -> color = 1;
                    x -> parent -> color = 0;
                    right_rotate(x -> parent);
                    w = x -> parent -> left;
                }
                if(w -> left -> color == 1 && w -> right -> color == 1){
                    w -> color = 0;
                    x = x -> parent;
                }
                else{
                    if(w -> left -> color == 1){
                        w -> right -> color = 1;
                        w -> color = 0;
                        left_rotate(w);
                        w = x -> parent -> left;
                    }
                    w -> color = x -> parent -> color;
                    x -> parent -> color = 1;
                    w -> left -> color = 1;
                    right_rotate(x -> parent);
                    x = root;
                }
            }
        }
        x -> color = 1;
    }
}
template<class T> typename order_statistic_tree<T>::node* order_statistic_tree<T>::_select(node* x, int i)const{
    int r = x -> left -> size + 1;
    if(i == r)
        return x;
    if(i < r)
        return _select(x -> left, i);
    return _select(x -> right, i - r);
}

template<class T> int order_statistic_tree<T>::rank(node* x)const{
    int r = x -> left -> size + 1;
    while(x != root){
        if(x == x -> parent -> right)
            r += x -> parent -> left -> size + 1;
        x = x -> parent;
    }
    return r;
}
/*
int main(){
    order_statistic_tree<int> t;
    int arr[12]{2,5,1,6,2,8,3,4,6,7,3,2};
    for(int i = 0;i < 12; i++)
        t.insert(arr[i]);
    t.inorder_walk();
    t.del(t.search(2));
    t.inorder_walk();
    t.del(t.search(6));
    t.inorder_walk();
    cout << t.rank(t.search(7)) << endl;
    cout << (t.select(9) -> val);
}
*/
