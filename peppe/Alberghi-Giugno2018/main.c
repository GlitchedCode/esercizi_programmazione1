#include <stdio.h>
#include <stdlib.h>
#include "albergo.h"

void inserisci(ListaAlberghi *head);
void cerca(ListaAlberghi head, unsigned short stelle);

int main()
{
    ListaAlberghi head;
    char *filename = "alberghi.txt";
    unsigned choice;

    init_alberghi(&head);
    if(read_from_file(&head, filename))
        printf("Alberghi caricati da %s.\n", filename);

    print_all(head);

    do
    {
        printf("%s\n%s\n%s\n%s\n",
            "1. Inserisci un albergo.",
            "2. Cerca albergo per servizio.",
            "3. Cerca albergo per servizio e stelle.",
            "0. Esci.");
        scanf("%u", &choice);

        switch (choice)
        {
        case 1:
            inserisci(&head);
            break;
        case 2:
            cerca(head, 0);
            break;
        case 3:
            do
            {
                printf("Inserire il numero di stelle richieste: ");
                scanf("%hu", &choice);
            } while (!choice);
            cerca(head, choice);
            break;
        default:
            break;
        }
    } while (choice);

    if(!save_to_file(head, filename))
        printf("Impossibile salvare gli alberghi in %s.\n", filename);
    destroy_alberghi(head);

    return 0;    
}


void inserisci(ListaAlberghi *head)
{
    char nome[MAX_NOME_ALBERGO + 1], **servizi;
    int nServizi; 
    int stelle;

    printf("Inserire nome: ");
    scanf("%20s", nome);
    printf("Inserire il numero di stelle: ");
    scanf("%d", &stelle);
    printf("Inserire il numero di servizi: ");
    scanf("%d", &nServizi);
    servizi = (char**)malloc(sizeof(char*)*nServizi);
    for(unsigned i = 0; i < nServizi; i++)
    {
        servizi[i] = (char*)malloc(sizeof(char) * (MAX_NOME_SERVIZIO + 1));
        printf("Inserire servizio: ");
        scanf("%50s", servizi[i]);
    }
    insert_albergo(head, nome, stelle, nServizi, servizi);
}

void cerca(ListaAlberghi head, unsigned short stelle)
{
    char servizio[MAX_NOME_SERVIZIO + 1];

    printf("Inserisci il nome del servizio richiesto: ");
    scanf("%50s", servizio);
    query_alberghi(head, stelle, servizio);
}