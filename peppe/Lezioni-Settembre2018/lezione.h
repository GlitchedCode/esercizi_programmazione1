#ifndef LEZIONE_H
#define LEZIONE_H

#define CODE_MAX_LEN 10

struct lezione
{
    char code[CODE_MAX_LEN + 1];
    unsigned short day, mon, year;
    unsigned presenze;
    struct lezione *next;
};

typedef struct lezione Lezione;
typedef Lezione *ListaLezioni;

// Ciclo vitale
void init_lista_lezioni(ListaLezioni *head);
void destroy_lista_lezioni(ListaLezioni head);
// Funzioni di persistenza
int load_from_file(ListaLezioni *head, const char *filename);
int save_to_file(ListaLezioni head, const char *filename);
// Funzioni di accesso
int insert_head(ListaLezioni *head, const char *code, unsigned short day, unsigned short mon, 
    unsigned short year, unsigned presenze);
int insert_tail(ListaLezioni tail, const char *code, unsigned short day, unsigned short mon, 
    unsigned short year, unsigned presenze);
// Manipolazione dei dati
float media_presenze(ListaLezioni head, const char *code);
void print_most_unpopular(ListaLezioni head);
void print_most_popular(ListaLezioni head);
void print_courses_data(ListaLezioni head);


#endif