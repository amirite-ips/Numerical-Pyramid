#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#define forn(a,b) for(int (a)=0; (a)<(int)(b); ++(a))
using namespace std;
typedef int intv;

/** * * * * * * * * * * * * * * *
 *  ABUSING OOP TO ITS LIMITS   *
 * * * * * * * * * * * * * * * **/

/// CLASS CELL
class cell{
    public:
        cell(int _x, int _y) : unknown(true), value(0), x(_x), y(_y) {}
        void set(intv v);
        intv get();
        bool isUnknown();

    private:
        bool unknown;
        intv value;
        int x, y;
};

/// CLASS PYRAMID
class pyramid{
    public:
        pyramid(int n) : data(n) {
            forn(x, n){
                  data[x].reserve(x+1);
                  forn(y, x+1) data[x].emplace_back(x,y);
            }
        }
        bool isSolved();
        bool solve();
        string toString();
        cell& at(int x, int y);

    private:
        vector<vector<cell>> data;
};

/// MAIN FUNCTION
int main(){
    pyramid *A = new pyramid(6);

    A->at(3,1).set(43210);

    cout<<A->toString()<<endl;

    return 0;
}

/// CELL METHODS
/* set: assigns a new value to the cell and marks it as resolved */
void cell::set(intv v){
    value = v;
    unknown = false;
}

/* get: returns the current value of the cell, it should be called if isUnknown
        returned false */
intv cell::get(){
    return value;
}

/* isUnknown: returns whether the cell's value has been resolved */
bool cell::isUnknown(){
    return unknown;
}

/// PYRAMID METHODS

bool pyramid::isSolved(){
    for(auto &row : data)
        for(auto &c : row)
            if( c.isUnknown() ) return false;
    /// check forall cell that it's the sum of the others
}

bool pyramid::solve(){
    queue<cell*> Q;
    for(auto &row : data)
        for(auto &c : row)
            if( !c.isUnknown() ) Q.push( &c );
    while( Q.size() ){
        /// update cells
    }
}

/* toString: returns a string representation of the pyramid */
string pyramid::toString(){
    stringstream s;
    for(auto& row : data){
        forn(i, row.size()){
            if( i ) s<<' ';
            s.width(5), s<<row[i].get();
        }
        s<<endl;
    }
    return s.str();
}

/* at: returns a reference of the cell appointed by row x, column y */
cell& pyramid::at(int x, int y){
    return data[x][y];
}
