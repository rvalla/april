#include <iostream>
#include <stdio.h>

void eternity(){
    char d;
    std::cout << "Sólo una tecla podrá detenerme." << std::endl;
    std::cin >> d; //Vemos qué símbolo ingresó el usuario
    while (!(d == 'q')){ //Mientras el símbolo sea distinto de q entramos
        std::cout << "No voy a parar..." << std::endl;
        std::cin >> d; //Nos guardamos el nuevo símbolo
    }
    std::cout << "Ya no tengo dudas." << std::endl;
}

void elapsed(){
    int c = 0;
    while (c<10){ //Mientras c sea menor qure 10 entramos
        std::cout << "Ya casi paro." << std::endl;
        c++; //Incrementamos el valor de c en cada ciclo
    }
}

int main() { //El programa siempre empieza por acá.
    char d;
    std::cout << "Tenés que elegir: ¿A o B?" << std::endl; //El usuario decide camino
    std::cin >> d;
    if (d=='A'){
        eternity(); //Llamamos la función eternity()
    } else if (d=='B') {
        elapsed(); //Llamamos la función elapsed()
    } else {
        std::cout << "Así no hago nada." << std::endl; //No hacemos nada
    }
    return 0;
}