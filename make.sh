#!/bin/sh

SH_RUTA=$(dirname "$0")

if [ $# -ne 0 ] && [ $1 = '--testear' ]; then
	testeararg=-DTESTEAR
fi

gcc -O2 -Wall $SH_RUTA/src/main.c $SH_RUTA/src/equiscero.c $SH_RUTA/src/imprimircolor.c -o EquisCero $testeararg
