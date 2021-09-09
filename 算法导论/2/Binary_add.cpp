//
//  Binary_add.cpp
//  算法导论
//
//  Created by a magic neko on 2021/6/5.
//

#include "../head.hpp"
using namespace std;

int binary_add(int a, int b)
{
    int len = 1;
    int temp1, temp2;
    temp1 = a;
    temp2 = b;
    while(true){
        temp1 /= 2;
        temp2 /= 2;
        if(temp1 == 0 && temp2 == 0)
            break;
        else
            len++;
        }
    int res[len+1];
    int A[len];
    int B[len];
    for(int i = 0; i < len; i++){
        A[i] = (a >> i) % 2;
        B[i] = (b >> i) % 2;
    }
    int up=0;
    int temp;
    for(int i = 0; i < len; i++){
        temp = A[i] + B[i] + up;
        if(temp >= 2){
            res[i] = temp-2;
            up=1;
        }
        else{
            res[i] = temp;
            up = 0;
        }
    }
    res[len] = up;
    int Res = 0;
    temp = 1;
    for(int i = 0; i < len+1; i++){
        Res += res[i] * temp;
        temp *= 2;
    }
    return Res;
}
/*
int main(){
    int a=10000000;
    int b=10000000;
    cout<<binary_add(a, b);
}
*/
