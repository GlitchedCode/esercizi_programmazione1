#include <stdio.h>
#include "rubrica.h"

int main()
{
    Rubrica rubrica;
    char *filename = "rubrica.txt";
    char nome[MAX_NAMELEN+1], numero[MAX_NUMLEN+1];
    unsigned short choice;

    rubrica_init(&rubrica);
    if (read_from_file(&rubrica, filename))
        printf("Rubrica letta da file su disco: %s\n", filename);    

    do
    {
        printf("%s\n%s\n%s\n%s\n%s\n",
            "1. Aggiungi nuova voce in rubrica",
            "2. Ricerca esatta per nome",
            "3. Ricerca approssimata per nome",
            "4. Stampa completa della rubrica",
            "0. Esci");
        scanf("%hd", &choice);
        switch (choice)
        {
        case 1:
            printf("Inserisci nome e numero:\n");
            scanf("%" MACROSTR(MAX_NAMELEN) "s %" MACROSTR(MAX_NUMLEN) "s", 
                nome, numero);
            insert(&rubrica, nome, numero);
            break;
        case 2:
            printf("Inserisci il nome da cercare:\n");
            scanf("%" MACROSTR(MAX_NAMELEN) "s", nome);
            search(&rubrica, nome, EXACT);
            break;
        case 3:
            printf("Inserisci il nome da cercare:\n");
            scanf("%" MACROSTR(MAX_NAMELEN) "s", nome);
            search(&rubrica, nome, FUZZY);
            break;
        case 4:
            print(&rubrica);
            break;
        default:
            break;
        }
        fflush(stdin);
    }while(choice);

    if(!save_to_file(&rubrica, filename))
        fprintf(stderr, "Impossibile salvare rubrica su file: %s", filename);

    return 0;
}