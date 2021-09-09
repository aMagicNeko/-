//
//  edit distance.cpp
//  算法导论
//
//  Created by Ekko on 2021/9/8.
//

#include "head.hpp"
using namespace std;
template<class T> class edit_distance{
private:
    class OP{
    public:
        bool doubl;
        int n;
        int* p;
        OP(){
            p = new int[2];
        }
        void build(int a){
            //single operation
            *p = a;
            doubl = false;
        }
        void build(int a, int b, int nb){
            p[0] = a;
            p[1] = b;
            doubl = true;
            n = nb;
        }
        ~OP(){
            delete [] p;
        }
        int changes1(){
            int res = 0;
            switch (p[0]) {
                case 0:
                    res += 1;
                    break;
                case 1:
                    res += 1;
                    break;
                case 2:
                    res += 1;
                    break;
                case 4:
                    res += 2;
                    break;
                default:
                    break;
            }
            if(doubl)
                switch (p[1]) {
                    case 0:
                        res += 1 * n;
                        break;
                    case 1:
                        res += 1 * n;
                        break;
                    case 2:
                        res += 1 * n;
                        break;
                    case 4:
                        res += 2 * n;
                        break;
                    default:
                        break;
                }
            return res;
        }
        
        int changes2(){
            int res = 0;
            switch (p[0]) {
                case 0:
                    res += 1;
                    break;
                case 1:
                    res += 1;
                    break;
                case 3:
                    res += 1;
                    break;
                case 4:
                    res += 2;
                    break;
                default:
                    break;
            }
            if(doubl)
                switch (p[1]) {
                    case 0:
                        res += 1 * n;
                        break;
                    case 1:
                        res += 1 * n;
                        break;
                    case 3:
                        res += 1 * n;
                        break;
                    case 4:
                        res += 2 * n;
                        break;
                    default:
                        break;
                }
            return res;
        }
        void show(){
            cout <<"one time " << p[0]<<' ';
            if(doubl)
                cout << n << "times" << p[1] <<' ';
        }
        const OP& operator=(const OP& a){
            doubl = a.doubl;
            p[0] = a.p[0];
            p[1] = a.p[1];
            n = a.n;
            return *this;
        }
    };
    T cost;
public:
    edit_distance(const T *COST, const string &s1, const string &s2);
    ~edit_distance(){
    }
};

template<class T> edit_distance<T>::edit_distance(const T *COST, const string &s1, const string &s2){
    int len1 = s1.size();
    int len2 = s2.size();
    T c[len1][len2];
    OP op[len1][len2];
    int tmp;
    //0,0
    c[0][0] = numeric_limits<int>::max();
    if(s1[0] == s2[0]){
        //copy
        c[0][0] = COST[0];
        op[0][0].build(0);
    }
    //replace
    tmp = COST[1];
    if(c[0][0] > tmp){
        c[0][0] = tmp;
        op[0][0].build(1);
    }
    //delete and insert
    tmp = COST[2] + COST[3];
    if(c[0][0] > tmp){
        c[0][0] = tmp;
        op[0][0].build(2, 3, 1);
    }
    for(int i = 0; i < len2; i++){
        //0,i
        c[0][i] = numeric_limits<int>::max();
        if(s1[0] == s2[i]){
            //copy and insert
            c[0][i] = COST[0] + (i) * COST[3];
            op[0][i].build(0, 3, i);
        }
        //replace and insert
        tmp = COST[1] + COST[3] * (i);
        if(c[0][i] > tmp){
            c[0][i] = tmp;
            op[0][i].build(1, 3, i);
        }
        //delete and insert
        tmp = COST[2] + COST[3] * (i + 1);
        if(c[0][i] > tmp){
            c[0][i] = tmp;
            op[0][i].build(2, 3, i + 1);
        }
        //insert
        tmp = COST[3] + c[0][i - 1];
        if(c[0][i] > tmp){
            c[0][i] = tmp;
            op[0][i].build(3);
        }
    }
    for(int j = 0; j < len1; j++){
        //i,0
        c[j][0] = numeric_limits<int>::max();
        if(s1[j] == s2[0]){
            //copy and delete
            c[j][0] = COST[0] + COST[2] * (j);
            op[j][0].build(0, 2, j);
        }
        //replace and delete
        tmp = COST[1] + COST[2] * (j);
        if(c[j][0] > tmp){
            c[j][0] = tmp;
            op[j][0].build(1, 2, j);
        }
        //delete
        tmp = COST[2] + c[j - 1][0];
        if(c[j][0] > tmp){
            c[j][0] = tmp;
            op[j][0].build(2);
        }
        //insert and delete
        tmp = COST[3] + COST[2] * (j + 1);
        if(c[j][0] > tmp){
            c[j][0] = tmp;
            op[j][0].build(3, 2, j + 1);
        }
    }
    OP Otmp;
    for(int i = 1; i < len2; i++)
        for(int j = 1; j < len1; j++){
            c[j][i] = numeric_limits<int>::max();
            if(s1[j] == s2[i]){
                //copy
                c[j][i] = c[j - 1][i - 1] + COST[0];
                op[j][i].build(0);
            }
            //replace
            tmp = c[j - 1][i - 1] + COST[1];
            if(c[j][i] > tmp){
                c[j][i] = tmp;
                op[j][i].build(1);
            }
            //delete
            tmp = c[j - 1][i] + COST[2];
            if(c[j][i] > tmp){
                c[j][i] = tmp;
                op[j][i].build(2);
            }
            //insert
            tmp = c[j][i - 1] + COST[3];
            if(c[j][i] > tmp){
                c[j][i] = tmp;
                op[j][i].build(3);
            }
            if(s1[j] == s2[i - 1] && s1[j - 1] == s2[i]){
                //twiddle
                if(i != 1 && j != 1){
                    tmp = c[j - 2][i - 2] + COST[4];
                    Otmp.build(4);
                }
                else if(i != 1){
                    tmp = COST[4] + COST[3] * (j - 1);
                    Otmp.build(4, 3, j - 1);
                }
                else if(j != 1){
                    tmp = COST[4] + COST[2] * (i - 1);
                    Otmp.build(4, 2, j - 1);
                }
                else{
                    tmp = COST[4];
                    Otmp.build(4);
                }
                if(c[j][i] > tmp){
                    c[j][i] = tmp;
                    op[j][i] = Otmp;
                }
            }
        }
    int flag;
    for(int i = 1; i < len1; i++){
        tmp = COST[5] + c[i - 1][len2 - 1];
        if(tmp < c[len1 - 1][len2 - 1]){
            c[len1 - 1][len2 - 1] = tmp;
            flag = i - 1;
            op[len1 - 1][len2 - 1].build(5);
        }
    }
    tmp = COST[5] + COST[3] * len2;
    if(tmp < c[len1 - 1][len2 - 1]){
        c[len1 - 1][len2 - 1] = tmp;
        flag = -1;
        op[len1 - 1][len2 - 1].build(5, 3, len2);
    }
    int i, j;
    i = len1 - 1;
    j = len2 - 1;
    Stack<OP*> s;
    OP* ptmp;
    if(op[i][j].p[0] == 5){
        ptmp = &op[i][j];
        s.push(ptmp);
        i = flag;
        j -= ptmp -> changes2();
    }
    while(true){
        if(i < 0 && j < 0)
            break;
        ptmp = &op[i][j];
        s.push(ptmp);
        i -= ptmp -> changes1();
        j -= ptmp -> changes2();
    }
    while(!s.isempty()){
        ptmp = s.pop();
        ptmp -> show();
    }
    cout << endl;
    for(int i = 0; i < len1; i++){
        for(int j = 0; j < len2; j++)
            cout<<c[i][j]<<' ';
        cout<<endl;
    }
}
/*
int main(){
    string s1 = "algorithm";
    string s2 = "altruistic";
    int COST[6] = {1, 2, 1, 1, 1, 3};
    edit_distance<int>(COST, s1, s2);
}
 */

