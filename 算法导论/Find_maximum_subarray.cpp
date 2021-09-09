//
//  Find_maximum_subarray.cpp
//  算法导论
//
//  Created by a magic neko on 2021/6/8.
//

#include "head.hpp"
#include <limits>
using namespace std;
//All intervals are closed
void find_maximum_subarray1(const int* arr, int left, int right, int* res){//recursive method, time complexity: Theta(nlg(n))
    int mid = (left + right)/2;
    if(left == right) {
        res[0] = arr[left];
        res[1] = res[2] = left;
        return ;
    }
    int lres[3];
    int rres[3];
    find_maximum_subarray1(arr, left, mid, lres);
    find_maximum_subarray1(arr, mid+1, right, rres);
    int rs = 0;
    int rms = (numeric_limits<int>::min)();
    int lms = (numeric_limits<int>::min)();
    int lindex, rindex;
    int ls = 0;
    for(int i = mid; i >= 0; i--){
        ls += arr[i];
        if(ls > lms){
            lms = ls;
            lindex = i;
        }
    }
    for(int i = mid + 1; i <= right ; i++){
        rs += arr[i];
        if(rs > rms){
            rms = rs;
            rindex = i;
        }
    }
    if(lres[0] >= rres[0] && lres[0] >= rms + lms){
        res[0] = lres[0];
        res[1] = lres[1];
        res[2] = lres[2];
    }
    else if(rres[0] >= rms + lms){
        res[0] = rres[0];
        res[1] = rres[1];
        res[2] = rres[2];
    }
    else{
        res[0] = rms + lms;
        res[1] = lindex;
        res[2] = rindex;
    }
    
}

void find_maximum_subarray2(const int* arr, int left, int right, int*res){
    //use the maximum subarray of [0,k-1] to find that of [0,k].time complexity: O(n)
    res[0] = numeric_limits<int>::min();
    int index; //left point of the maximum subarray of [res[2]+1,i]
    int sum1;//sum of [res[1],i]
    int sum2;//max sum of subarr of [res[2]+1,i]
    int flag;//whether res[2] changed last circle
    flag = 1;
    for(int i = left; i <= right; i++){
      /*  cout<<"circle:"<<i<<" one:"<<res[0]<<endl<<res[1]<<endl<<res[2]<<endl<<sum1<<endl<<sum2<<endl<<index<<endl<<flag<<endl;*/
        if(flag == 1){
            sum1 = res[0] + arr[i];
            sum2 = arr[i];
            index = i;
        }
        else{
            sum1 += arr[i];
            if(sum2 > 0){
                sum2 += arr[i];
            }
            else{
                sum2 = arr[i];
                index = i;
            }
        }
        if(sum1 >= sum2 && sum1 >= res[0]){
            res[0] = sum1;
            res[2] = i;
            flag = 1;
        }
        else if(sum2 >= res[0]){
            res[0] = sum2;
            res[1] = index;
            res[2] = i;
            flag = 1;
        }
        else
            {
                flag = 0;
            }
    }
}
/*
int main(){
    int arr[10]{1,5,-4,6,7,1,3,-5,1,2};
    int res[3];
    find_maximum_subarray2(arr, 0, 9, res);
    for(int i=0; i < 3; i++){
        cout<<res[i]<<endl;
    }
}
*/
