#ifndef SCACCHIERA_H
#define SCACCHIERA_H

typedef unsigned short Riga[4];
typedef Riga Scacchiera[4];

void init_scacchiera(Scacchiera in);
void print_scacchiera(Scacchiera in);
unsigned short get_moves(Scacchiera in, unsigned short *marray);
void move_piece(Scacchiera in, unsigned short piece);
int verify(Scacchiera in);

#endif