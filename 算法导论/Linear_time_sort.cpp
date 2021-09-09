//
//  Linear_time_sort.cpp
//  算法导论
//
//  Created by a magic neko on 2021/6/13.
//

#include "head.hpp"
using namespace std;

void counting_sort(int* arr, int* res, int len, int k){
    //time: theta(len+k), space: theta(k+len), stable
    int arr_count[k];
    int i;
    for(i = 0; i < k; i++){
        arr_count[i] = 0;
    }
    for(i = 0; i < len; i++){
        arr_count[arr[i]] += 1;
    }
    arr_count[0]--;
    for(i = 1; i < k; i++){
        arr_count[i] += arr_count[i - 1];
    }
    for(i = len - 1; i >= 0; i--){
        res[arr_count[arr[i]]--] = arr[i];
    }
    return;
}

void in_place_counting_sort(int *arr, int len, int k){
    //time: theta(len+k), space: theta(k), unstable
    int arr_count[k];
    int i;
    for(i = 0; i < k; i++){
        arr_count[i] = 0;
    }
    for(i = 0; i < len; i++){
        arr_count[arr[i]] += 1;
    }
    arr_count[0]--;
    for(i = 1; i < k; i++){
        arr_count[i] += arr_count[i - 1];
    }
    int temp;
    int arr_count1[k];//the start point of {key=k}
    for(i = 1; i < k; i++){
        arr_count1[i] = arr_count[i-1];
    }
    arr_count1[0] = -1;
    for(i = 0; i < len; i++){
        while(arr_count[arr[i]] != arr_count1[arr[i]])//c=c1 then element in proper position
        {
            temp = arr[i];
            arr[i] = arr[arr_count[temp]];
            arr[arr_count[temp]] = temp;
            while(temp == arr[arr_count[temp]])//proper position
                arr_count[temp]--;
        }
    }
    return;
}

void radix_counting_sort(int* arr, int* res, int len, int k){
    //time: theta(len+k), space: theta(k+len), stable
    int arr_count[k];
    int i;
    for(i = 0; i < k; i++){
        arr_count[i] = 0;
    }
    for(i = 0; i < len; i++){
        arr_count[arr[i]] += 1;
    }
    arr_count[0]--;
    for(i = 1; i < k; i++){
        arr_count[i] += arr_count[i - 1];
    }
    int temp[len];
    for(i = 0; i < len; i++){
        temp[i] = res[i];
    }
    for(i = len - 1; i >= 0; i--){
        res[arr_count[arr[i]]--] = temp[i];
    }
    return;
}

void radix_sort(int* arr, int len, int d, int k){//d: numbers of unites
    int arr1[len];
    int pow[d];
    pow[0] = 1;
    for(int i = 1; i < d + 1; i++){
        pow[i] = pow[i - 1] * k;
    }
    for(int i = 0; i < d; i++){
        for(int j = 0; j < len; j++){
            arr1[j] = (arr[j] % pow[i + 1]) / pow[i];
        }
        radix_counting_sort(arr1, arr, len, k);
    }
}
struct ls{
    ls* next = NULL;
    int key;
};

void bucket_sort(int* arr, int len, int min, int max, int n){
    ls* bucket[n];
    int i;
    for(i = 0; i < n; i++)
        bucket[i] = NULL;
    int pos;
    int Key;
    ls* p,* pt;
    float d = (max - min) / n;
    for(i = 0; i < len; i++){
        Key = arr[i];
        pos = int((Key - min) / d);
        if(pos >= n)
            pos = n - 1;
        //insert
        p = new ls;
        p->key = Key;
        pt = bucket[pos];
        if(pt == NULL)
            bucket[pos] = p;
        else if(pt->key >= Key){
                p->next = pt;
                bucket[pos] = p;
            }
        else{
            while(pt->next != NULL){
                if(pt->key <= Key && pt->next->key >= Key){
                    break;
                }
                pt = pt->next;
            }
            p->next = pt->next;
            pt->next = p;
        }
    }
    int j = 0;
    while(bucket[j] == NULL)
    {
        j++;
    }
    pt = bucket[j];
    for(i = 0; i < len; i++){
        arr[i] = pt->key;
        p = pt;
        pt = pt->next;
        delete p;
        if(pt == NULL){
            j++;
            while(bucket[j] == NULL)
            {
                j++;
            }
            pt = bucket[j];
        }
    }
}

/*
int main(){
    int arr[12]{5,6,9,1,4,5,6,2,6,5,2,7};
    int res[12];
    counting_sort(arr, res, 12, 10);
    for(int i = 0; i < 12; i++){
        cout<<res[i]<<endl;
    }
    in_place_counting_sort(arr, 12, 10);
    for(int i = 0; i < 12; i++){
        cout<<arr[i]<<endl;
    }
    int arr1[]{231,523,124,634,856,124,956,124,346,234,568,214,575,123,567,156,568,143,982};
    //radix_sort(arr1, 19, 3, 10);
    bucket_sort(arr1, 19, 100, 1000, 10);
    for(int i = 0; i < 19; i++)
        cout<<arr1[i]<<' ';
}

*/
