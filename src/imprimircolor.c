#if (defined __WIN32__) || (defined _WIN32)
#include <windows.h>
#else
#include <wchar.h>
#endif

int colores = -1;

void ObtenerColoresOriginales() {
#if (defined __WIN32__) || (defined _WIN32)
    CONSOLE_SCREEN_BUFFER_INFO temp;

    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &temp)) {
        colores = 0 | 7; // Fondo blanco y texto negro.
    } else {
        colores = temp.wAttributes;
    }
#else
    colores = 0;
#endif
}

#if (defined __WIN32__) || (defined _WIN32)
void EstablecerColores(int color) {
#else
void EstablecerColores(char *color) {
#endif
    if (colores == -1) {
        ObtenerColoresOriginales();
    }

#if (defined __WIN32__) || (defined _WIN32)
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        color
    );
#else
    wprintf(L"\033[%sm", color);
#endif
}

void RestablecerColores() {
#if (defined __WIN32__) || (defined _WIN32)
    if (colores != -1) {
        EstablecerColores(colores);
    }
#else
    wprintf(L"\033[0m");
#endif
}
