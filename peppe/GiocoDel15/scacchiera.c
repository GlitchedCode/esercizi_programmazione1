#include "scacchiera.h"
#include <stdlib.h>
#include <stdio.h>

void init_scacchiera(Scacchiera in)
{
    unsigned short n, i, j;
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
            in[i][j] = 0;
    for(n = 1; n < 16;)
    {
        i = rand() % 4;
        j = rand() % 4;
        if(!in[i][j])
        {
            in[i][j] = n;
            n++;
        }
    }
}

void print_scacchiera(Scacchiera in)
{
    unsigned short i, j;
    Riga *current;
    printf("-");
        for(j = 0; j < 4; j++)
            printf("---");
        printf("\n");
    for(i = 0; i < 4; i++)
    {
        current = &(in[i]);
        printf("|");
        for(j = 0; j < 4; j++)
        {
            if((*current)[j])
                printf("%2hd|", (*current)[j]);
            else
                printf("  |");
        }
        printf("\n-");
        for(j = 0; j < 4; j++)
            printf("---");
        printf("\n");        
    }
}

unsigned short get_moves(Scacchiera in, unsigned short *marray)
{
    unsigned short empty_row, empty_col, found = 0, ret = 0;
    for(empty_row = 0; empty_row < 4; empty_row++)
    {
        for(empty_col = 0; empty_col < 4; empty_col++)
            if(in[empty_row][empty_col] == 0)
            {
                found = 1;
                break;
            }
        if(found) break;
    }
    
    
    // Controllo che le celle adiacenti siano contenute nella scacchiera
    if(empty_row > 0)
    {
        marray[ret] = in[empty_row - 1][empty_col];
        ret = ret + 1;
    }
    if(empty_row < 3)
    {
        marray[ret] = in[empty_row + 1][empty_col];
        ret = ret + 1;
    }
    if(empty_col > 0)
    {
        marray[ret] = in[empty_row][empty_col - 1];
        ret = ret + 1;
    }
    if(empty_col < 3)
    {
        marray[ret] = in[empty_row][empty_col + 1];
        ret = ret + 1;
    }
    return ret;
}

void move_piece(Scacchiera in, unsigned short piece)
{
    unsigned short piece_row, piece_col, found = 0;
    if(!piece || piece > 15)
    {
        fprintf(stderr, "Numero invalido\n");
        return;
    }
    for(piece_row = 0; piece_row < 4 && !found; piece_row++)
    {
        for(piece_col = 0; piece_col < 4; piece_col++)
            if(in[piece_row][piece_col] == piece)
            {
                found = 1;
                break;
            }
        if(found) break;
    }
    // Controllo che tra i pezzi adiacenti sia presente lo spazio vuoto
    if(piece_row > 0)
    {
        if(!in[piece_row - 1][piece_col])
        {
            in[piece_row - 1][piece_col] = piece;
            in[piece_row][piece_col] = 0;
            return;
        }
    }
    if(piece_row < 3)
    {
        if(!in[piece_row + 1][piece_col])
        {
            in[piece_row + 1][piece_col] = piece;
            in[piece_row][piece_col] = 0;
            return;
        }
    }
    if(piece_col > 0)
    {
        if(!in[piece_row][piece_col - 1])
        {
            in[piece_row][piece_col - 1] = piece;
            in[piece_row][piece_col] = 0;
            return;
        }
    }
    if(piece_col < 3)
    {
        if(!in[piece_row][piece_col + 1])
        {
            in[piece_row][piece_col + 1] = piece;
            in[piece_row][piece_col] = 0;
            return;
        }
    }

    printf("Impossibile muovere questo pezzo.\n");
}

int verify(Scacchiera in)
{
    unsigned short current_count = 0;
    unsigned row, col;

    for(row = 0; row < 4; row++)
    {
        for(col = 0; col < 4; col++)
        {
            if((in[row][col] - current_count) >= 0)
                current_count++;
            else
                return 0;
        }
    }

    return 1;
}