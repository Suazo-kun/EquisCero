#if (defined __WIN32__) || (defined _WIN32)
#include <windows.h>
//#else
#endif

int colores = -1;

#if (defined __WIN32__) || (defined _WIN32)
void ObtenerColoresOriginales() {
    CONSOLE_SCREEN_BUFFER_INFO temp;

    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &temp)) {
        colores = 0 | 7; // Fondo blanco y texto negro.
    } else {
        colores = temp.wAttributes;
    }
}
//#else
#endif

void EstablecerColores(int color) {
    if (colores == -1) {
        ObtenerColoresOriginales();
    }

    #if (defined __WIN32__) || (defined _WIN32)
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        color
    );
    //#else
    #endif
}

void RestablecerColores() {
    if (colores != -1) {
        EstablecerColores(colores);
    }
}
