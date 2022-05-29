#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "la_sombra_de_mac.h"

#define MOVER_ARRIBA 'W'
#define MOVER_IZQUIERDA 'A'
#define MOVER_ABAJO 'S'
#define MOVER_DERECHA 'D'
#define AUXILIAR_FIN 'F'

#define LETRA_MAC 'M'
#define LETRA_BLOO 'B'
#define VIDAS_INICIO 0

/* 
*  Pre: La coordenada no debe salirse de los parámetros, ya sea excediendo
*  el máximo de filas o columnas o poseer un número negativo.  
*  Post: Devuelve la coordenada de Bloo (Estando dentro de los limites establecidos).
*/
coordenada_t coordenada_para_bloo(coordenada_t ref_coordenada_mac){
    coordenada_t coordenada_interna;
    coordenada_interna.fila = ref_coordenada_mac.fila;
    coordenada_interna.col = (MAX_COLUMNAS - 1) - ref_coordenada_mac.col;
    return coordenada_interna;
}


int main (){

    srand (( unsigned)time(NULL)); // Genera la semilla aleatoria.

    coordenada_t coordenada_mac = coordenada_aleatoria(MAX_FILAS, MAX_COLUMNAS); // Genera unas coordenadas aleatoria y se la asigna a Mac

    coordenada_t coordenada_bloo = coordenada_para_bloo(coordenada_mac); // Calcula las coordenadas de Bloo a partir de la de mac y se las asignan

    printf("Los valores de Mac son fila %i y columa %i, y los de Bloo son fila %i y columna %i\n", coordenada_mac.fila, coordenada_mac.col, coordenada_bloo.fila, coordenada_bloo.col);
    // Verifica que se generen en espejo

    if (coordenadas_iguales(coordenada_mac, coordenada_bloo)){
        printf("Las coordenadas de Mac y Bloo son iguales\n");
    }else{
        printf("Las coordenadas de Mac y Bloo no son iguales\n");
    } // Verifica que las coordenadas no sean iguales

    if (coordenadas_iguales(coordenada_mac, coordenada_mac)){
        printf("Las coordenadas 1 y 2 son iguales\n");
    }else{
        printf("Las coordenadas 1 y 2 no son iguales\n");
    } // Verifica que la función pueda devolver false

    coordenada_t coordenada_fuera_rango; 
    coordenada_fuera_rango.fila = 40;
    coordenada_fuera_rango.col = -10;
    // Crea una coordenada y le asigna valores que esten fuera de rango

    if (esta_dentro_rango(coordenada_mac, MAX_FILAS, MAX_COLUMNAS)){
        printf("La coordenada de Mac esta dentro del rango\n");
    }else{
        printf("La coordenada de Mac no esta dentro del rango\n");
    } // Verifica que la coordenada de Mac esté dentro del rango

    if (esta_dentro_rango(coordenada_fuera_rango, MAX_FILAS, MAX_COLUMNAS)){
        printf("La coordenada ingresada esta dentro del rango\n");
    }else{
        printf("La coordenada ingresada no esta dentro del rango\n");
    } // Verifica que la funcion pueda devolver false

    printf("\n");

    personaje_t personaje;

    inicializar_personaje (&personaje, coordenada_mac); // Inicializa al personaje (Le asigna los valores generados y los iniciales)
    
    printf("La posición del personaje es columna %i y fila %i, su vidas son %i y sus puntos son %i \n", personaje.posicion.col, personaje.posicion.fila, personaje.vida, personaje.puntos); // Imprime el status del personaje (menos los bool)

    sombra_t sombra;

    inicializar_sombra (&sombra, coordenada_bloo); // Inicializa la sombra (Le asigna los valores generados y los iniciales)

    printf("La posición de la sombra es columna %i y fila %i\n", sombra.posicion.col, sombra.posicion.fila); // Imprime el status de la sombra (Solo las coordenadas porque la otra es un bool)

    printf("\n");

    juego_t juego;
    juego.personaje = personaje;
    juego.sombra = sombra;
    // Inicializa la variable juego (Le asigna los datos inicializados anteriormente a personaje y sombra)

    printf("Este es el terreno inicial\n");

    imprimir_terreno(juego); // Verifica que todo este saliendo bien con el terreno

    char movimiento;

    pedir_movimiento(&movimiento); // Pide un movimiento valido

    printf("\n");

    printf("La posición del personaje es fila %i columna %i y la de la sombra es fila %i columna %i\n", juego.personaje.posicion.fila, juego.personaje.posicion.col, juego.sombra.posicion.fila, juego.sombra.posicion.col); // Imprime las coordenadas del personaje y de la sombra

    mover_personaje(&(juego.personaje), &(juego.sombra), movimiento); // Mueve al personaje

    printf("La posición del personaje es fila %i columna %i y la de la sombra es fila %i columna %i\n", juego.personaje.posicion.fila, juego.personaje.posicion.col, juego.sombra.posicion.fila, juego.sombra.posicion.col); // Verifica que haya un cambio de coordenadas (Y que sea el correspondiente) 

    elemento_t vector_elemento[MAX_ELEMENTOS];
    vector_elemento[3].posicion.fila = 10;
    vector_elemento[3].posicion.col = 14;
    int tope = 4;
    coordenada_t coordenada_para_vector;
    coordenada_para_vector.fila = 10;
    coordenada_para_vector.col = 14;
    // Inicializa un vector de elementos

    int posicion_en_vector = buscar_elemento(vector_elemento, tope, coordenada_para_vector); // Asigna la posicion en el vector del elemento en cuestion a la variable

    printf("La posición en el vector del elemento es %i\n", posicion_en_vector); // Verifica que funcione

    vector_elemento[3].posicion.col = 12; // Cambia la coordenada del vector

    posicion_en_vector = buscar_elemento(vector_elemento, tope, coordenada_para_vector); // Reasigna el valor de la posicion

    printf("La posición en el vector del elemento es %i\n", posicion_en_vector); // Verifica que devuelva -1 en caso de que no encuentre el elemento

    vector_elemento[1].posicion.fila = 10;
    vector_elemento[1].posicion.col = 14;
    // Crea una posicion anterior en el vector con las mismas coordenadas

    posicion_en_vector = buscar_elemento(vector_elemento, tope, coordenada_para_vector); // Reasigna el valor de la posicion

    printf("La posición en el vector del elemento es %i\n", posicion_en_vector); // Verifica que el valor corresponda al primer elemento que se encuentre (Aun si hay otros despues)

    imprimir_terreno(juego); // Imprime el terreno y verifica todo lo anterior

    while(movimiento != AUXILIAR_FIN){
        pedir_movimiento(&movimiento);
        mover_personaje(&(juego.personaje), &(juego.sombra), movimiento);
        system("clear");
        imprimir_terreno(juego);
        printf("La posición del personaje es fila %i columna %i y la de la sombra es fila %i columna %i\n",juego.personaje.posicion.fila, juego.personaje.posicion.col, juego.sombra.posicion.fila, juego.sombra.posicion.col);
    } // Hace un ciclo infinito (del que solo se sale Ingresando la "F") en el que pide un movimiento, realiza dicho
      // movimiento, limpia de la terminal lo escrito antes, imprime un terreno y las coordenadas de los personajes
      
    return 0;
}