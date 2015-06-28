#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <tuple>
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
        tuple<int, int> getCoordinates();
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
            base = n;
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
        int base;
        vector<vector<cell>> data;
};

/// MAIN FUNCTION
int main(){
    int n = 13;
    pyramid *A = new pyramid(n);

    forn(i, n)
    A->at(n-1, i).set(i+1);

    for(int i = n-2; i>=0; --i)
        for(int e = 0; e <= i; ++e)
            A->at(i, e).set( A->at(i+1,e).get() + A->at(i+1,e+1).get() );

    cout<<"The pyramid is "<<( A->isSolved() ? "" : "not " )<<"solved"<<endl;

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

tuple<int, int> cell::getCoordinates(){
    return make_tuple(x, y);
}

/* isUnknown: returns whether the cell's value has been resolved */
bool cell::isUnknown(){
    return unknown;
}

/// PYRAMID METHODS
bool pyramid::isSolved(){
    int x, y;
    for(auto &row : data)
        for(auto &c : row){
            if( c.isUnknown() ) return false;
            tie(x, y) = c.getCoordinates();
            if( x < base-1 )
                if( c.get() != at(x+1,y).get() + at(x+1,y+1).get() )
                    return false;
        }
    return true;
}

bool pyramid::solve(){
    queue<cell*> Q;
    for(auto &row : data)
        for(auto &c : row)
            if( !c.isUnknown() ) Q.push( &c );

    int x, y;
    while( Q.size() ){
        cell *c = Q.front();
        tie(x, y) = c->getCoordinates();

    }
}

/* toString: returns a string representation of the pyramid */
string pyramid::toString(){
    int b = base;
    const int space = 6;
    stringstream s;

    for(auto& row : data){
        s.width( (b--) * ((space+1) / 2 ) ); //s << ' '; can't tell the diff.?
        forn(i, row.size()){
            if( i ) s.width( space );
            s<<row[i].get();
        }
        s<<endl;
    }
    return s.str();
}

/* at: returns a reference of the cell appointed by row x, column y */
cell& pyramid::at(int x, int y){
    return data[x][y];
}
