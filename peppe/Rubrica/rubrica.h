#ifndef RUBRICA_H
#define RUBRICA_H

#define MAX_CONTATTI 100
#define MAX_NAMELEN 40
#define MAX_NUMLEN 20

#define EXP(M) #M
#define MACROSTR(M) EXP(M)

enum EXACT { FUZZY, EXACT };

struct Contatto
{
    char    nome[MAX_NAMELEN+1];
    char    numero[MAX_NUMLEN+1];
};
typedef struct Contatto Contatto;

struct Rubrica
{
    Contatto    contatti[MAX_CONTATTI];
    unsigned    count;
};
typedef struct Rubrica Rubrica;

// Controllo dei dati della rubrica
void rubrica_init(Rubrica *r);
int read_from_file(Rubrica *r, const char *filename);
int save_to_file(Rubrica *r, const char *filename);
// Operazioni sui dati
int insert(Rubrica *r, const char *nome, const char* numero);
void print(Rubrica *r);
// il parametro exact appartiene all'enum EXACT e determina se la ricerca deve essere
// stringente o meno
void search(Rubrica *r, const char *query, int exact);

#endif