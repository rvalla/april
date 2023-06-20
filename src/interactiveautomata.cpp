#include <iostream>
#include <stdio.h>

/*Intentaremos construir un autómata celular que imprima su evolución en la terminal. Como todo
autómata celular tendrá células y algunas reglas para evolucionar. Vamos a tener dos modos de
evolución en la misma clase autómata.*/
/*Esta vez intentamos controlarlo desde la línea de comandos para que sea más divertido. Vamos
a ir guardando los parámetros de configuración para instanciar la clase automata al final.*/

class cell { //Definimos una clase cell...
    public:
        bool alive; //La clase tiene algunos atributos...
        bool will_be_alive;
        int code;

        cell(){ //¡Este constructor parece ser necesario! No sé cómo evitar llamarlo...
            alive = false;
            will_be_alive = false;
            code = 0;
        }

        cell(bool a, int c){ //¡Este es el constructor!
            alive = a;
            will_be_alive = false;
            code = c;
        }

        void update(){ //Acá la célula toma su nuevo estado...
            alive = will_be_alive;
        }
};

class automata { //Definimos una clase automata...
    public:
        int size; //La clase tiene algunos atributos públicos...
        int mode; //Vamos a tener dos modos de evolución...
        int generations; //Decidimos qué cantidad de generaciones calculamos...
        char alive_char; //Tenemos un caracter para las células vivas...
        char death_char; //Tenemos un caracter para las células muertas...

        automata(int s, int m, int g, char ac, char dc, std::string is){
            size = s; //Tiene que ser la cantidad de células...
            mode = m; //Tiene que ser 0 o 1...
            generations = g; //Tiene que ser un número natural...
            cell cells[size]; //Inicializamos las células ahora que sabemos cuántas son...
            bool * initial_state = build_initial_state(is); //Aća tenemos un puntero (ver más adelante).
            for (int i = 0; i < size; i++){ 
                cells[i] = cell(initial_state[i], i); //Cargamos las células...
            }
            alive_char = ac; //Guardamos el caracter vivo
            death_char = dc; //Guardamos el caracter muerto
            run(cells);
        }

        /*Como inicialmente no conocemos el tamaño del autómata porque es el usuario
        quien define la cantidad de células decidimos no definir el arreglo de células
        afuera del constructor (deberíamos usar un vector porque no conocemos el tamaño).
        Entonces vamos pasando el arreglo de células de una función a otra. No es lo más
        elegante, pero no dominamos C++ todavía.*/
        void run(cell cells[]){ //El método que ejecuta el autómata...
            for (int i = 0; i < generations; i++){ 
                print_state(cells); //Imprimimos una generación...
                evolve(cells); //Calculamos la siguiente generación...
            }
        }

        void evolve(cell cells[]){ //Lo hacemos evolucionar...
            for (int i = 0; i < size; i++){ 
                evolve_cell(cells, i); //Calculamos qué pasa en la generación siguiente...
            }
            for (int i = 0; i < size; i++){ 
                cells[i].update(); //Actualizamos la célula ya calculada...
            }
        }

        void evolve_cell(cell cells[], int c){ //Este método define si una célula vivirá o morirá...
            int n = 0;
            if (mode == 0){ //Distinguimos entre dos modos...
                /*El modo 0 cuenta la cantidad de vecinos para cualquier célula. Si tienen
                un vecino estarán vivas en la generación siguiente.*/
                if (cells[get_cell_position(c-1)].alive){ //ver get_cell_position() más adelante...
                    n += 1;
                }
                if (cells[get_cell_position(c+1)].alive){
                    n += 1;
                }
                if (n == 1){
                    cells[c].will_be_alive = true;
                } else {
                    cells[c].will_be_alive = false;
                }
            } else { //Acá viene el modo dos...
                /*El modo 1 cuenta la cantidad de vecinos para las células muertas. Si tienen
                un vecino estarán vivas en la generación siguiente. Si están vivas, se mueren.*/
                if (cells[c].alive == false){
                    if (cells[get_cell_position(c-1)].alive){
                        n += 1;
                    }
                    if (cells[get_cell_position(c+1)].alive){
                        n += 1;
                    }
                    if (n == 1){
                        cells[c].will_be_alive = true;
                    }
                } else {
                    cells[c].will_be_alive = false;
                }
            }
        }

        /*En álgebra el resto de dividir un entero por un número es siempre positivo. En C++ no.
        Eso es un problema porque queremos que las células de los bordes busquen sus vecinos del
        otro lado del arreglo. Entonces con la función get_cell_position() nos aseguramos que
        los vecinos estén siempre adentro del arreglo.*/
        int get_cell_position(int n){
            int p = n%size; //Calculamos el resto de dividir posición del vecino / tamaño del autómata.
            if (p<0){ //Si el resto es negativo le sumamos el tamaño.
                p += size;
            }
            return p;
        }

        /*¡Acá nos divertimos! Queremos que el usuario pueda pasarnos un estado inicial. Pero
        no queremos que tenga que pasarnos una lista de 150 estados (vivos - muertos). Por eso
        le pedimos un string con 0s y 1s y construimos nuestro estado inicial a partir de ese
        string. La idea es acomodar en el medio de un arreglo del mismo tamaño que el autómata
        el estado inicial del usuario.*/
        bool * build_initial_state(std::string is){
            /*Tenemos que devolver un arreglo pero eso no se puede. Vamos a devolver un puntero
            a donde quede guardado el arreglo que hacemos.*/
            bool * state = new bool[size]; //Acá definimos un puntero hacia un arreglo de tamaño size.
            for (int i = 0; i<size; i++){
                state[i] = false; //Inicializamos todas las posiciones del arreglo.
            }
            bool user_state[is.size()-1]; //Definimos un arreglo del tamaño del string del usuario.
            int user_state_width = is.size()-1; //El string nos llega con un caracter de más.
            for (int i = 0; i<user_state_width; i++){
                if (is[i] == '1'){ //Si el usuario mandó 1 asignamos true a la posición...
                    user_state[i] = true;
                } else { //Si no asignamos falso...
                    user_state[i] = false;
                }
            }
            /*Ok. Ahora tenemos un arreglo de tamaño size lleno de false y un arreglo del usuario
            más chico con el estado inicial que queremos. Lo vamos a guardar en el arreglo grande,
            pero en el medio.*/
            int jump = (size - user_state_width) / 2; //Calculamos cuánto margen dejar...
            for (int i = 0; i < user_state_width; i++){ //Asignamos los valores...
                state[jump + i] = user_state[i];
            }
            return state; //Devolvemos la dirección del puntero que apunta al arreglo.
        }

        void print_state(cell cells[]){ //Simplemente para imprimir el estado del autómata...
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

void create_automata(){
    /*Vamos a definir las variables en donde guardar la configuración.*/
    int size;
    int mode;
    int generations;
    char alive;
    char dead;
    std::string state;
    //Recolectemos los parámetros...
    std::cout << "¿Cuántas células querés que tenga?" << std::endl;
    std::cin >> size;
    std::cout << "¿Qué modo de evolución elegís? Elegí: 0 o 1" << std::endl;
    std::cin >> mode;
    std::cout << "¿Cuántas generaciones querés que calcule?" << std::endl;
    std::cin >> generations;
    std::cout << "¿Con qué símbolo querés que represente la vida?" << std::endl;
    std::cin >> alive;
    std::cout << "¿Con qué símbolo querés que represente la muerte?" << std::endl;
    std::cin >> dead;
    std::cout << "¡Sólo falta que definas un estado inicial!" << std::endl;
    std::cout << "Tenés que mandarme una cadena sin espacios de 0s y 1s.\n" << std::endl;
    std::cout << "No puede superar la cantidad de células." << std::endl;
    std::cin >> state;
    //Creemos el autómata ahora...
    std::cout << "\n\n";
    automata a = automata(size, mode, generations, alive, dead, state);
    std::cout << "\n\n";
}

int main() { //El programa siempre empieza por acá.
    char d;
    while (true){
        std::cout << "¿Querés que calculemos un autómata celular? Elegí S o N." << std::endl;
        std::cin >> d;
        if (d=='s' || d=='S'){
            create_automata();
        } else {
            break;
        }
    }
    std::cout << "Parece que ya no tengo nada que hacer." << std::endl;
    return 0;
}