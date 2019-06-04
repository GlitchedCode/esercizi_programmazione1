#!/bin/sh
gcc Ristorante/calendario.c Ristorante/main.c Ristorante/prenotazione.c -o Ristorante/ristorante.out
gcc Istogramma/main.c Istogramma/operations.c -lm -o Istogramma/istogramma.out
gcc SpiraleMatrice/main.c SpiraleMatrice/matrix.c -lm -o SpiraleMatrice/spiraleMatrice.out
