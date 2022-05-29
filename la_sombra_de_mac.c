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

void realizar_movimiento_personaje(coordenada_t* pos_recibida, char movimiento){
    if (movimiento == MOVER_ARRIBA){
        (*pos_recibida).fila --;
    }else if (movimiento == MOVER_ABAJO){
        (*pos_recibida).fila ++;
    }else if (movimiento == MOVER_IZQUIERDA){
        (*pos_recibida).col --;
    }else if (movimiento == MOVER_DERECHA){
        (*pos_recibida).col ++;
    }
}

void realizar_movimiento_sombra(coordenada_t* pos_recibida, char movimiento){
    if (movimiento == MOVER_ARRIBA){
        (*pos_recibida).fila --;
    }else if (movimiento == MOVER_ABAJO){
        (*pos_recibida).fila ++;
    }else if (movimiento == MOVER_IZQUIERDA){
        (*pos_recibida).col ++;
    }else if (movimiento == MOVER_DERECHA){
        (*pos_recibida).col --;
    }
}

coordenada_t coordenada_aleatoria(int max_alto, int max_ancho){
    coordenada_t coordenada_aleatoria_interna;
    coordenada_aleatoria_interna.fila = rand () % max_alto;
    coordenada_aleatoria_interna.col = rand () % max_ancho;
    return coordenada_aleatoria_interna;
}

bool coordenadas_iguales(coordenada_t a, coordenada_t b){ 
    return((a.fila == b.fila) && (a.col == b.col));
}

bool esta_dentro_rango(coordenada_t posicion, int max_alto, int max_ancho){
    return ((posicion.col >= 0) && (posicion.col < max_ancho) && (posicion.fila >= 0) && (posicion.fila < max_alto));
}

void inicializar_personaje(personaje_t* ref_personaje, coordenada_t arranque_personaje){
    (*ref_personaje).posicion = arranque_personaje;
    (*ref_personaje).vida = VIDAS_INICIO;
    (*ref_personaje).puntos = 0;
    (*ref_personaje).tiene_llave = false;
    (*ref_personaje).interruptor_apretado = false;
}

void inicializar_sombra(sombra_t* ref_sombra, coordenada_t arranque_sombra){
    (*ref_sombra).posicion = arranque_sombra;
    (*ref_sombra).esta_viva = true;
}

bool es_movimiento_valido(char movimiento){
    return ((movimiento == MOVER_ARRIBA) || (movimiento == MOVER_IZQUIERDA) || (movimiento == MOVER_ABAJO) || (movimiento == MOVER_DERECHA) || (movimiento == AUXILIAR_FIN));
}

void pedir_movimiento(char* ref_movimiento){
    printf("Ingrese un movimiento\n");
    scanf(" %c", ref_movimiento);
    if (!es_movimiento_valido(*ref_movimiento)){
        printf("Ese movimiento no es válido, te pido que ingreses '%c', '%c', '%c' o '%c' para moverte para arriba, para la izquierda, para abajo o para la derecha, respectivamente\n", MOVER_ARRIBA, MOVER_IZQUIERDA, MOVER_ABAJO, MOVER_DERECHA);
        scanf(" %c", ref_movimiento);
    }
    while (!es_movimiento_valido(*ref_movimiento)){
        printf("Ese movimiento no es válido, te pido que ingreses un movimiento válido para continuar\n");
        scanf(" %c", ref_movimiento);
    }
    
}

void mover_personaje(personaje_t* ref_personaje, sombra_t* ref_sombra, char movimiento){
    coordenada_t pos_nueva_personaje = (*ref_personaje).posicion;
    realizar_movimiento_personaje(&pos_nueva_personaje, movimiento);

    if (esta_dentro_rango(pos_nueva_personaje, MAX_FILAS, MAX_COLUMNAS)){
        (*ref_personaje).posicion = pos_nueva_personaje;
    }
    
    coordenada_t pos_nueva_sombra = (*ref_sombra).posicion;
    realizar_movimiento_sombra(&pos_nueva_sombra, movimiento);

    if (esta_dentro_rango(pos_nueva_sombra, MAX_FILAS, MAX_COLUMNAS)){
        (*ref_sombra).posicion = pos_nueva_sombra;
    }
    
}

int buscar_elemento(elemento_t elementos[MAX_ELEMENTOS], int tope, coordenada_t posicion){
    int posicion_elemento = -1;
    int veces_while = 0;
    bool encontrado = false;

    while((veces_while < tope) && !encontrado){
        if(coordenadas_iguales(elementos[veces_while].posicion, posicion)){
            posicion_elemento = veces_while;
            encontrado = true;
        }
        veces_while ++;
    }

    return posicion_elemento;
}

void imprimir_terreno(juego_t juego){
    char dibujo[MAX_FILAS][MAX_COLUMNAS];

    for (int i = 0; i < MAX_FILAS; ++i){
        for (int j = 0; j < MAX_COLUMNAS; ++j){
            dibujo[i][j] = '-';
        }
    }

    dibujo [juego.personaje.posicion.fila][juego.personaje.posicion.col] = LETRA_MAC;
    dibujo [juego.sombra.posicion.fila][juego.sombra.posicion.col] = LETRA_BLOO;

    for (int i = 0; i < MAX_FILAS; ++i){
        for (int j = 0; j < MAX_COLUMNAS; ++j){
            printf(" %c ", dibujo[i][j]);
        }
        printf("\n");
    }
}
