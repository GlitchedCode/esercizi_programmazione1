#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "treno.h"

Treno *scelta_treno(ListaTreni head);

int main()
{
    ListaTreni head, temp;
    char* filename = "treni.txt";
    int row, seat, car;
    unsigned choice, result;

    srand(time(0));
    init_treni(&head);
    if(load_from_file(&head, filename))
        printf("Treni caricati da %s.\n", filename);

    do
    {
        printf("1. Visualizza i posti liberi.\n"
                "2. Prenota un posto.\n"
                "3. Libera un posto.\n"
                "0. Esci\n");
        scanf("%u", &choice);

        switch (choice)
        {
        case 1:
            temp = scelta_treno(head);
            if(!temp) break;
            stampa_posti_treno(temp);
            break;
        case 2:
            temp = scelta_treno(head);
            if(!temp) break;
            printf("1. Corridoio\n2. Finestrino\n");
            scanf("%u", &choice);
            result = prenota_posto(temp, choice, &row, &seat);
            if(result) printf("ID prenotazione: %u\n", result);
            choice = 2;
            break;
        case 3:
            temp = scelta_treno(head);
            if(!temp) break;
            printf("Inserire posto, fila e carrozza in cui liberare la prenotazione:\n");
            scanf("%d %d %d", &seat, &row, &car);
            libera_posto(temp, car, row, seat);
            break;
        default:
            break;
        }
    } while (choice);
    
    destroy_lista_treni(head);
    return 0;
}

Treno *scelta_treno(ListaTreni head)
{
    char partenza[MAX_CITY_NAME_LEN + 1];
    char destinazione[MAX_CITY_NAME_LEN + 1];

    printf("Inserire la stazione di partenza: ");
    scanf("%s", partenza);
    printf("Inserire la stazione di destinazione: ");
    scanf("%s", destinazione);

    return seleziona_treno(head, partenza, destinazione);
}