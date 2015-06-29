#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <tuple>
#define forn(a,b) for(int (a)=0; (a)<(int)(b); ++(a))
using namespace std;
typedef int intv;

/** * * * * * * * * * * * * * * * * * * *
 *                                      *
 *      PYRAMID SOLVER v1.0 (BETA)      *
 *                                      *
 * * * * * * * * * * * * * * * * * * * **/

    /* * * * * * * * * * * * * * * *
     *  ABUSING OOP TO ITS LIMITS  *
     * * * * * * * * * * * * * * * */

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
        int base;
        const vector<int> dx = {0, -1, 0, -1};  //x offset of neighboring cells
        const vector<int> dy = {-1, -1, 1, 0};  //y offset of neighboring cells
        vector<vector<cell>> data;
};

/// MAIN FUNCTION
int main(){
    pyramid *A = new pyramid(6);

    A->at(1,0).set(80);
    A->at(2,2).set(65);
    A->at(3,1).set(10);
    A->at(3,2).set(25);
    A->at(5,1).set(15);
    A->at(5,2).set(8);

    A->solve();
    cout<<"The pyramid is "<<( A->isSolved() ? "" : "not " )<<"solved."<<endl;
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

/* getCoordinates: returns a pair with the cell coordinates */
tuple<int, int> cell::getCoordinates(){
    return make_tuple(x, y);
}

/* isUnknown: returns whether the cell's value has been resolved */
bool cell::isUnknown(){
    return unknown;
}

/// PYRAMID METHODS
/* isSolved: returns true if the pyramid is valid and is solved*/
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

/* solve: most important method, solves the piramid, returns true on success*/
bool pyramid::solve(){
    queue<cell*> Q;
    int x, y;

    for(auto &row : data)
        for(auto &c : row)
            if( !c.isUnknown() ) Q.push( &c );

    while( Q.size() ){
        cell *c = Q.front(); Q.pop();
        tie(x, y) = c->getCoordinates();
        //cout<<"solved ("<<x<<','<<y<<") = "<<c->get()<<endl;

        // siblings and parents
        /*  given the current known cell 'c', k = c+(dx[i] ,dy[i]) and
            p = c+(dx[i+1] ,dy[i+1])
            you can update k with p-c if p is known
            otherwise, if k is known, then update p with k+c */
        for(int i=0; i<dx.size(); i+=2){
            if( isValid(x+dx[i+1], y+dy[i+1]) ){
                cell *k = &data[ x+dx[i] ][ y+dy[i] ];
                cell *p = &data[ x+dx[i+1] ][ y+dy[i+1] ];

                if( !k->isUnknown() && p->isUnknown() ){
                    p->set( c->get() + k->get() );
                    Q.push( p );
                }
                if( !p->isUnknown() && k->isUnknown() ){
                    k->set( p->get() - c->get());
                    Q.push( k );
                }
            }
        }
        // children
        if( x < base-1 ){
            cell *k = &data[ x+1 ][ y ];
            cell *p = &data[ x+1 ][ y+1 ];
            if( !p->isUnknown() && k->isUnknown() ){
                k->set( c->get() - p->get());
                Q.push( k );
            }
            if( !k->isUnknown() && p->isUnknown() ){
                p->set( c->get() - k->get());
                Q.push( p );
            }
        }
    }
    return isSolved();
}

/* toString: returns a string representation of the pyramid */
string pyramid::toString(){
    int b = base;
    const int space = 6;
    stringstream s;

    for(auto& row : data){
        s.width( (b--) * ((space+1) / 2 ) );
        forn(i, row.size()){
            if( i ) s.width( space );
            s<<row[i].get();
        }
        s<<endl;
    }
    return s.str();
}

/* isValid: returns whether the specified coordinates are valid */
bool pyramid::isValid(int x, int y){
    if( x<0 || x>=base ) return false;
    if( y<0 || y>=data[x].size() ) return false;
    return true;
}

/* at: returns a reference of the cell appointed by row x, column y */
cell& pyramid::at(int x, int y){
    return data[x][y];
}
