//
//  Longest palindrome subsequence.cpp
//  算法导论
//
//  Created by Ekko on 2021/8/16.
//

#include "head.hpp"
using namespace std;
//Manacher algorithm: time: O(n)

template<class T> class LPCS{
private:
    T* p;
    int size;
public:
    LPCS(T* arr, int n, T div);
    ~LPCS();
    void show() const;
};
template<class T>LPCS<T>::LPCS(T* arr, int n, T div){
    //time: theta(n)
    int nn = 2 * n + 1;
    T* arr1 = new T[nn];
    int radius[nn];
    for(int i = 0; i < nn; i++){
        arr1[i] = i % 2 == 0 ? div : arr[i / 2];
    }
    int r = -1;//The max index of the right point of PSs
    int c = -1;//the central point of the rightest PS
    int Nradius;//the radius now
    int Nr;
    int Nl;
    int sym;//symmetry point of i about c
    for(int i = 0; i < nn; i++){
        if(i < r){
            sym = 2 * c - i;
            Nradius = radius[sym];
            Nr = i + Nradius - 1;
            if(Nr < r){
                radius[i] = Nradius;
                continue;
            }
            Nl = 2 * i - Nr;
        }
        else{
            Nr = i;
            Nradius = 1;
            Nl = i;
        }
        while(true){
            if(arr1[Nl - 1] != arr1[Nr + 1]){
                break;
            }
            --Nl;
            ++Nr;
            ++Nradius;
        }
        radius[i] = Nradius;
        r = Nr;
        c = i;
    }
    size = 0;
    for(int i = 0; i < nn; i++){
        if(size <= radius[i] - 1){
            size = radius[i] - 1;
            c = i;
        }
    }
    p = new T[size];
    int j = 0;
    for(int i = c - size; i <= c + size; i++){
        if(arr1[i] != div){
            p[j++] = arr1[i];
        }
    }
    delete [] arr1;
// delete [] radius;
}
template<class T> void LPCS<T>::show()const{
    for(int i = 0; i < size; i++){
        cout << p[i];
    }
}
template<class T> LPCS<T>::~LPCS(){
    delete[] p;
}
template<class T> class LPS{
private:
    T* p;
    int size;
public:
    void show()const;
    LPS(T* arr, int n);
    ~LPS();
};
template<class T> LPS<T>::LPS(T* arr, int n){
    //time: O(n^2)
    int len[n][n];
    for(int i = 0; i < n; i++){
        len[i][i] = 1;
    }
    int j, i;
    for(int l = 2; l <= n; l++){
        i = 0;
        j = i + l - 1;
        while(true){
            if(j >= n)
                break;
            if(arr[i] == arr[j]){
                if(l == 2)
                    len[i][j] = 2;
                else
                    len[i][j] = len[i + 1][j - 1] + 2;
                len[j++][i++] = 0;
            }
            else{
                if(len[i][j - 1] >= len[i + 1][j]){
                    len[i][j] = len[i][j - 1];
                    len[j++][i++] = 1;
                }
                else{
                    len[i][j] = len[i + 1][j];
                    len[j++][i++] = -1;
                }
            }
        }
    }
    size = len[0][n - 1];
    p = new T[size];
    i = 0;
    j = n - 1;
    int k, t;
    k = 0;
    t = size - 1;
    while(true){
        if(j == i){
            p[k] = arr[i];
            break;
        }
        else{
            switch(len[j][i]){
                case 0:{
                    p[k++] = p[t--] = arr[i];
                    ++i;
                    --j;
                    break;
                }
                case 1:{
                    --j;
                    break;
                }
                case -1:{
                    ++i;
                    break;
                }
            }
    }
    }
}
template<class T> void LPS<T>::show()const{
    for(int i = 0; i < size; i++)
        cout << p[i];
}
template<class T> LPS<T>::~LPS(){
    delete[] p;
}
/*
int main(){
    char str[9]{'c','h','a','r','a','c','t','e','r'};
    LPCS<char> s(str, 9, '#');
    s.show();
    LPS<char> s1(str, 9);
    s1.show();
}
*/
