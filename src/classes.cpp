#include <iostream>
#include <stdio.h>

class base { //Definimos una clase base...
    public:
        bool alive; //La clase tiene algunos atributos públicos...
        int code;   //Como son públicos son visibles para otras clases...

        base(){ //¡Este es el constructor!
            alive = true;
            code = 1;
            std::cout << "A base instance was built!" << std::endl;
        }

        void show(){ //Este es un método de la clase...
            std::cout << "I am here!" << std::endl;
        }
};

class meta { //Definimos una clase meta...
    public:
        base b; //La clase tiene instancias de la clase base como atributo...
        base d; //Estas líneas llaman al constructor de base porque existe el constructor base()...

        meta(){ //¡Este es el constructor!
            b = base(); //Esta línea no tiene sentido.
            d = base(); //El constructor ya fue llamado antes.
            std::cout << "A meta instance was built!" << std::endl;
        }

        void show(){ //Este es un método de la clase...
            b.show();
            d.show();
        }
};

int main() { //El programa siempre empieza por acá.
    std::cout << "Vamos a probar instanciar unas clases..." << std::endl;
    meta m = meta(); //Construimos una instancia de meta...
    m.show(); //Llamamos el método show() de meta...
    base b = base(); //Construimos una instancia de base...
    b.show(); //Llamamos el método show() de base...
    return 0;
}