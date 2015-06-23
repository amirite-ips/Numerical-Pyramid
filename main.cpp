#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#define forn(a,b) for(int (a)=0; (a)<(int)(b); ++(a))
using namespace std;

typedef int intv;

/** * * * * * * * * * * * * * *
 *  ABUSING OOP TO ITS LIMITS *
 * * * * * * * * * * * * * * **/

/// CLASS CELL
class cell{
    public:
        cell() : unknown(true), value(0) {}
        void set(intv v);
        intv get();
        bool isUnknown();

    private:
        bool unknown;
        intv value;
};

/// CLASS PYRAMID
class pyramid{
    public:
        pyramid(int n){
            data.resize(n);
            forn(i, n)  data[i].resize(i+1);
        }
        bool canSolve();
        bool solve();
        string toString();
        cell& at(int x, int y);

    private:
        vector<vector<cell>> data;
};

/// MAIN FUNCTION
int main(){
    pyramid *A;
    string s;

    A = new pyramid(6);

    A->at(3,1).set(4);

    s = A->toString();

    cout<<s<<endl;


    return 0;
}

/// CELL METHODS

void cell::set(intv v){
    value = v;
    unknown = false;
}

intv cell::get(){
    return value;
}

bool cell::isUnknown(){
    return unknown;
}

/// PYRAMID METHODS

string pyramid::toString(){
    stringstream s;
    for(auto& row : data){
        forn(i, row.size()){
            if( i ) s<<' ';
            s<<row[i].get();
        }
        s<<endl;
    }
    return s.str();
}

cell& pyramid::at(int x, int y){
    return data[x][y];
}
