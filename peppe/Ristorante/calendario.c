#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "calendario.h"

// Questa funzione inizializza il calendario per un mese, restituendo quanti
// giorni sono stati impostati 
int calendario(MESE* mese){
    FILE *pf;
    char scelta;
    int i, j;
    int giorni = 0;
    // dichiarati come unsigned ci permettono di risparmiarci 
    // un controllo quando verifichiamo la correttezza dei dati
    unsigned int mes, anno, apertura, chiusura, riposo;

    pf = fopen("aperture.txt", "r+");

    // Controllo dell'input
    if(pf) do{
        printf("Inserire nuovo mese? [(S/n)]\n");
        scanf("%c", &scelta);
        fflush(stdin);
    }while(tolower((int)scelta) != 's' && tolower((int)scelta) != 'n'); 
    else scelta = 's';
    // creo il nuovo calendario
    if (scelta == 's'){
        do{
            printf("Inserire mese (1-12):\n");
            scanf("%d", &mes);
        }while(mes < 1 || mes > 12);

        mese->mese = mes;

        printf("Inserire anno:");
        scanf("%d", &anno);
        
        mese->anno = anno;

        // Anno bisestile
        if(!(anno % 4) && mes == 2)
            giorni = 29;
        else
            giorni = mese_count[mes-1];

        mese->numero_giorni = giorni;

        do{
            printf("Inserire inserire orario di apertura (0-23): ");
            scanf("%d", &apertura);
            printf("Inserire orario chiusura (0-23): ");
            scanf("%d", &chiusura);
        } while(apertura > 23 || chiusura > 23);
        
        mese->apertura = apertura;
        mese->chiusura = chiusura;

        do{
            printf("Inserire primo giorno di riposo (1-31):");
            scanf("%d", &riposo);
        } while(riposo < 1 || riposo > 31);

        pf = fopen("aperture.txt", "w");

        // Il mese è stato inizializzato (i giorni non ancora)
        fprintf(pf, "%2d %4d, %2d:00 - %2d:00\n", mes, anno, apertura, chiusura);
        printf("%s %4d, %2d:00 - %2d:00\n", mese_str[mes-1], anno, apertura, chiusura);


        // Inizializzo i giorni
        for (i=0; i<giorni; i++){
            for(j=0;j<NUMERO_SALE;j++)
            {
                mese->giorni[i].stato_ora[j] = (int*)malloc(sizeof(int)*(chiusura - apertura));
                memset(mese->giorni[i].stato_ora[j],0,sizeof(int)*(chiusura - apertura));
            }
            if (i+1 == riposo){
                //printf("%d", riposo);
                mese->giorni[i].aperto = CHIUSO;
                riposo= riposo + 7;
            }
            else
                mese->giorni[i].aperto = APERTO;
            fprintf(pf, "%2d, %d\n", i + 1, mese->giorni[i].aperto);
            printf("%2d, %s\n", i + 1, apertura_str[mese->giorni[i].aperto]);
        }
    }
    // leggo da file il calendario esistente
    else {
        pf = fopen("aperture.txt", "r");
        fscanf(pf, "%2d %4d, %2d:00 - %2d:00\n", &(mese->mese), 
            &(mese->anno), &(mese->apertura), &(mese->chiusura));
        printf("%s %4d, %2d:00 - %2d:00\n", mese_str[mese->mese - 1], 
            mese->anno, mese->apertura, mese->chiusura);

        // Anno bisestile
        if(!(mese->anno % 4) && mese->mese == 2)
            giorni = 29;
        else
            giorni = mese_count[mese->mese-1];

        mese->numero_giorni = giorni;

        int indice, aperto;
        // Inizializzo i giorni
        while(fscanf(pf, "%2d, %d\n", &indice, &aperto) != EOF)
        {
            for(j=0;j<NUMERO_SALE;j++)
            {
                mese->giorni[indice - 1].stato_ora[j] = (int*)malloc(sizeof(int)*(mese->chiusura - mese->apertura));
                memset(mese->giorni[indice -1].stato_ora[j],0,sizeof(int)*(mese->chiusura - mese->apertura));
            }
            mese->giorni[indice-1].aperto = aperto;
            printf("%2d, %s\n", indice, apertura_str[aperto]);            
        }
    }
    fclose(pf);    
}

void distruggi_calendario(MESE* mese)
{
    if(!mese) return;
    for (int i = 0; i < mese->numero_giorni; i++)
    {
        for(int j = 0; j < NUMERO_SALE; j++)
        {
            free(mese->giorni[i].stato_ora[j]);
        }
    }
    free(mese);
}