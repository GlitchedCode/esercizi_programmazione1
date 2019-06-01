#ifndef CALENDARIO_H
#define CALENDARIO_H
// Usiamo queste stringhe per presentare in maniera più leggibile l'output su file 
// e su terminale
static const char* mese_str[] = {"Gennaio", "Febbraio", "Marzo", "Aprile", "Maggio", "Giugno", 
                        "Luglio", "Agosto", "Settembre", "Ottobre", "Novembre", "Dicembre"};

static const char* apertura_str[] = { "Chiuso", "Aperto" }; 

// Giorni in ogni mese
static const int mese_count[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 31, 31};

enum stato_apertura { CHIUSO, APERTO };
#define NUMERO_SALE 5
#define NUMERO_TAVOLI 15
#define POSTI_TAVOLO 6

struct giorno{
    int *stato_ora[NUMERO_SALE];
    int aperto;
};

typedef struct giorno GIORNO;

struct mese{
    // primo indice, numero della sala
    // secondo indice, numero del giorno
    GIORNO giorni[31];
    int numero_giorni;
    int anno;
    int mese;
    int apertura;
    int chiusura;
};

typedef struct mese MESE;

int calendario(MESE*);
void distruggi_calendario(MESE*);
#endif