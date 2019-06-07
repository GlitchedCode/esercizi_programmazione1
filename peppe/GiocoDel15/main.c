#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "scacchiera.h"

int main()
{
    srand(time(NULL));
    Scacchiera scacchiera;
    unsigned short marray[4], move_count, c;
    int result;

    do
    {
        init_scacchiera(scacchiera);
    }while(verify(scacchiera));

    do
    {
        print_scacchiera(scacchiera);
        move_count = get_moves(scacchiera, marray);
        printf("Mosse disponibili: ");
        for(c = 0; c < move_count; c++)
        {
            printf("%hd ", marray[c]);
        }
        printf("\n");

        printf("Inserisci il pezzo da muovere: ");
        scanf("%hd", &c);
        fflush(stdin);
        if(!c) break;
        move_piece(scacchiera, c);
    }while(!(result = verify(scacchiera)));
    
    if(result) printf("Hai vinto!\n");
    return 0;
}