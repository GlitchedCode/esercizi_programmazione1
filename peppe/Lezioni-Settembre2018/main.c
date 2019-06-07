#include "lezione.h"
#include <stdio.h>

int main()
{
    ListaLezioni lista;
    char* filename = "lezioni.txt";
    unsigned short choice;
    char code[CODE_MAX_LEN + 1];
    unsigned short day, mon, year;
    unsigned presenze;

    init_lista_lezioni(&lista);
    if(load_from_file(&lista, filename))
        printf("Lezioni caricate da %s.\n", filename);

    do
    {
        printf("%s\n%s\n%s\n%s\n%s\n",
            "1. Inserisci lezione.",
            "2. Stampa la media delle presenze.",
            "3. Corso più popolare.",
            "4. Corso meno popolare.",
            "0. Esci");
        scanf("%hd", &choice);

        switch (choice)
        {
        case 1:
            printf("Inserire i dati della lezione (CODICE GG/MM/AAAA NUMEROPRESENZE):\n");
            scanf("%s %2hd/%2hd/%4hd %hd", code, &day, &mon, &year, &presenze);
            if(!insert_head(&lista, code, day, mon, year, presenze))
                fprintf(stderr,"Errore durante l'inserimento della lezione.\n");
            break;
        case 2:
            print_courses_data(lista);
            break;
        case 3:
            print_most_popular(lista);
            break;
        case 4:
            print_most_unpopular(lista);
            break;
        default:
            break;
        }

    } while (choice);
    

    if(!save_to_file(lista, filename))
        fprintf(stderr,"Impossibile salvare le lezioni in %s.\n", filename);
    destroy_lista_lezioni(lista);
    return 0;
}