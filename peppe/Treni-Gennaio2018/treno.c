#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treno.h"

// Controllo allocazione
void init_carrozza(Carrozza *vec, unsigned int nCarrozze)
{
    if(vec && nCarrozze) memset(vec, 0, sizeof(int) * FILE_PER_CARROZZA * 4 * nCarrozze);
}

void init_treni(ListaTreni *head)
{
    if(head) *head = NULL;
}

int insert_treno_head(ListaTreni *head, char *partenza, char *destinazione, unsigned int nCarrozze,
    unsigned int oraPartenza, unsigned int minPartenza, unsigned int oraArrivo, unsigned int minArrivo)
{
    ListaTreni temp;
    if(!head || !strlen(partenza) || !strlen(destinazione) || !nCarrozze || oraPartenza > 23
        || minPartenza > 59 || oraArrivo > 23 || minArrivo > 59) 
    {
        fprintf(stderr, "Parametri invalidi passati ad insert_treno_head\n");
        return 0;        
    }
    
    if(!*head)
    {
        *head = (ListaTreni)malloc(sizeof(Treno));
        if(!*head)
        {
            fprintf(stderr, "Errore di allocazione\n");
            return 0;
        }
        (*head)->next = NULL;
        temp = *head;
    }
    else
    {
        temp = (ListaTreni)malloc(sizeof(Treno));
        if(!temp)
        {
            fprintf(stderr, "Errore di allocazione\n");
            return 0;
        }
        temp->next = *head;
        *head = temp;
    }
    
    temp->nCarrozze = nCarrozze;
    temp->partenza = (char*)malloc(sizeof(char) * (MAX_CITY_NAME_LEN + 1));
    temp->destinazione = (char*)malloc(sizeof(char) * (MAX_CITY_NAME_LEN + 1));
    temp->carrozze = (Carrozza*)malloc(sizeof(Carrozza) * nCarrozze);
    temp->oraArrivo = oraArrivo;
    temp->oraPartenza = oraPartenza;
    temp->minArrivo = minArrivo;
    temp->minPartenza = minPartenza;

    if(!temp->partenza || !temp->destinazione || !temp->carrozze)
    {
        fprintf(stderr, "Errore di allocazione\n");
        *head = temp->next;
        free(temp->partenza);
        free(temp->destinazione);
        free(temp->carrozze);
        free(temp);
        return 0;
    }

    strncpy(temp->partenza, partenza, MAX_CITY_NAME_LEN);
    strncpy(temp->destinazione, destinazione, MAX_CITY_NAME_LEN);
    init_carrozza(temp->carrozze, nCarrozze);

    return 1;
}

int load_from_file(ListaTreni *head, const char *filename)
{
    char partenza[MAX_CITY_NAME_LEN + 1], destinazione[MAX_CITY_NAME_LEN + 1];
    unsigned int nCarrozze;
    unsigned int oraPartenza, minPartenza, oraArrivo, minArrivo;
    FILE *handle;
    
    if(!head || !filename)
    {
        fprintf(stderr, "Parametri invalidi passati a load_from_file.\n");
        return 0;
    }

    handle = fopen(filename, "r");
    if(!handle)
    {
        fprintf(stderr, "Impossibile aprire il file %s.\n", filename);
        return 0;
    }

    while (fscanf(handle, "%s\n%s\n%2u:%2u\n%2u:%2u\n%u\n\n", partenza, destinazione,
        &oraPartenza, &minPartenza, &oraArrivo, &minArrivo, &nCarrozze) != EOF)
    {
        if(!insert_treno_head(head, partenza, destinazione, nCarrozze, 
            oraPartenza, minPartenza, oraArrivo, minArrivo))
        {
            destroy_lista_treni(*head);
            return 0;
        }
    }    

    return 1;
}

void destroy_lista_treni(ListaTreni head)
{
    ListaTreni temp;
    while (head)
    {
        free(head->partenza);
        free(head->destinazione);
        free(head->carrozze);
        temp = head->next;
        free(head);
        head = temp;
    }
    
}

// Controllo dei dati
unsigned stampa_carrozza(Carrozza *c)
{
    unsigned postiLiberi = 0;
    for(unsigned row = 0; row < FILE_PER_CARROZZA; row++)
    {
        printf("%2u", row + 1);
        for(unsigned short seat = 0; seat < 4; seat++)
        {
            if(!(seat % 2)) printf(" ");
            if((*c)[row][seat]) printf("X");
            else 
            {
                printf("O");
                postiLiberi++;
            }
        }
        printf("\n");
    }

    printf("Posti liberi: %d\n\n", postiLiberi);
    return postiLiberi;
}

void stampa_posti_treno(Treno *t)
{
    unsigned postiLiberi = 0;
    for(unsigned c = 0; c < t->nCarrozze; c++)
    {
        postiLiberi += stampa_carrozza(t->carrozze + c);
    }
    printf("Leggenda:\nO. Posto libero\nX. Posto occupato\n\nPosti liberi totali: %d\n", postiLiberi);
}

unsigned prenota_posto(Treno *t, TipoPosto tipo, int *_row, int *_seat)
{
    unsigned id = (unsigned)rand() + 1;
    unsigned int row, seat, c;
    unsigned temp;
    Carrozza *tcarrozza;

    if(!t || !_row || !_seat)
    {
        fprintf(stderr, "Parametri invalidi passati a prenota_posto.\n");
        return 0;
    }

    *_row = *_seat = -1;

    for(c = 0; c < t->nCarrozze; c++)
    {
        tcarrozza = t->carrozze + c;
        for(row = 0; row < FILE_PER_CARROZZA; row++)
        {
            for(seat = 0; seat < 4; seat++)
            {

                temp = (*tcarrozza)[row][seat];
                if(temp) continue;

                switch (tipo)
                {
                case CORRIDOIO:
                    if(seat > 0 && seat < 3)
                    {
                        *_row = row + 1;
                        *_seat = seat + 1;
                        break;
                    }
                    else continue;
                case FINESTRINO:
                    if(seat < 1 || seat > 2)
                    {
                        *_row = row + 1;
                        *_seat = seat + 1;
                        break;
                    }
                    else continue;
                default:
                    *_row = row + 1;
                    *_seat = seat + 1;
                    break;
                }
                if(row != -1) break;
            }
            if(row != -1) break;
        }
        if(row != -1) break;
    }

    if(row == -1)
    {
        fprintf(stderr, "Siamo spiacenti, non è stato possibile trovare un posto con la configurazione richiesta.\n");
        return 0;
    }

    (*tcarrozza)[row][seat] = id;

    printf("Carrozza %d, Fila %d, Posto %d\n", c + 1, row + 1, seat + 1);
    return id;
}

void libera_posto(Treno *t, unsigned int nCarrozza, int row, int seat)
{
    if(!t)
    {
        fprintf(stderr, "Parametri invalidi passati a libera_posto.\n");
        return;
    }

    if( nCarrozza < 1 || nCarrozza > t->nCarrozze || row < 1 || row > FILE_PER_CARROZZA
         || seat < 1 || seat > 4)
    {
        fprintf(stderr, "Parametri invalidi passati a libera_posto.\n");
        return;
    }

    t->carrozze[nCarrozza - 1][row - 1][seat - 1] = 0;
}

typedef struct results_list
{
    Treno *treno;
    struct results_list *next;
} results_list;

void insert_result(results_list **head, Treno *t)
{
    results_list *temp;
    if(!head) return;
    temp = (results_list*)malloc(sizeof(results_list));
    temp->next = *head;
    *head = temp;
    
    temp->treno = t;
}

void destroy_result_list(results_list *head)
{
    results_list *temp;
    while(head)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void print_results(results_list *head)
{
    for(unsigned i = 1; head != NULL; i++, head = head->next)
        printf("-- %d --\nPartenza: %s\nDestinazione: %s\n%2d:%2d - %2d:%2d\n\n", i,
            head->treno->partenza, head->treno->destinazione, head->treno->oraPartenza,
            head->treno->minPartenza, head->treno->oraArrivo, head->treno->minArrivo);
}

Treno *seleziona_treno(ListaTreni head, char *partenza, char *destinazione)
{
    results_list *rhead = NULL, *rselect;
    Treno *ret;
    unsigned count = 0, choice;

    while(head)
    {
        if(!strncmp(head->partenza, partenza, MAX_CITY_NAME_LEN) && 
            !strncmp(head->destinazione, destinazione, MAX_CITY_NAME_LEN))
            {insert_result(&rhead, head); count++;}
        head = head->next;
    }

    if(!count)
    {
        fprintf(stderr, "Siamo spiacenti, non è stato trovato alcun treno.\n");
        return NULL;
    }
    do
    {
        print_results(rhead);
        printf("Selezionare un treno (1 - %u): ", count);
        scanf("%u", &choice);
    } while (choice < 1 || choice > count);   


    rselect = rhead;
    for (size_t i = 1; i < choice; i++)
    {
        rselect = rselect->next;
    }

    ret = rselect->treno;
    destroy_result_list(rhead);
    return ret;
}