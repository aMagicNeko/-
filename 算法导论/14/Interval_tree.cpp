//
//  Interval_tree.cpp
//  算法导论
//
//  Created by Ekko on 2021/8/3.
//

#include "head.hpp"
using namespace std;
int pow(int n);
template<class T> class interval{
private:
    T low;
    T high;
public:
    T getmin()const{
        return low;
    }
    T getmax()const{
        return high;
    }
    interval(T l, T h){low = l;high =h;}
    bool operator<(interval i)const{
        if(getmin() < i.getmin())
            return true;
        return false;
    }
    bool operator>(interval i)const{
        if(getmin() > i.getmin())
            return true;
        return false;
    }
    bool operator==(interval i)const{
        if(getmin() == i.getmin())
            return true;
        return false;
    }
    bool isoverlap(interval i,bool open)const{
        if(open){
            if((getmin() > i.getmin() && getmin() < i.getmax()) || (i.getmin() > getmin() && i.getmin() < getmax()))
                return true;
            return false;
        }
        if((getmin() >= i.getmin() && getmin() <= i.getmax()) || (i.getmin() >= getmin() && i.getmin() <= getmax()))
            return true;
        return false;
    }
};

template <class T> class interval_tree{
private:
    class node{
    public:
        node* parent;
        node* left;
        node* right;
        bool color;//0: red, 1: black
        interval<T>* val;
        T _max;
        node(T l, T h){
            val = new interval<T>(l, h);
            parent = left = right = NULL;
            color = 0;
        }
        node(){
            val = NULL;
            parent = left = right = NULL;
            color = 0;
        }
        ~node(){
            if(val != NULL)
                delete val;
        }
    };
    node* root;
    node* null;
    void left_rotate(node* p);
    void right_rotate(node* p);
    void transplant(node* u, node* v);
public:
    interval_tree(){
        null = new node;
        root = null;
        null -> color = 1;
    }
    void insert(T l, T h);
    void del(node* p);
    node* search(const interval<T>& i, bool open) const;
    void _inorder_walk(node* p, int depth, node* tree[][100], int n)const;
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
                        cout << '['<<tree[j][i] -> val -> getmin()<<','<<tree[j][i] -> val -> getmax()<< ']' << "max: " << tree[j][i] -> _max << ' ';
                    else
                        cout<<"NULL";
                    if((tree[j][i]) -> color)
                        cout << "black";
                    else
                        cout << "red";
                }
            }
            cout << endl;
        }
        cout << endl;
    }
    ~interval_tree(){
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
        cout << "delete " << n;
    }
    void fix_max(node* p){
        if(p -> left == null && p -> right == null){
            p -> _max = p -> val->getmax();
            return;
        }
        T m;
        if(p -> left != null && p -> right != null){
            m = p -> left -> _max > p -> right -> _max ? p -> left -> _max : p -> right -> _max;
        }
        else if(p -> left != null){
            m = p -> left -> _max;
        }
        else{
            m = p -> right -> _max;
        }
        p -> _max = m > p -> val->getmax() ? m : p -> val->getmax();
    }
};
template <class T> void interval_tree<T>::transplant(node* u, node* v){
    if(root == u){
        root = v;
        return;
    }
    if(u == u -> parent -> left)
        u -> parent -> left = v;
    else
        u -> parent -> right = v;
    v -> parent = u -> parent;//here different from binary_tree, we should point null's parent.
    u = v;
    while(u != root){
        u = u -> parent;
        fix_max(u);
    }
}

template <class T> void interval_tree<T>::_inorder_walk(node* p, int depth, node* tree[][100], int n) const{
    if(p == NULL) return;
    _inorder_walk(p -> left, depth + 1, tree, 2 * n);
    tree[n][depth] = p;
    _inorder_walk(p -> right, depth + 1, tree, 2 * n + 1);
}
template <class T> typename interval_tree<T>::node* interval_tree<T>::search(const interval<T> &key, bool open)const{
    if(open){
        node* x = root;
        while(x != null){
            if(x -> val -> isoverlap(key, 1)){
                return x;
            }
            if(x -> left != null && x -> left -> _max > key.getmin())
                x = x -> left;
            else
                x = x -> right;
        }
        return NULL;
    }
    node* x = root;
    while(x != null){
        if(x -> val -> isoverlap(key, 0)){
            return x;
        }
        if(x -> left != null && x -> left -> _max >= key.getmin())
            x = x -> left;
        else
            x = x -> right;
    }
    return NULL;
}
template <class T> void  interval_tree<T>::left_rotate(node *p){
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
    fix_max(x);
    fix_max(p);
}
template <class T> void  interval_tree<T>::right_rotate(node *p){
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
    fix_max(x);
    fix_max(p);
}
template <class T> void  interval_tree<T>::insert(T l, T h){
    node* p = new node(l, h);
    const interval<T> & key = *(p -> val);
    p -> _max = key.getmax();//attribute max
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
        y = x;
        if(key == *(x -> val)){
            flag = rand() % 2;
        }
        else if(key < *(x -> val))
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
    //fix up attribute max
    y = p;
    while(y != root){
        y = y -> parent;
        fix_max(y);
    }
    y = p -> parent;
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

template<class T> void interval_tree<T>::del(interval_tree<T>::node* p){
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
        transplant(p, y);
        y -> left = p -> left;
        y -> left -> parent = y;
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
/*
int main(){
    interval_tree<int> t;
    int low[]{0,5,6,8,15,17,16,19,25,26};
    int high[]{3,8,10,9,23,19,21,20,30,26};
    for(int i = 0;i < 10; i++){
        t.insert(low[i], high[i]);}
    t.inorder_walk();
    t.del(t.search(interval<int>(6,7), 0));
    t.inorder_walk();
}

*/
