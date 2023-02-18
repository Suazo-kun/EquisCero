#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "equiscero.h"

unsigned char srand_llamado = 0;

unsigned char ObtenerNumeroAleatorio(unsigned char min, unsigned char max) {
    if (!srand_llamado) {
        srand(time(0));
        srand_llamado = 1;
    }

    return ((float)rand()) / RAND_MAX * max + min;
}

unsigned char RealizarJugadaPorPatron(char tabla[9]) {
    unsigned char jugadas_cantidad = 0;
    unsigned char i;

    for (i=0;i<9;i++) {
        if ((tabla[i] == O_CHAR) || (tabla[i] == X_CHAR)) {
            jugadas_cantidad++;
        }
    }

    if (jugadas_cantidad == 1) {
        if (strncmp(tabla, "    x    ", 9) == 0) {
            tabla[2] = O_CHAR;
            return 1;

        } else if (
            (strncmp(tabla, "x        ", 9) == 0) || (strncmp(tabla, "  x      ", 9) == 0) ||
            (strncmp(tabla, "      x  ", 9) == 0) || (strncmp(tabla, "        x", 9) == 0)) {
            tabla[4] = O_CHAR;
            return 1;

        } else {
            char tabla_temp[] = "         ";

            for (i=1;i<8;i+=2) {
                if (i > 1) tabla_temp[i-2] = LIMPIO;
                tabla_temp[i] = X_CHAR;

                if (strncmp(tabla, tabla_temp, 9) == 0) {
                    tabla[8-i] = O_CHAR;
                    return 1;
                }
            }
        }

    } else if (jugadas_cantidad == 3) {
        if ((strncmp(tabla, "x   o   x", 9) == 0) || (strncmp(tabla, "  x o x  ", 9) == 0)) {
            tabla[ObtenerNumeroAleatorio(0, 3) * 2 + 1] = O_CHAR;
            return 1;
        }

        if (tabla[4] == X_CHAR) {
            if ((tabla[0] == X_CHAR) && (tabla[8] == O_CHAR)) {
                tabla[6] = O_CHAR;
                return 1;
            } else if ((tabla[2] == X_CHAR) && (tabla[6] == O_CHAR)) {
                tabla[8] = O_CHAR;
                return 1;
            } else if ((tabla[6] == X_CHAR) && (tabla[2] == O_CHAR)) {
                tabla[0] = O_CHAR;
                return 1;
            } else if ((tabla[8] == X_CHAR) && (tabla[0] == O_CHAR)) {
                tabla[2] = O_CHAR;
                return 1;
            }

            if ((tabla[1] == X_CHAR) && (tabla[7] == O_CHAR)) {
                tabla[ObtenerNumeroAleatorio(0, 1) ? 0 : 2] = O_CHAR;
                return 1;
            } else if ((tabla[7] == X_CHAR) && (tabla[1] == O_CHAR)) {
                tabla[ObtenerNumeroAleatorio(0, 1) ? 6 : 8] = O_CHAR;
                return 1;
            } else if ((tabla[3] == X_CHAR) && (tabla[5] == O_CHAR)) {
                tabla[ObtenerNumeroAleatorio(0, 1) ? 0 : 6] = O_CHAR;
                return 1;
            } else if ((tabla[5] == X_CHAR) && (tabla[3] == O_CHAR)) {
                tabla[ObtenerNumeroAleatorio(0, 1) ? 2 : 8] = O_CHAR;
                return 1;
            }
        }

        for (i=1;i<8;i+=6) {
            if ((tabla[1*i] == X_CHAR) && (tabla[3] == X_CHAR) && (tabla[7/i] == O_CHAR)) {
                tabla[i-1] = O_CHAR;
                return 1;
            } else if ((tabla[1*i] == X_CHAR) && (tabla[5] == X_CHAR) && (tabla[7/i] == O_CHAR)) {
                tabla[i+1] = O_CHAR;
                return 1;
            } else if ((tabla[i-1?3:5] == X_CHAR) && (tabla[1] == X_CHAR) && (tabla[i-1?5:3] == O_CHAR)) {
                tabla[i-1?0:2] = O_CHAR;
                return 1;
            } else if ((tabla[i-1?3:5] == X_CHAR) && (tabla[7] == X_CHAR) && (tabla[i-1?5:3] == O_CHAR)) {
                tabla[i-1?6:8] = O_CHAR;
                return 1;
            }
        }

        if ((tabla[1] == X_CHAR) && (tabla[8] == X_CHAR)) {
            tabla[2] = O_CHAR;
            return 1;
        } else if ((tabla[1] == X_CHAR) && (tabla[6] == X_CHAR)) {
            tabla[0] = O_CHAR;
            return 1;
        } else if ((tabla[5] == X_CHAR) && (tabla[0] == X_CHAR)) {
            tabla[2] = O_CHAR;
            return 1;
        } else if ((tabla[5] == X_CHAR) && (tabla[6] == X_CHAR)) {
            tabla[8] = O_CHAR;
            return 1;
        } else if ((tabla[7] == X_CHAR) && (tabla[2] == X_CHAR)) {
            tabla[8] = O_CHAR;
            return 1;
        } else if ((tabla[7] == X_CHAR) && (tabla[0] == X_CHAR)) {
            tabla[6] = O_CHAR;
            return 1;
        } else if ((tabla[3] == X_CHAR) && (tabla[2] == X_CHAR)) {
            tabla[0] = O_CHAR;
            return 1;
        } else if ((tabla[3] == X_CHAR) && (tabla[8] == X_CHAR)) {
            tabla[6] = O_CHAR;
            return 1;
        }
    } else if ((jugadas_cantidad == 5) && (tabla[4] == LIMPIO)) {
        tabla[4] = O_CHAR;
        return 1;
    }

    return 0;
}

unsigned char RealizarJugada(char tabla[9], const char caracter) {
    char temp[4];
    char patron1[] = {caracter, caracter};
    char patron2[] = {caracter, LIMPIO, caracter};
    unsigned char i;

    for (i=0;i<9;i+=3) { 
        snprintf(temp, 3, "%s", tabla+i);

        // Evalúa: "xx ".
        if ((strncmp(temp, patron1, 2) == 0) && (tabla[2+i] == ' ')) {
            tabla[2+i] = O_CHAR;
            return 1;
        }

        snprintf(temp, 3, "%s", tabla+i+1);

        // Evalúa: " xx".
        if ((strncmp(temp, patron1, 2) == 0) && (tabla[i] == ' ')) {
            tabla[i] = O_CHAR;
            return 1;
        }

        snprintf(temp, 4, "%s", tabla+i);

        // Evalúa: "x x".
        if (strncmp(temp, patron2, 3) == 0) {
            tabla[i+1] = O_CHAR;
            return 1;
        }
    }

    for (i=0;i<3;i++) { 
        sprintf(temp, "%c%c", tabla[i], tabla[i+3]);

        // Evalúa: "xx " (verticalmente).
        if ((strncmp(temp, patron1, 2) == 0) && (tabla[i+6] == ' ')) {
            tabla[i+6] = O_CHAR;
            return 1;
        }

        sprintf(temp, "%c%c", tabla[i+3], tabla[i+6]);

        // Evalúa: " xx" (verticalmente).
        if ((strncmp(temp, patron1, 2) == 0) && (tabla[i] == ' ')) {
            tabla[i] = O_CHAR;
            return 1;
        }

        sprintf(temp, "%c%c%c", tabla[i], tabla[i+3], tabla[i+6]);

        // Evalúa: "x x" (verticalmente).
        if (strncmp(temp, patron2, 3) == 0) {
            tabla[i+3] = O_CHAR;
            return 1;
        }
    }

    for (i=0;i<3;i+=2) { 
        sprintf(temp, "%c%c", tabla[i], tabla[4]);

        // Evalúa: "xx " (diagonal).
        if ((strncmp(temp, patron1, 2) == 0) && (tabla[8-i] == ' ')) {
            tabla[8-i] = O_CHAR;
            return 1;
        }

        sprintf(temp, "%c%c", tabla[8-i], tabla[4]);

        // Evalúa: " xx" (diagonal).
        if ((strncmp(temp, patron1, 2) == 0) && (tabla[i] == ' ')) {
            tabla[i] = O_CHAR;
            return 1;
        }

        sprintf(temp, "%c%c%c", tabla[i], tabla[4], tabla[8-i]);

        // Evalúa: "x x" (diagonal).
        if (strncmp(temp, patron2, 3) == 0) {
            tabla[4] = O_CHAR;
            return 1;
        }
    }

    return 0;
}

void TurnoDeLaPC(char *tabla, unsigned char dificultad) {
    switch (dificultad) {
        case 1:
            goto dificultad_1;
        case 2:
            goto dificultad_2;
        case 3:
            goto dificultad_3;
        default:
            goto fin;
    }

dificultad_1: ; // Por aleatoriedad.
    unsigned char casilla;

    while (1) {
        casilla = ObtenerNumeroAleatorio(0, 8);

        if (tabla[casilla] == LIMPIO) {
            tabla[casilla] = O_CHAR;
            break;
        }
    }

    goto fin;

dificultad_2: ; // Por aleatoriedad y algoritmo.
    if (ObtenerNumeroAleatorio(1, 2) == 1) {
        goto dificultad_1;
    } else {
        goto dificultad_3;
    }

    goto fin;

dificultad_3: ; // Por algoritmo (y aleatoriedad en algunos casos).
    
    if (RealizarJugadaPorPatron(tabla)) {
        goto fin;
    } else if (RealizarJugada(tabla, O_CHAR)) {
        goto fin;
    } else if (RealizarJugada(tabla, X_CHAR)) {
        goto fin;
    }

    // En caso de no cumplirse ninguna condición.
    goto dificultad_1;

fin: ;
}

unsigned char EvaluarTabla(const char tabla[9]) {
    unsigned char i;
    char temp[4];

    for (i=0;i<9;i+=3) {
        snprintf(temp, 4, "%s", tabla+i);

        if (strcmp(temp, "xxx") == 0) {
            return GANASTE;
        } else if (strcmp(temp, "ooo") == 0) {
            return PERDISTE;
        }
    }

    for (i=0;i<3;i++) {
        sprintf(temp, "%c%c%c", tabla[i], tabla[i+3], tabla[i+6]);

        if (strcmp(temp, "xxx") == 0) {
            return GANASTE;
        } else if (strcmp(temp, "ooo") == 0) {
            return PERDISTE;
        }
    }
    
    for (i=2;i<5;i+=2) {
        sprintf(temp, "%c%c%c", tabla[-2+i], tabla[4], tabla[10-i]);

        if (strcmp(temp, "xxx") == 0) {
            return GANASTE;
        } else if (strcmp(temp, "ooo") == 0) {
            return PERDISTE;
        }
    }

    for (i=0;i<9;i++) {
        if ((tabla[i] != X_CHAR) && (tabla[i] != O_CHAR)) {
            return SINRESULTADO;
        }
    }

    return EMPATE;
}
