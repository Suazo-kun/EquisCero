#include <stdio.h>
#include "equiscero.h"

#if (defined __WIN32__) || (defined _WIN32)
#include <windows.h>
#define limpiar() system("cls")
#define pausa() system("pause > nul")
#else
#define limpiar() system("clear")
#define pausa() getchar()
#endif

char tabla[9];
unsigned char dificultad = 0;

void EquisCeroLogo() {
    printf(
        "\t\t\t""┌─         º ┌─    ┌── ┌─ ┌─┐ ┌─┐""\n"
        "\t\t\t""├─ ┌─┐ | | | └─┐   |   ├─ ├─┘ | |""\n"
        "\t\t\t""└─ └─┤ └─┘ |  ─┘   └── └─ | \\ └─┘""\n"
        "\n\n\n\n\n"
    );
}

void LimpiarTabla() {
    for (unsigned char i=0;i<9;i++) {
        tabla[i] = LIMPIO;
    }
}

void ImprimirTabla() {
    printf(
        " %c | %c | %c\n───┼───┼───\n %c | %c | %c\n───┼───┼───\n %c | %c | %c\n",
        tabla[0], tabla[1], tabla[2], tabla[3], tabla[4], tabla[5], tabla[6],
        tabla[7], tabla[8]
    );
}

void ElegirCasilla() {
    unsigned char casilla;

    printf("NOTA: Ponga un número del 1 al 9 para elegir su casilla.\n");

    while (1) {
        printf("Casilla: "); casilla = getchar();

        if (getchar() != '\n') {
            while (getchar() != '\n');

            printf("\nPero mamañema se te está pidiendo un número del 1 al 9.\n");

        } else if ((casilla < '1') || (casilla > '9')) {
            printf("\nPero ANORMAL, pon un número del 1 al 9, singa tu madre.\n");

        } else if (tabla[casilla - '1'] != LIMPIO) {
            printf(
                "\nMi vida, mi amor, mi todo... Esa maldita casilla ya está "
                "elegida, MAMAGUEVAZO\n"
            );

        } else {
            tabla[casilla - '1'] = X_CHAR;
            break;
        }

        printf("[Pulsa una tecla]\n"); pausa();
        printf("Ahora sí hazlo bien.\n\n");
    }
}

unsigned char Comprobar() {
    unsigned char resultado = EvaluarTabla(tabla);

    if (resultado == GANASTE) {
        ImprimirTabla(); printf("\n");
        printf("Ganaste mamañema y na' má' porque te mamate un guevo.\n");
    } else if (resultado == PERDISTE) {
        ImprimirTabla(); printf("\n");
        printf("Ya sabía yo, perdiste maldita basura.\n");
    } else if (resultado == EMPATE) {
        ImprimirTabla(); printf("\n");
        printf("Te salvaste porque no soy maldaoso.\n");
    }

    if (resultado != SINRESULTADO) {
        printf("[Pulsa una tecla]"); pausa(); printf("\n");
        return 1;
    }

    return 0;
}

void Iniciar() {
    char eleccion = 0;
    unsigned char mamanema = 0;

    limpiar();
    EquisCeroLogo();

    while (1) {
        printf("Mi loco elija la dificultad:\n");
        printf("1) Izi pisi\n");
        printf("2) Masomenos\n");
        printf("3) Bobo\n");
        printf(": "); eleccion = getchar();

        if (getchar() != '\n') {
            while (getchar() != '\n');

            printf(
                "\nPero mamañema se te está pidiendo un número del 1 al 3. E' "
                "má' toma dificultad 3 por azaroso.\n"
            );
            printf("[Pulsa una tecla]"); pausa();

            mamanema = 1;
            dificultad = 3;

        } else if ((eleccion >= '1') && (eleccion <= '3')) {
            dificultad = eleccion - '1' + 1;

        } else {
            printf("\nPero anormal... Pon un número, siempre de idiota.\n");
            printf("[Pulsa una tecla]"); pausa();
            printf("\n\nAhora sí elige bien coño.\n\n");
            continue;
        }

        break;
    }

    printf("\n");

    if (dificultad == 1) {
        printf("Ya yo sabía que tú era' pájaro, dique \"izi pisi\".\n");
    } else if (dificultad == 2) {
        printf("Ahí 'tá bien, una dificultad chilling.\n");
    } else if ((dificultad == 3) && !mamanema) {
        printf("Oh, me salió rabia, tú va ve' que te va llevar el diablo.\n");
    }

    if (!mamanema) {
        printf("[Pulsa una tecla]"); pausa();
        printf("\n");
    }

    while (1) {
        LimpiarTabla();

        for (char i=0;i<5;i++) {
            if (i == 0) {
                printf("\nDale tú primero.\n");
                printf("[Pulsa una tecla]"); pausa();
                printf("\n\n");
            }

            // Turno del jugador.
            ImprimirTabla(); printf("\n");
            ElegirCasilla(); printf("\n");

            if (i > 1) {if (Comprobar()) {break;}}

            ImprimirTabla();

            // Turno de la PC.
            printf("\nVoy yo.\n");
            printf("[Pulsa una tecla]"); pausa();
            printf("\n\n");

            TurnoDeLaPC(tabla, dificultad);

            if (i > 1) {if (Comprobar()) {break;}}
        }

        printf("\n");
        printf("Klk, vamo' otra mano pa' que pierda.\n");
        printf("1) Claro.\n");
        printf("2) Soy muy hembra.\n");
        printf(": "); eleccion = getchar();

        printf("\n");

        if (getchar() != '\n') {
            printf("Va' pa'l diablo maricon.\n");
            break;
        } else if (eleccion == '1') {
            printf("Ahora sí te va a llevar el diablo, mmg.\n");
        } else if (eleccion == '2') {
            printf("Sa, rata.\n");
            break;
        } else {
            printf("Eeeeeh, esa mierda que tú pusiste significa sí.\n");
        }

        printf("[Pulsa una tecla]"); pausa(); printf("\n");
    }
}

void Test();

int main() {
#if (defined __WIN32__) || (defined _WIN32)
    SetConsoleOutputCP(65001);
#endif

#ifdef TESTEAR
    Test();
#else
    Iniciar();
#endif

    return 0;
}

void Test() {
    printf("Test 1:\n");
    LimpiarTabla();
    tabla[0] = tabla[1] = O_CHAR;
    ImprimirTabla(); printf("\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); printf("\n");

    printf("Test 2:\n");
    LimpiarTabla();
    tabla[1] = tabla[2] = O_CHAR;
    ImprimirTabla(); printf("\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); printf("\n");

    printf("Test 3:\n");
    LimpiarTabla();
    tabla[0] = tabla[3] = O_CHAR;
    ImprimirTabla(); printf("\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); printf("\n");

    printf("Test 4:\n");
    LimpiarTabla();
    tabla[3] = tabla[6] = O_CHAR;
    ImprimirTabla(); printf("\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); printf("\n");

    printf("Test 5:\n");
    LimpiarTabla();
    tabla[0] = tabla[4] = O_CHAR;
    ImprimirTabla(); printf("\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); printf("\n");

    printf("Test 6:\n");
    LimpiarTabla();
    tabla[2] = tabla[4] = O_CHAR;
    ImprimirTabla(); printf("\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); printf("\n");

    printf("Test 7:\n");
    LimpiarTabla();
    tabla[0] = tabla[2] = O_CHAR;
    ImprimirTabla(); printf("\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); printf("\n");

    printf("Test 8:\n");
    LimpiarTabla();
    tabla[0] = tabla[6] = O_CHAR;
    ImprimirTabla(); printf("\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); printf("\n");

    printf("Test 9:\n");
    LimpiarTabla();
    tabla[0] = tabla[8] = O_CHAR;
    ImprimirTabla(); printf("\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); printf("\n");

    printf("Test 10:\n");
    LimpiarTabla();
    tabla[8] = tabla[0] = X_CHAR;
    tabla[4] = O_CHAR;
    ImprimirTabla(); printf("\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); printf("\n");

    printf("Test 11:\n");
    LimpiarTabla();
    tabla[2] = tabla[6] = X_CHAR;
    tabla[4] = O_CHAR;
    ImprimirTabla(); printf("\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); printf("\n");
}
