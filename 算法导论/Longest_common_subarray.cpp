//
//  Longest_common_subarray.cpp
//  算法导论
//
//  Created by Ekko on 2021/8/8.
//

#include "head.hpp"
using namespace std;

template<class T>
Stack<T>* find_LCS(T* arr1, T* arr2, int n, int m){
    T c[n + 1][m + 1];//index1: the length of front-arr1, index2...
    int i, j;
    for(i = 0; i < n + 1; i++){
        c[i][0] = 0;
    }
    for(j = 0; j < m + 1; j++){
        c[0][j] = 0;
    }
    for(i = 1; i < n + 1; i++){
        for(j = 1; j < m + 1; j++){
            if(arr1[i - 1] == arr2[j - 1])
                c[i][j] = c[i - 1][j - 1] + 1;
            else if(c[i - 1][j] >= c[i][j - 1])
                c[i][j] = c[i - 1][j];
            else
                c[i][j] = c[i][j - 1];
        }
    }
    i = n - 1;
    j = m - 1;
    Stack<T>* s = new Stack<T>;
    while(i >= 0 && j >= 0){
        if(arr1[i] == arr2[j]){
            s -> push(arr1[i]);
            --i;
            --j;
        }
        else if(c[i][j + 1] >= c[i + 1][j]){
            --i;
        }
        else{
            --j;
        }
    }
    return s;
}
/*
int main(){
    char str1[11] {'a','w','e','d','s','a','f','z','f','w','s'};
    char str2[9]{'d','a','f','z','c','x','s','z','d'};
    Stack<char>* s = find_LCS<char>(str1, str2, 11, 9);
    while(!s -> isempty()){
        cout<<s -> pop();
    }
    
}
*/
