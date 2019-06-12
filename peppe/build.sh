#!/bin/sh
gcc Ristorante/calendario.c Ristorante/main.c Ristorante/prenotazione.c -o Ristorante/ristorante.out
gcc Istogramma/main.c Istogramma/operations.c -lm -o Istogramma/istogramma.out
gcc SpiraleMatrice/main.c SpiraleMatrice/matrix.c -lm -o SpiraleMatrice/spiraleMatrice.out
gcc Rubrica/main.c Rubrica/rubrica.c -o Rubrica/rubrica.out
gcc Alberghi-Giugno2018/main.c Alberghi-Giugno2018/albergo.c -o Alberghi-Giugno2018/alberghi-Giugno2018.out
