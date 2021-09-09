//
//  Order_statistics.cpp
//  算法导论
//
//  Created by a magic neko on 2021/6/15.
//

#include "head.hpp"
using namespace std;

int select(int* arr, int l, int r, int k){
    //select kth order statistic, expected time: theta(n)
    int i = rand() % (r - l + 1) + l;
    int key = arr[i];
    arr[i] = arr[l];
    arr[l] = key;
    int low = l - 1;
    int high = l;
    for(i = l + 1; i <= r; i++){
        if(arr[i] < key){
            low++;
            high++;
            arr[low] = arr[i];
            arr[i] = arr[high];
            arr[high] = key;
        }
        else if(arr[i] == key){
            high++;
            arr[i] = arr[high];
            arr[high] = key;
        }
    }
    if(k > low && k <= high)
        return key;
    if(k <= low)
        return select(arr, l, low, k);
    return select(arr, high + 1, r, k);
}
void insertion_sort(int* arr, int l, int r)//From small to large
{
    int n = l;
    int key;
    int i;
    while(n < r){
        i = n;
        n++;
        key = arr[n];
        while(key < arr[i] && i >= l){
            arr[i+1] = arr[i];
            i--;
        }
        arr[i+1] = key;
    }
    return;
}
int modified_select(int* arr, int l, int r, int k){
    //time: O(n)
    int n = (r - l + 1) / 5;
    if(n == 0){
        insertion_sort(arr, l, r);
        return arr[k];
    }
    int med[n];
    int i;
    for(i = 0; i < n - 1; i++){
        insertion_sort(arr, l + 5 * i, l + 5 * (i + 1) - 1);
        med[i] = arr[l + 5 * i + 3];
    }
    insertion_sort(arr, l + 5 * (n - 1), r);
    med[n - 1] = arr[(l + 5 * (n - 1) + r) / 2 + 1];
    int m = modified_select(med, 0, n - 1, n / 2);
    for(int j = l; j <= r; j++){
        if(arr[j] == m)
        {
            i = j;
            break;
        }
    }
    int key = m;
    arr[i] = arr[l];
    arr[l] = key;
    int low = l - 1;
    int high = l;
    for(i = l + 1; i <= r; i++){
        if(arr[i] < key){
            low++;
            high++;
            arr[low] = arr[i];
            arr[i] = arr[high];
            arr[high] = key;
        }
        else if(arr[i] == key){
            high++;
            arr[i] = arr[high];
            arr[high] = key;
        }
    }
    if(k > low && k <= high)
        return key;
    if(k <= low)
        return modified_select(arr, l, low, k);
    return modified_select(arr, high + 1, r, k);
}
/*
int main(){
    int A[10]{4,2,10,1,7,2,5,1,7,8};
    cout<<select(A, 0, 9, 9)<<endl;
    cout<<modified_select(A, 0, 9, 5);
}
*/
