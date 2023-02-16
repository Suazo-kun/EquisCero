#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <wchar.h>
#include <locale.h>
#include "equiscero.h"

#if (defined __WIN32__) || (defined _WIN32)
#include <windows.h>
#define limpiar() system("cls")
#define pausa() system("pause > nul")

#define NEGROYMORADO 0 | 5
#define NEGROYAMARILLO 0 | 6
#define NEGROYBLANCO 0 | 7
#define NEGROYROJO 0 | 4
#define NEGROYAZUL 0 | 1

#else

#define limpiar() system("clear")
#define pausa() getchar()

#define NEGROYMORADO "35;40"
#define NEGROYAMARILLO "33;40"
#define NEGROYBLANCO "37;40"
#define NEGROYROJO "31;40"
#define NEGROYAZUL "34;40"

#endif

extern void ObtenerColoresOriginales();
#if (defined __WIN32__) || (defined _WIN32)
extern void EstablecerColores(int color);
#else
extern void EstablecerColores(char *color);
#endif
extern void RestablecerColores();

void Test();

char tabla[9];
unsigned char dificultad = 0;

void EquisCeroLogo() {
    EstablecerColores(NEGROYMORADO);
    wprintf(
        L"\t\t\t""┌─         o ┌─    ┌── ┌─ ┌─┐ ┌─┐""\n"
        L"\t\t\t""├─ ┌─┐ | | | └─┐   |   ├─ ├─┘ | |""\n"
        L"\t\t\t""└─ └─┤ └─┘ |  ─┘   └── └─ | \\ └─┘""\n"
        L"\n\n\n\n\n"
    );
    RestablecerColores();
}

void LimpiarTabla() {
    for (unsigned char i=0;i<9;i++) {
        tabla[i] = LIMPIO;
    }
}

void ImprimirTabla() {
    for (unsigned char i=0;i<9;i++) {
        if (tabla[i] == X_CHAR) {
            EstablecerColores(NEGROYAZUL);
        } else if (tabla[i] == O_CHAR) {
            EstablecerColores(NEGROYROJO);
        } else {
            EstablecerColores(NEGROYBLANCO);
        }

        wprintf(L" %c ", tabla[i]);

        EstablecerColores(NEGROYBLANCO);

        if ((i == 2) || (i == 5)) {
            wprintf(L"\n───┼───┼───\n");
        } else if (i < 8) {
            wprintf(L"|");
        } else {
            wprintf(L"\n");
        }
    }

    RestablecerColores();
}

void PulsaUnaTecla() {
    EstablecerColores(NEGROYBLANCO);
    wprintf(L"[Pulsa una tecla]"); pausa();
}

void ElegirCasilla() {
    unsigned char casilla;

    EstablecerColores(NEGROYBLANCO);
    wprintf(L"NOTA: Ponga un número del 1 al 9 para elegir su casilla.\n");

    while (1) {
        wprintf(L"Casilla: "); casilla = getchar();
        EstablecerColores(NEGROYAMARILLO);

        if (getchar() != '\n') {
            while (getchar() != '\n');
            wprintf(L"\nPero mamañema se te está pidiendo un número del 1 al 9.\n");

        } else if ((casilla < '1') || (casilla > '9')) {
            wprintf(L"\nPero ANORMAL, pon un número del 1 al 9, singa tu madre.\n");

        } else if (tabla[casilla - '1'] != LIMPIO) {
            wprintf(
                L"\nMi vida, mi amor, mi todo... Esa maldita casilla ya está "
                L"elegida, MAMAGUEVAZO\n"
            );

        } else {
            tabla[casilla - '1'] = X_CHAR;
            break;
        }

        PulsaUnaTecla(); wprintf(L"\n\n");
        EstablecerColores(NEGROYAMARILLO);
        wprintf(L"Ahora sí hazlo bien.\n\n");
        EstablecerColores(NEGROYBLANCO);
    }

    RestablecerColores();
}

unsigned char Comprobar() {
    unsigned char resultado = EvaluarTabla(tabla);

    if (resultado == GANASTE) {
        ImprimirTabla(); wprintf(L"\n");
        EstablecerColores(NEGROYAMARILLO);
        wprintf(L"Ganaste mamañema y na' má' porque te mamate un guevo.\n");
    } else if (resultado == PERDISTE) {
        ImprimirTabla(); wprintf(L"\n");
        EstablecerColores(NEGROYAMARILLO);
        wprintf(L"Ya sabía yo, perdiste maldita basura.\n");
    } else if (resultado == EMPATE) {
        ImprimirTabla(); wprintf(L"\n");
        EstablecerColores(NEGROYAMARILLO);
        wprintf(L"Te salvaste porque no soy maldaoso.\n");
    }

    if (resultado != SINRESULTADO) {
        PulsaUnaTecla(); wprintf(L"\n");
        RestablecerColores();

        return 1;
    }

    RestablecerColores();
    return 0;
}

void Iniciar() {
    char eleccion = 0;
    unsigned char mamanema = 0;

    limpiar();
    EquisCeroLogo();

    while (1) {
        EstablecerColores(NEGROYBLANCO);

        wprintf(L"Mi loco elija la dificultad:\n");
        wprintf(L"1) Izi pisi\n");
        wprintf(L"2) Masomenos\n");
        wprintf(L"3) Bobo\n");
        wprintf(L": "); eleccion = getchar();

        EstablecerColores(NEGROYAMARILLO);

        if (getchar() != '\n') {
            while (getchar() != '\n');

            wprintf(
                L"\nPero mamañema se te está pidiendo un número del 1 al 3. E' "
                L"má' toma dificultad 3 por azaroso.\n"
            );

            PulsaUnaTecla();

            mamanema = 1;
            dificultad = 3;

        } else if ((eleccion >= '1') && (eleccion <= '3')) {
            dificultad = eleccion - '1' + 1;

        } else {
            wprintf(L"\nPero anormal... Pon un número, siempre de idiota.\n");
            PulsaUnaTecla();
            EstablecerColores(NEGROYAMARILLO);
            wprintf(L"\n\nAhora sí elige bien coño.\n\n");
            continue;
        }

        break;
    }

    wprintf(L"\n");

    if (dificultad == 1) {
        wprintf(L"Ya yo sabía que tú era' pájaro, dique \"izi pisi\".\n");
    } else if (dificultad == 2) {
        wprintf(L"Ahí 'tá bien, una dificultad chilling.\n");
    } else if ((dificultad == 3) && !mamanema) {
        wprintf(L"Oh, me salió rabia, tú va ve' que te va llevar el diablo.\n");
    }

    if (!mamanema) {
        PulsaUnaTecla();
        wprintf(L"\n");
    }

    while (1) {
        LimpiarTabla();

        for (char i=0;i<5;i++) {
            EstablecerColores(NEGROYAMARILLO);

            if (i == 0) {
                wprintf(L"\nDale tú primero.\n");
                PulsaUnaTecla();
                wprintf(L"\n\n");
            }

            // Turno del jugador.
            ImprimirTabla(); wprintf(L"\n");
            ElegirCasilla(); wprintf(L"\n");

            if (i > 1) {if (Comprobar()) {break;}}

            ImprimirTabla();

            // Turno de la PC.
            EstablecerColores(NEGROYAMARILLO);
            wprintf(L"\nVoy yo.\n");
            PulsaUnaTecla();
            wprintf(L"\n\n");

            TurnoDeLaPC(tabla, dificultad);

            if (i > 1) {if (Comprobar()) {break;}}
        }

        EstablecerColores(NEGROYBLANCO);
        wprintf(L"\n");
        wprintf(L"Klk, vamo' otra mano pa' que pierda.\n");
        wprintf(L"1) Claro.\n");
        wprintf(L"2) Soy muy hembra.\n");
        wprintf(L": "); eleccion = getchar();

        wprintf(L"\n");
        EstablecerColores(NEGROYAMARILLO);

        if (getchar() != '\n') {
            wprintf(L"Va' pa'l diablo maricon.\n");
            break;
        } else if (eleccion == '1') {
            wprintf(L"Ahora sí te va a llevar el diablo, mmg.\n");
        } else if (eleccion == '2') {
            wprintf(L"Sa, rata.\n");
            break;
        } else {
            wprintf(L"Eeeeeh, esa mierda que tú pusiste significa sí.\n");
        }

        PulsaUnaTecla();
        wprintf(L"\n");
    }

    RestablecerColores();
}

int main() {
    ObtenerColoresOriginales();

#if (defined __WIN32__) || (defined _WIN32)
    _setmode(_fileno(stdout), _O_U8TEXT);
#else
    setlocale(LC_CTYPE, "es_DO.UTF-8");
#endif

#ifdef TESTEAR
    Test();
#else
    Iniciar();
#endif

    return 0;
}

void Test() {
    wprintf(L"Test 1:\n");
    LimpiarTabla();
    tabla[0] = tabla[1] = O_CHAR;
    ImprimirTabla(); wprintf(L"\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); wprintf(L"\n");

    wprintf(L"Test 2:\n");
    LimpiarTabla();
    tabla[1] = tabla[2] = O_CHAR;
    ImprimirTabla(); wprintf(L"\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); wprintf(L"\n");

    wprintf(L"Test 3:\n");
    LimpiarTabla();
    tabla[0] = tabla[3] = O_CHAR;
    ImprimirTabla(); wprintf(L"\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); wprintf(L"\n");

    wprintf(L"Test 4:\n");
    LimpiarTabla();
    tabla[3] = tabla[6] = O_CHAR;
    ImprimirTabla(); wprintf(L"\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); wprintf(L"\n");

    wprintf(L"Test 5:\n");
    LimpiarTabla();
    tabla[0] = tabla[4] = O_CHAR;
    ImprimirTabla(); wprintf(L"\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); wprintf(L"\n");

    wprintf(L"Test 6:\n");
    LimpiarTabla();
    tabla[2] = tabla[4] = O_CHAR;
    ImprimirTabla(); wprintf(L"\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); wprintf(L"\n");

    wprintf(L"Test 7:\n");
    LimpiarTabla();
    tabla[0] = tabla[2] = O_CHAR;
    ImprimirTabla(); wprintf(L"\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); wprintf(L"\n");

    wprintf(L"Test 8:\n");
    LimpiarTabla();
    tabla[0] = tabla[6] = O_CHAR;
    ImprimirTabla(); wprintf(L"\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); wprintf(L"\n");

    wprintf(L"Test 9:\n");
    LimpiarTabla();
    tabla[0] = tabla[8] = O_CHAR;
    ImprimirTabla(); wprintf(L"\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); wprintf(L"\n");

    wprintf(L"Test 10:\n");
    LimpiarTabla();
    tabla[8] = tabla[0] = X_CHAR;
    tabla[4] = O_CHAR;
    ImprimirTabla(); wprintf(L"\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); wprintf(L"\n");

    wprintf(L"Test 11:\n");
    LimpiarTabla();
    tabla[2] = tabla[6] = X_CHAR;
    tabla[4] = O_CHAR;
    ImprimirTabla(); wprintf(L"\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); wprintf(L"\n");

    wprintf(L"Test 12:\n");
    LimpiarTabla();
    tabla[1] = O_CHAR;
    tabla[2] = tabla[7] = X_CHAR;
    ImprimirTabla(); wprintf(L"\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); wprintf(L"\n");

    wprintf(L"Test 13:\n");
    LimpiarTabla();
    tabla[1] = O_CHAR;
    tabla[4] = tabla[7] = X_CHAR;
    ImprimirTabla(); wprintf(L"\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); wprintf(L"\n");

    wprintf(L"Test 14:\n");
    LimpiarTabla();
    tabla[2] = O_CHAR;
    tabla[4] = tabla[6] = X_CHAR;
    ImprimirTabla(); wprintf(L"\n");
    TurnoDeLaPC(tabla, 3);
    ImprimirTabla(); wprintf(L"\n");
}
