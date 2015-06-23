#include <iostream>
#include <vector>
#include <string>
#define forn(a,b) for(int (a)=0; (a)<(int)(b); ++(a))
using namespace std;

class cell{
    public:
        cell() : unknown(true) {}
        void set(int v);
        int get();
    private:
        bool unknown;
        int value;
};

class pyramid{
    public:
        pyramid(int n){
            data.resize(n);
            forn(i, n)  data[i].resize(i+1);
        }
        bool canSolve();
        bool solve();
        string toString();
        cell& at(int x, int y){ return data[x][y]; }
    private:
        vector<vector<cell>> data;
};

int main(){
    pyramid *A;

    A = new pyramid(6);

    A->at(1,3).set(4);


    return 0;
}

void cell::set(int v){
    value = v;
    unknown = false;
}

int cell::get(){
    return value;
}
