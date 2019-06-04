#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main()
{
    unsigned order, row = 0, col = 0;
    short choice;
    Matrix mat;

    do{
        printf("Inserisci l'ordine della matrice da trattare: ");
        scanf("%d", &order);
    }while(!order);
    
    mat = create_matrix(order);
    if(!mat)
    {
        fprintf(stderr, "Errore durante la creazione della matrice\n");
        return 1;
    }

    do{
        printf("1. Matrice di Hilbert\n2. Matrice di Vandermonde(-1,1)\n");
        scanf("%hd", &choice);
    }while(choice < 1 || choice > 2);

    switch (choice)
    {
    case 1:
        fill_hilbert(mat, order);
        break;
    case 2:
        fill_vandermonde_ab(mat, order, -1.l, 1.l);
        break;
    default:
        break;
    }

    printf("Generata matrice di ordine %d.\n", order);

    print_matrix(mat, order);
    print_matrix_spiral(mat, order);

    destroy_matrix(&mat,order);
    return 0;
}