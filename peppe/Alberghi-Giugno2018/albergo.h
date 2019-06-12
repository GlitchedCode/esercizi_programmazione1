#ifndef ALBERGO_H
#define ALBERGO_H

#define MAX_NOME_ALBERGO 20
#define MAX_NOME_SERVIZIO 50

struct Albergo
{
    char nome[MAX_NOME_ALBERGO + 1];
    unsigned  stelle;
    unsigned  nServizi;
    char** servizi;
    struct Albergo *next;
};
typedef struct Albergo Albergo;
typedef Albergo *ListaAlberghi;

// Ciclo vitale della lista
void init_alberghi(ListaAlberghi *head);
int read_from_file(ListaAlberghi *head, char* filename);
int save_to_file(ListaAlberghi head, char* filename);
void destroy_alberghi(ListaAlberghi head);

// Controllo dei dati della lista
void print_all(ListaAlberghi head);
void insert_albergo(ListaAlberghi *head, char *nome, unsigned short stelle, 
    unsigned short nServizi, char **servizi);
void query_alberghi(ListaAlberghi head, unsigned short stelle, char *servizio);
#endif