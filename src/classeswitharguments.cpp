#include <iostream>
#include <stdio.h>

class base { //Definimos una clase base...
    public:
        bool alive; //La clase tiene algunos atributos públicos...
        int code;

        base(bool a, int c){ //¡Este es el contructor! ¡Pero con argumentos!
            alive = a;
            code = c;
            std::cout << "A base instance was built!" << std::endl;
        }

        void show(){ //Acá hay un método de la clase...
            std::cout << "I am here!" << std::endl;
        }
};

class meta { //Definimos una clase meta...
    public:
        base x; //La clase tiene instancias de base como atributo...
        base y;

        meta(bool a, bool b, int c, int d) //¡Este es el constructor con argumentos!
            : x(a,c), y(b,d) //Por alguna razón hace falta inicializar las base así...
        {
            std::cout << "A meta instance was built!" << std::endl;
        }

        void show(){ //Acá hay un método de la clase
            x.show();
            y.show();
        }
};

int main() { //El programa siempre empieza por acá.
    std::cout << "Vamos a probar instanciar unas clases..." << std::endl;
    meta m = meta(true, false, 1, 0); //Construimos una instancia de meta...
    m.show(); //Llamamos el método show() de meta...
    base b = base(false, 1); //Construimos una instancia de base...
    b.show(); //Llamamos el método show() de base...
    return 0;
}