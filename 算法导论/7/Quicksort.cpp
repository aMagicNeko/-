//
//  Quicksort.cpp
//  算法导论
//
//  Created by a magic neko on 2021/6/11.
//

#include "head.hpp"
using namespace std;

void quicksort(int* arr, int l, int r){
    if(l >= r) return;
    //partition
    int i = rand() % (r - l + 1) + l;
    int div = arr[i];
    arr[i] = arr[l];
    arr[l] = div;
    int low = l - 1;
    int temp;
    int high = l;
    for(int j = l + 1; j <= r; j ++){
        if(arr[j] < div){
            low++;
            high++;
            temp = arr[low];
            arr[low] = arr[j];
            arr[j] = arr[high];
            arr[high] = temp;
        }
        else if(arr[j] == div){
            high++;
            temp = arr[high];
            arr[high] = arr[j];
            arr[j] = temp;
        }
    }
    quicksort(arr, l, low);
    quicksort(arr, high + 1, r);
    return;
}

void tail_recursive_quicksort(int* arr, int l, int r){
    while(true){
        if(l >= r) return;
        //partition
        int i = rand() % (r - l + 1) + l;
        int div = arr[i];
        arr[i] = arr[l];
        arr[l] = div;
        int low = l - 1;
        int temp;
        int high = l;
        for(int j = l + 1; j <= r; j ++){
            if(arr[j] < div){
                low++;
                high++;
                temp = arr[low];
                arr[low] = arr[j];
                arr[j] = arr[high];
                arr[high] = temp;
            }
            else if(arr[j] == div){
                high++;
                temp = arr[high];
                arr[high] = arr[j];
                arr[j] = temp;
            }
        }
        if(low - l <= r - high - 1){
            tail_recursive_quicksort(arr, l, low);
            l = high + 1;
        }
        else{
            tail_recursive_quicksort(arr, high + 1, r);
            r = low;
        }
    }
}
/*
int main(){
    srand(int(time(0)));
    int arr[11]{5,6,9,1,24,5,6,2,62,25,2};
    tail_recursive_quicksort(arr, 0, 10);
    for(int i=0;i<11;i++){
        cout<<arr[i]<<endl;
    }
}


*/
