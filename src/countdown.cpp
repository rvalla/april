#include <iostream>
#include <stdlib.h> //Vamos a usar números al azar
#include <time.h> //Sólo para inicializar rand()

/*Acá nos inventamos una función para hacer cuentas
*regresivas. La idea es que la función recibe el
*número de partida y va imprimiendo en pantalla
*todos los números hasta que llega a 0.
*/
void countDown(int number){ //La función recibe un entero
    std::cout << std::to_string(number); //Imprimimos el número.
    std::cout << "\n"; //Agregamos el salto de línea.
    if (number > 0) //Si todavía no llegamos a 0 hacemos countDown(n-1)
        /*¡Llamamos countDown() desde countDown()!
        *Es una llamada recursiva. La recursión es
        *muy poderosa aunque si la llamás mal cuelga el programa.
        *vale probar llamar countDown(number) (sin restar nada).
        */
        countDown(number - 1);
}

//Parece que main() tiene que ir abajo...
int main() {
    srand(time(NULL)); //Hay que inicializar el generador aleatorio.
    /*Vamos a pedir un número al azar usando rand().
    *rand() devuelve un entero al azar entre 0 y 32767
    *(el máximo puede cambiar según la librería que se use).
    *Para acotar el número agregamos "% 100" para quedarnos
    *con el resto de dividir rand() por 100.
    */
    int number = rand() % 100;
    countDown(number); //A imprimir la cuenta regresiva nomás...
    return 0;
}