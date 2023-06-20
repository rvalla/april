#include <iostream>

int main() { //El programa siempre empieza por acá.
    int count = 5; //Definimos una cantidad de números.
    int numbers[count] = {0,1,2,3,4}; //Definimos un arreglo de 5 números.
    for (int i = 0; i < count; i++){ //Recorremos el arreglo
        std::cout << std::to_string(numbers[i]); //Imprimimos sus elementos
        std::cout << "\n";
    }

    return 0;
}