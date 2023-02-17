@ECHO off

set RUTA_ACTUAL=%cd%
set BAT_RUTA=%~dp0

IF "%~1" == "--testear" (
    set testeararg=-DTESTEAR
)

IF exist build (
    rmdir build /S /Q
    mkdir build
) ELSE (
    mkdir build
)

cd %BAT_RUTA%

windres -i src\equiscero.rc -o equiscero.res --output-format=coff
gcc -O2 -Wall src\main.c src\equiscero.c src\imprimircolor.c equiscero.res -o "%RUTA_ACTUAL%\build\EquisCero.exe" %testeararg%

del equiscero.res

cd %RUTA_ACTUAL%

set testeararg=
set BAT_RUTA=
set RUTA_ACTUAL=
