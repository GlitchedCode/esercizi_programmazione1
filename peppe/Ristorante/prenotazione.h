#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H
#define LUN 100
#include "calendario.h"

typedef enum pasto{ristorante,pizzeria} PASTO;

struct contatto
{
    char nome[LUN];
    char cognome[LUN];
    long n_cell;
};
typedef struct contatto CONTATTO;


struct prenotazione
{
    unsigned int giorno;
    unsigned int ora;
    unsigned int n_partecipanti;
    PASTO tipo_pasto;
    CONTATTO dati_contatto;
    int sala; //aggiungi 1 durante la stampa su terminale
    struct prenotazione *next;
};
typedef struct prenotazione PRENOTAZIONE;

typedef PRENOTAZIONE* LISTA_prenot;

// Inizializza la lista delle prenotazioni
void iniz_prenot(LISTA_prenot*);
// Crea una nuova prenotazione
PRENOTAZIONE* nuova_prenotazione();
// Inserisce la prenotazione nella lista concatenata
void inserisci_prenotazione(LISTA_prenot*, PRENOTAZIONE*, MESE*);
// Stampa i tavoli disponibili
void tavoli_disponibili(MESE*);
// Queste funzioni salvano e leggono da file le prenotazioni
// Restituiscono NULL se sono riscontrati errori
LISTA_prenot importa_prenot(MESE*);
int salva_su_file(LISTA_prenot);
// Libera la memoria allocata per la lista di prenotazioni
void distruggi_prenotazioni(LISTA_prenot);

#endif