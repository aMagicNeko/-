//
//  Merge_sort.cpp
//  算法导论
//
//  Created by a magic neko on 2021/6/5.
//
#include "../head.hpp"
using namespace std;

void merge_sort(int* arr, int l, int r);
void merge(int* arr, int l, int mid, int r);
void merge_sort(int* arr, int len){
    merge_sort(arr, 0, len-1);
}

void merge_sort(int* arr, int l, int r){
    if(l >= r) return;//if less than one number
    int mid = (l+r)/2;
    merge_sort(arr, l, mid);
    merge_sort(arr, mid+1, r);
    merge(arr, l, mid, r);
}
void merge(int* arr, int l, int mid, int r){
    if(mid+1 > r) return;//if the right part is empty
    int arrL[mid-l+1];
    int arrR[r-mid];
    int i;
    for(i = l; i <= mid; i++){
        arrL[i-l] = arr[i];
    }
    for(i = mid+1; i <= r; i++){
        arrR[i-mid-1] = arr[i];
    }
    i = l;
    int ir = 0;
    int il = 0;
    while(true){
        if(arrL[il] <= arrR[ir])
            arr[i++] = arrL[il++];
        else
            arr[i++] = arrR[ir++];
        if(il > mid-l){
            while(i <= r)
                arr[i++] = arrR[ir++];
            break;
        }
        if(ir > r-mid-1){
            while( i <= r)
                arr[i++] = arrL[il++];
            break;
        }
    }
    return;
}
/*
int main(){
    int arr[11]{2,6,1,5,2,6,2,34,32,6,13};
    merge_sort(arr, 11);
    for(int i=0; i<11; i++){
        cout<<arr[i]<<endl;
    }
}
*/
