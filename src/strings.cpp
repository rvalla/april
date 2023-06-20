#include <iostream>

int main() { //El programa siempre empieza por acá.
    std::string s = "Esto es un mensaje"; //Definimos una cadena de caracteres...
    std::cout << s << std::endl;
    for (int i = 0; i < s.size(); i++){ //Recorremos la cadena de caracteres...
        std::cout << s[i] << std::endl; //Imprimimos sus elementos
    }
    return 0;
}