#ifndef SALA_H
#define SALA_H
struct sala
{
    char nome;
    char tipo[15];
    int n_tavoli;
    int n_posti;
};

typedef struct sala SALA;

void iniz_sala(SALA*);
void lista_dei_tavoli_ancora_disponibili();
#endif