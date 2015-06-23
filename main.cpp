#include <iostream>
#include <string>
using namespace std;

class cell{
    public:
        void set( ... );
        
        // cell *left_child = ... ;
        // cell *right_child = ... ;
    private:
        
};

class pyramid{
    public:
        bool canSolve();
        string toString();
    private:
};

int main(){
    cout << "Hello GitHub!" << endl;

    return 0;
}

/** 
    Como construir la pirámide:
- Asignarle a cada casilla los numeros del 1 al 21 numerando desde arriba hacia abajo, 
    siempre de izquierda a derecha
- Asignarle un nivel 'y' a cada casilla, tal que la fila del 1 tenga nivel y=1,
    la fila del 2 y el 3 con y=2, y así sucesivamente hasta la última con y=6
- Para algana casilla con número 'x' en la pirámide, sus hijos son (x + y) y (x + y + 1)
**/
