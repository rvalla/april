#include <iostream>

int main() { //El programa siempre empieza por acá.
    int number = 0; //Definimos un número entero llamado "number".
    /*Vamos a hacerlo crecer mientras lo imprimimos.
    **Para eso usamos un bucle "for" que comienza con la variable
    **control "i=0". Notar que C++, al terminar cada vuelta del bucle
    **le suma 1 a i (es lo que indica "i++"). El bucle termina cuando
    **i=5 porque se le indicó la condición "i<5".
    */
    for (int i = 0; i < 5; i++){ 
        number += 1; //Le sumamos 1 a number cada vez.
        std::cout << std::to_string(number);
        std::cout << "\n";
    }

    std::cout << "\n\n"; //Dejamos unos renglones.

    //Repetimos el bucle pero saltando de 3 en 3 ahora.
    for (int i = 0; i < 25; i=i+3){
        //i es un entero, podemos usarlo para contar.
        std::cout << std::to_string(i);
        std::cout << "\n";
    }

    return 0;
}