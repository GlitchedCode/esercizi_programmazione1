#ifndef TRENO_H
#define TRENO_H

#define MAX_CITY_NAME_LEN 80
#define FILE_PER_CARROZZA 20

typedef int Carrozza[FILE_PER_CARROZZA][4];

enum TipoPosto { QUALUNQUE, CORRIDOIO, FINESTRINO };
typedef enum TipoPosto TipoPosto;

struct Treno
{
    char *partenza;
    char *destinazione;
    Carrozza *carrozze;
    unsigned int oraPartenza;
    unsigned int minPartenza;
    unsigned int oraArrivo;
    unsigned int minArrivo;
    unsigned int nCarrozze;
    struct Treno *next;
};

typedef struct Treno Treno;
typedef Treno *ListaTreni;

// Controllo allocazione
void init_carrozza(Carrozza *vec, unsigned int nCarrozze);
void init_treni(ListaTreni *head);
int insert_treno_head(ListaTreni *head, char *partenza, char *destinazione, unsigned int nCarrozze,
    unsigned int oraPartenza, unsigned int minPartenza, unsigned int oraArrivo, unsigned int minArrivo);
int load_from_file(ListaTreni *head, const char *filename);
void destroy_lista_treni(ListaTreni head);
// Controllo dei dati
unsigned stampa_carrozza(Carrozza *c);
void stampa_posti_treno(Treno *t);
Treno *seleziona_treno(ListaTreni head, char *partenza, char *destinazione);
unsigned prenota_posto(Treno *t, TipoPosto tipo, int *row, int *seat);
void libera_posto(Treno *t, unsigned int nCarrozza, int row, int seat);

#endif