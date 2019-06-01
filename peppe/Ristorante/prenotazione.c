#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prenotazione.h"
#include "calendario.h"

PRENOTAZIONE* nuova_prenotazione(){
    char s_pasto[20];
    PRENOTAZIONE *prenotazione = (PRENOTAZIONE*)malloc(sizeof(PRENOTAZIONE)); 
    printf("Inserire nome: ");
    scanf("\n%[^\n]", prenotazione->dati_contatto.nome);
    printf("Inserire cognome: ");
    scanf("\n%[^\n]", prenotazione->dati_contatto.cognome);
    printf("Inserire numero di telefono: ");
    scanf("%ld", &(prenotazione->dati_contatto.n_cell));

    printf("Inserire giorno: ");
    scanf("%d", &(prenotazione->giorno));
    printf("Inserire ora: ");
    scanf("%d", &(prenotazione->ora));
    printf("Inserire numero partecipanti: ");
    scanf("%d", &(prenotazione->n_partecipanti));
    printf("Inserire tipo pasto: ");
    scanf("\n%[^\n]", s_pasto);
    if (strstr(s_pasto, "pizza") == 0){
        prenotazione->tipo_pasto = pizzeria;
    }
    else{
        prenotazione->tipo_pasto = ristorante;
    }
    prenotazione->sala =-1;
    prenotazione->next=NULL;
    return prenotazione;
}


void inserisci_prenotazione(LISTA_prenot *head_prenot, PRENOTAZIONE* temp, MESE* mese){
    if(!temp || !head_prenot || !mese) return;

    // Validità della data di prenotazione
    if(temp->ora < mese->apertura || temp->ora >= mese->chiusura || temp->giorno > mese->numero_giorni
        || !mese->giorni[temp->giorno - 1].aperto || !temp->n_partecipanti)
    {
        printf("Prenotazione invalida\n");
        free(temp);
        return;
    }

    // Controllo se esiste unsa sala disponibile
    int c;
    int sala_max;
    if(temp->tipo_pasto == ristorante) { c = 0; sala_max = NUMERO_SALE / 2; }
    else { c = NUMERO_SALE / 2; sala_max = NUMERO_SALE; }
    for(;c < sala_max && temp->sala == -1; c++)
    {
        // Calcolo il numero di tavoli necessari in quest'ora
        int totale_tavoli = mese->giorni[temp->giorno - 1].stato_ora[c][temp->ora - mese->apertura]
            + (temp->n_partecipanti / POSTI_TAVOLO);
        if(temp->n_partecipanti % POSTI_TAVOLO)
            totale_tavoli++;

        //printf("%d %d", c, totale_tavoli);

        // Se supero il limite non posso prenotare in questa sala
        if(totale_tavoli < NUMERO_TAVOLI+1)
        {
            mese->giorni[temp->giorno - 1].stato_ora[c][temp->ora - mese->apertura] = totale_tavoli;
            temp->sala = c;
        }
    }

    if(temp->sala == -1)
    {
        printf("Impossibile prenotare, tutti i tavoli sono occupati.\n");
        free(temp);
        return;
    }
    
    printf("Inserimento prenotazione in sala %d\n", temp->sala + 1);

    if (*head_prenot == NULL) // controlliamo fuori dal ciclo se head è nullo per non controllare sempre
        *head_prenot = temp;
    else do 
    {
        if(temp->ora < (*head_prenot)->ora && temp->giorno <= (*head_prenot)->giorno)
        {
            temp->next = (*head_prenot)->next; // Bisogna collegare il nuovo elemento correttamente al resto della lista
            (*head_prenot)->next = temp;
            break;
        }
        else if(!(*head_prenot)->next)
        {
            (*head_prenot)->next = temp;
            break;
        }
        else
        {
            head_prenot = &(*head_prenot)->next;
        }        
    }while (1); // inutile controllare ad ogni iterazione se head è nullo perché ce lo tiriamo fuori dal loop
}

int salva_su_file(LISTA_prenot head)
{
    FILE *pf = fopen("prenotazioni.txt","w");
    if(!pf) return 0;

    printf("Salvataggio su file... ");
    while(head)
    {
        fprintf(pf, "%2d %2d %d %1d %1d %s %s %ld\n", head->giorno, head->ora,
            head->n_partecipanti, head->tipo_pasto, head->sala,
            head->dati_contatto.nome, head->dati_contatto.cognome, head->dati_contatto.n_cell);
        head = head->next;
    }

    printf("Completato\n");
    return 1;
}

LISTA_prenot importa_prenot(MESE* mese){
    FILE *pf = fopen("prenotazioni.txt","r");
    if(!pf) return NULL;
    int giorno, ora, n_partecipanti, tipo_pasto, sala;
    PRENOTAZIONE *temp = NULL; 
    LISTA_prenot ret = NULL;
    while(fscanf(pf, "%2d %2d %d %1d %1d ", &giorno, &ora,
            &n_partecipanti, &tipo_pasto, &sala) != EOF)
    {
        temp = (PRENOTAZIONE*)malloc(sizeof(PRENOTAZIONE));
        temp->ora = ora; temp->giorno = giorno; temp->n_partecipanti = n_partecipanti;
        temp->tipo_pasto = tipo_pasto; temp->sala = sala;
        fscanf(pf, "%s %s %ld\n", temp->dati_contatto.nome, temp->dati_contatto.cognome, &temp->dati_contatto.n_cell);
        inserisci_prenotazione(&ret, temp, mese);
    }

    printf("Prenotazioni lette da hard disk.\n");
    return ret;
}

void tavoli_disponibili(MESE* mese)
{
    if(!mese) return;
    int giorno;
    int numero_ore = mese->chiusura - mese->apertura;

    do
    {
        printf("Inserire il giorno da esaminare (1-%d): ", mese->numero_giorni);
        scanf("%d", &giorno);
    }while(giorno < 1 || giorno > mese->numero_giorni);

    if(mese->giorni[giorno-1].aperto)
    {
        // ciclo delle ore
        for(int i = 0; i < numero_ore; i++)
        {
            printf("%2d %s %4d - ore %d:\n", giorno, mese_str[mese->mese - 1], 
                mese->anno,  i + mese->apertura);
            // ciclo delle sale
            for(int j = 0; j < NUMERO_SALE; j++)
            {
                printf("%d tavoli disponibili in sala %d.\n", 
                    NUMERO_TAVOLI - mese->giorni[giorno - 1].stato_ora[j][i], j + 1);
            }
            printf("\n");
        }
    }
    else
        printf("Il locale è chiuso in questa data.\n");
}

void distruggi_prenotazioni(LISTA_prenot head)
{
    PRENOTAZIONE* temp;
    while(head)
    {
        temp = head;
        free(temp);
        head = head->next;
    }
}