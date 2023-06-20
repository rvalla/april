#include <iostream>
#include <stdio.h>

/*Intentaremos construir un autómata celular que
imprima su evolución en la terminal. Como todo
autómata celular tendrá células y algunas reglas
para evolucionar.*/

class cell { //Definimos una clase cell...
    public:
        bool alive; //La clase tiene algunos atributos...
        bool will_be_alive;
        int code;

        cell(){
            alive = false;
            will_be_alive = false;
            code = 0;
        }

        cell(bool a, int c){ //¡Este es el constructor!
            alive = a;
            will_be_alive = false;
            code = c;
        }

        void update(){
            alive = will_be_alive;
        }
};

class automata { //Definimos una clase automata...
    public:
        int size; //La clase tiene algunos atributos públicos...
        int generations;
        cell cells[100]; //Definimos la cantidad de células explícitamente...
        char alive_char;
        char death_char;

        automata(int g, char ac, char dc, bool initial_state[], int initial_width){
            size = 100; //Tiene que ser la cantidad de células...
            generations = g;
            for (int i = 0; i < size; i++){ 
                cells[i] = cell(initial_state[i%initial_width], i); //Cargamos las células...
            }
            alive_char = ac; //Guardamos el caracter vivo
            death_char = dc; //Guardamos el caracter muerto
            run();
        }

        void run(){ //El método que ejecuta el autómata...
            for (int i = 0; i < generations; i++){ 
                print_state();
                evolve();
            }
        }

        void evolve(){ //Lo hacemos evolucionar...
            for (int i = 0; i < size; i++){ 
                evolve_cell(i);
            }
            for (int i = 0; i < size; i++){ 
                cells[i].update();
            }
        }

        void evolve_cell(int c){ //Este método define si una célula vivirá o morirá...
            int n = 0;
            if (cells[(c-1%size)].alive){
                n += 1;
            }
            if (cells[(c+1%size)].alive){
                n += 1;
            }
            if (n == 1){
                cells[c].will_be_alive = true;
            } else {
                cells[c].will_be_alive = false;
            }
        }

        void print_state(){ //Simplemente para imprimir el estado del autómata...
            for (int i = 0; i < size; i++){
                if (cells[i].alive){
                    std::cout << alive_char;
                } else {
                    std::cout << death_char;
                } 
            }
            std::cout << "\n";
        }

};

class other_automata { //Definimos otra clase automata...
    public:
        int size; //La clase tiene algunos atributos públicos...
        int generations;
        cell cells[125]; //Definimos la cantidad de células...
        char alive_char;
        char death_char;

        other_automata(int g, char ac, char dc, bool initial_state[], int initial_width){
            size = 125; //Tiene que ser la cantidad de células...
            generations = g;
            for (int i = 0; i < size; i++){ 
                cells[i] = cell(initial_state[i%initial_width], i);
            }
            alive_char = ac;
            death_char = dc;
            run();
        }

        void run(){
            for (int i = 0; i < generations; i++){ 
                print_state();
                evolve();
            }
        }

        void evolve(){
            for (int i = 0; i < size; i++){ 
                evolve_cell(i);
            }
            for (int i = 0; i < size; i++){ 
                cells[i].update();
            }
        }

        void evolve_cell(int c){ //Una regla distinta para que el autómata evolucione...
            int n = 0;
            if (cells[(c-1%size)].alive){
                n += 1;
            }
            if (cells[(c+1%size)].alive){
                n += 1;
            }
            if (n == 1){
                if (cells[c].alive == false){
                    cells[c].will_be_alive = true;
                } else {
                    cells[c].will_be_alive = false;
                }
            } else {
                cells[c].will_be_alive = false;
            }
        }

        void print_state(){
            for (int i = 0; i < size; i++){
                if (cells[i].alive){
                    std::cout << alive_char;
                } else {
                    std::cout << death_char;
                } 
            }
            std::cout << "\n";
        }

};

int main() { //El programa siempre empieza por acá.
    std::cout << "Vamos a simular un autómata celular. Dame 1 millonésima de segundo...\n" << std::endl;
    bool initial_state[] = {false,false,false,false,false,false,true,false,false,false,false,false,false}; //Definimos un estado inicial
    automata a = automata(50, '*', '-', initial_state, 13); //Construimos un automata de 50 generaciones...
    std::cout << "\n";
    bool initial_state_2[] = {false,false,false,false,false,false,true,false,false,false,false,false,false}; //Definimos un estado inicial
    other_automata o_a = other_automata(75, '0', '+', initial_state, 13); //Construimos un other_automata de 75 generaciones...
    std::cout << "\n";
    return 0;
}