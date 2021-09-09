//
//  Optimal_binary_search_tree.cpp
//  算法导论
//
//  Created by Ekko on 2021/8/11.
//

#include "head.hpp"
using namespace std;
int pow(int);
template<class T, class U>class optimal_BST{
private:
    class node{
    public:
        node* parent;
        node* left;
        node* right;
        T val;
    };
    node* root;
public:
    optimal_BST(T* arr1, U* prob1, T* arr2, U* prob2, int n);
    ~optimal_BST(){
        int n = 0;
        Stack<node*> s;
        node* now = root;
        node* tmp;
        while(true){
            if(now != NULL){
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
        cout << "delete " << n;
    }
    void _inorder_walk(node* p, int depth, node* tree[][100], int n)const{
        if(p == NULL) return;
        _inorder_walk(p -> left, depth + 1, tree, 2 * n);
        tree[n][depth] = p;
        _inorder_walk(p -> right, depth + 1, tree, 2 * n + 1);
    }
    void inorder_walk() const{
        node* x = root;
        int d = 0;
        while(x != NULL){
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
                    if(tree[j][i] != NULL)
                        cout << (tree[j][i]) -> val <<' ';
                }
            }
            cout << endl;
        }
        cout << endl;
    }
};
template<class T, class U>optimal_BST<T, U>::optimal_BST(T* arr1, U* prob1, T* arr2, U* prob2, int n){
    //time: theta(n^2)
    U e[n][n];//expected expense: if i > j: expense of tree. otherwise extral expense
    int r[n][n];//root
    int l;
    for(int i = 0; i < n; i++){
        e[i][i] = prob1[i] + prob2[i] + prob2[i + 1];
    }
    for(l = 2; l <= n; l++){
        for(int i = 0; i + l - 1 < n; i++){
            e[i + l - 1][i] = e[i + l - 2][i] + prob1[i + l - 1] + prob2[i + l];
        }
    }
    U tmp;
    for(int i = 0; i < n; i++)
        r[i][i] = i;// l = 1
    for(l = 2; l <= n; l++){
        for(int i = 0; i + l - 1 < n; i++){
            e[i][i + l - 1] = e[i + 1][i + l - 1] + e[i + l - 1][i];
            r[i][i + l - 1] = i;
            for(int j = r[i][i + l - 2]; j <= r[i + 1][i + l - 1]; j++){//Knuth Theorem
                if(j == i){
                    continue;
                }
                else if(j == i + l - 1){
                    tmp = e[i][i + l - 2] + e[i + l - 1][i];
                    if(tmp < e[i][i + l - 1]){
                        r[i][i + l - 1] = i + l - 1;
                        e[i][i + l - 1] = tmp;
                    }
                }
                else{
                    tmp = e[i][j - 1] + e[j + 1][i + l - 1] + e[i + l - 1][i];
                    if(tmp < e[i][i + l - 1]){
                        r[i][i + l - 1] = j;
                        e[i][i + l - 1] = tmp;
                    }
                }
            }
        }
    }
    Stack<node*> s;
    Stack<int> ls;
    Stack<int> rs;
    Stack<int> rts;
    int nowrt = r[0][n - 1];
    int nowl = 0;
    int nowr = n - 1;
    node* nowp;
    node* prevp;
    nowp = new node;
    nowp -> val = arr1[nowrt];
    root = nowp;
    nowp -> parent = NULL;
    while(true){
        if(nowrt > nowl){
            s.push(nowp);
            ls.push(nowl);
            rs.push(nowr);
            rts.push(nowrt);
            prevp = nowp;
            nowp = new node;
            nowr = nowrt - 1;
            nowrt = r[nowl][nowr];
            nowp -> val = arr1[nowrt];
            prevp -> left = nowp;
            nowp -> parent = prevp;
        }
        else  if(nowr >= nowl){
            prevp = nowp;
            nowp = new node;
            nowp -> parent = prevp;
            prevp -> left = nowp;
            nowp -> val = arr2[nowl];
            nowp -> left = nowp -> right = NULL;
            if(nowr != nowrt){
                nowp = new node;
                nowl = nowrt + 1;
                nowrt = r[nowl][nowr];
                nowp -> val = arr1[nowrt];
                nowp -> parent = prevp;
                prevp -> right = nowp;
            }
            else{
                nowp = new node;
                nowp -> val = arr2[nowrt + 1];
                nowp -> parent = prevp;
                prevp -> right = nowp;
                nowp -> left = nowp -> right = NULL;
                if(!s.isempty()){
                    prevp = s.pop();
                    nowl = ls.pop();
                    nowrt = rts.pop();
                    nowr = rs.pop();
                    if(nowrt != nowr){
                        nowl = nowrt + 1;
                        nowrt = r[nowl][nowr];
                        nowp = new node;
                        nowp -> val = arr1[nowrt];
                        nowp -> parent = prevp;
                        prevp -> right = nowp;
                    }
                    else{
                        nowp = new node;
                        nowp -> val = arr2[nowr + 1];
                        nowp -> parent = prevp;
                        nowp -> left = nowp -> right = NULL;
                        prevp -> right = nowp;
                        nowl = nowr + 1;
                    }
                }
                else{
                    break;
                }
            }
        }
        else{
            if(!s.isempty()){
                prevp = s.pop();
                nowl = ls.pop();
                nowrt = rts.pop();
                nowr = rs.pop();
                if(nowrt != nowr){
                    nowl = nowrt + 1;
                    nowrt = r[nowl][nowr];
                    nowp = new node;
                    nowp -> val = arr1[nowrt];
                    nowp -> parent = prevp;
                    prevp -> right = nowp;
                }
                else{
                    nowp = new node;
                    nowp -> val = arr2[nowr + 1];
                    nowp -> parent = prevp;
                    prevp -> right = nowp;
                    nowl = nowr + 1;
                    nowp -> left = nowp -> right = NULL;
                }
            }
            else{
                break;
            }
        }
    }
};
/*
int main(){
    int arr1[7]{1,2,3,4,5,6,7};
    int arr2[8]{0,15,25,35,45,55,65,75};
    float prob1[7]{0.04,0.06,0.08,0.02,0.10,0.12,0.14};
    float prob2[8]{0.06,0.06,0.06,0.06,0.05,0.05,0.05,0.05};
    optimal_BST<int, float>t(arr1, prob1, arr2, prob2, 7);
    t.inorder_walk();
}
*/
