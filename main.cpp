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
        bool isValid(int x, int y);
        // given the current known cell 'c', k = c+(dx[i] ,dy[i]) and
        // p = c+(dx[i+1] ,dy[i+1])
        // you can update k with p-c if p is known
        // otherwise, if k is known, then update p with k+c
        int base;
        const vector<int> dx = {0, -1, 0, -1};
        const vector<int> dy = {-1, -1, 1, 0};
        vector<vector<cell>> data;
};

/// MAIN FUNCTION
int main(){
    int n = 4;
    pyramid *A = new pyramid(n);
/**
    forn(i, n)
    A->at(n-1, i).set(i+1);

    for(int i = n-2; i>=0; --i)
        for(int e = 0; e <= i; ++e)
            A->at(i, e).set( A->at(i+1,e).get() + A->at(i+1,e+1).get() );
**/

    A->at(1,0).set(40);
    A->at(2,2).set(20);
    A->at(3,1).set(10);
    A->at(3,2).set(10);

    A->solve();
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
    int x, y;

    for(auto &row : data)
        for(auto &c : row)
            if( c.isUnknown() == false ) Q.push( &c );

    while( Q.size() ){
        cell *c = Q.front();
        tie(x, y) = c->getCoordinates();

        forn(i, dx.size()){
            if( isValid(x+dx[i], y+dy[i]) ){
                cell *k = &data[ x+dx[i] ][ y+dy[i] ];
                cell *p = &data[ x+dx[i+1] ][ y+dy[i+1] ];

                if( k->isUnknown() == false ){
                    p->set( c->get() + k->get() );
                    Q.push( p );
                }
                else if( p->isUnknown() == false ){
                    k->set( p->get() - c->get());
                    Q.push( k );
                }
            }
            i++;
        }

        Q.pop();
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

bool pyramid::isValid(int x, int y){
    if( x<0 || x>=base ) return false;
    if( y<0 || y>=data[x].size() ) return false;

    return true;
}

/* at: returns a reference of the cell appointed by row x, column y */
cell& pyramid::at(int x, int y){
    return data[x][y];
}
