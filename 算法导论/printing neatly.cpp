//
//  printing neatly.cpp
//  算法导论
//
//  Created by Ekko on 2021/9/8.
//

#include "head.hpp"
using namespace std;

void printing_neatly(string *s, int n, int M){
    int cube[n];
    int res[n];
    int tmp;
    int Ctmp;
    cube[0] = M - s[0].length();
    cube[0] = cube[0] * cube[0] * cube[0];
    for(int i = 1; i < n; i++){
        cube[i] = numeric_limits<int>::max();
        tmp = M + 1;
        for(int j = i; j >= 0; j--){
            tmp = tmp - s[j].length() - 1;
            if(tmp < 0)
                break;
            Ctmp = tmp * tmp * tmp + cube[j - 1];
            if(Ctmp < cube[i]){
                cube[i] = Ctmp;
                res[i] = j - 1;
            }
        }
    }
    res[0] = -1;
    int l,r;
    r = n - 1;
    Stack<string*> S;
    string s1 = " ";
    string s2 = "\n";
    while(true){
        l = res[r] + 1;
        tmp = r;
        while(true){
            S.push(&(s[tmp]));
            S.push(&s1);
            if(tmp == l)
                break;
            --tmp;
        }
        S.push(&s2);
        r = res[r];
        if(r < 0)
            break;
    }
    S.pop();
    while(!S.isempty())
        cout << *S.pop();
}
/*
int main(){
    string s[10] = {"abc","def","gh","polq","cs","opaqe","klfgh","t","asd","th"};
    printing_neatly(s, 10, 8);
}
*/
