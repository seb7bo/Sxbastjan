#include <iostream>
#define EXAMPLE_1 1
/*
 * TEMA Templates en C++
 *
 * Un template es una herramienta simple y poderosa en C++. La idea es simple es pasar un tipo de dato como parametro, de esta manera no tenemos que escribir el mismo codigo para diferentes tipos de datos. Por ejemplo , una compañia de software nececista un ordenamiento Sort() and y pasa el tipo de datao como parametro.
 *C++ agrega dos nuevas palabras claves para soportar templates: "template y typename#, La segunda palabra puede ser suistituida siempre por la palabra class"
 *Como funcionan los templates?
 *Los templates se expanden en tiempo de compilacion, Como las Macros. La diferencia es , el compilador hace una revision de tipo antes de hacer la expansion del template. 
 *La idea es simple, El codigo solo contiene, funciones y clases , pero el codigo compulado puede contenes multiples copias de la misma clase o funcion.
 */

/*Funcion templates: Escribimos una funcion egenerica que puede ser usada para diferentes tip´s de datos
 * Ejemplo, de funcion templates son sort(),max(),min(),printArray().
 */

#ifdef EXAMPLE_1

using namespace std;

template<typename T>
T myMax(T x, T y){
    return (x>y)?x:y;
}

int main(){
    cout<<myMax<int>(3,7)<<endl;
    cout<<myMax<float>(5.6,3.5)<<endl;
    cout<<myMax<char>('a','x')<<endl;
    return 0;
}

#endif


