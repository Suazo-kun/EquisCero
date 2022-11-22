@ECHO off

set RUTA_ACTUAL=%cd%
set BAT_RUTA=%~dp0

IF "%~1" == "--testear" (
    set testeararg=-DTESTEAR
)

cd %BAT_RUTA%

windres -i src\equiscero.rc -o equiscero.res --output-format=coff
gcc -O2 -Wall src\main.c src\equiscero.c equiscero.res -o "%RUTA_ACTUAL%\EquisCero.exe" %testeararg%

del equiscero.res

cd %RUTA_ACTUAL%

set testeararg=
set BAT_RUTA=
set RUTA_ACTUAL=
