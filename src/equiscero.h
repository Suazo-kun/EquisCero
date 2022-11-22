#ifndef EQUIS_CERO_H
#define EQUIS_CERO_H

#define SINRESULTADO 0
#define GANASTE 1
#define PERDISTE 2
#define EMPATE 3

#define LIMPIO ' '
#define X_CHAR 'x'
#define O_CHAR 'o'

void TurnoDeLaPC(char *tabla, unsigned char dificultad);
unsigned char EvaluarTabla(const char tabla[9]);

#endif
