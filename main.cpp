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
    Como construir la pirámide (de base n):
- Hacer n arrays de tamaño 1, 2, 3, ..., n
- Para una celda en la posicion P[y][x], los hijos son P[y+1][x] y P[y+1][x+1]
**/

/** 
    Otra forma:
- Asignarle a cada casilla los numeros del 1 al f(n)=f(n-1)+n numerando desde arriba hacia abajo, 
    siempre de izquierda a derecha (con f(1)=1)
- Asignarle un nivel 'y' a cada casilla, tal que la fila del 1 tenga nivel y=1,
    la segunda fila con y=2, y así sucesivamente hasta la última con y=n
- Para algana casilla con número 'x' en la pirámide, sus hijos son (x+y) y (x+y+1)
**/
