#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "albergo.h"

// Ciclo vitale della lista
void init_alberghi(ListaAlberghi *head)
{
    if(head) *head = NULL;
}

int read_from_file(ListaAlberghi *head, char* filename)
{
    FILE *fp;
    char nome[MAX_NOME_ALBERGO + 1], **servizi = NULL;
    unsigned short stelle = 0, nServizi;
    int res;

    fp = fopen(filename, "r");
    if(!fp) return 0;

    do
    {
        fscanf(fp, "%20s (", nome);
        while (fscanf(fp,"*") > 0)
            stelle++;

        fscanf(fp, "), %u ", &nServizi);
        
        if(nServizi)
        {
            servizi = (char**)malloc(sizeof(char*)*nServizi);
            for(unsigned i = 0; i < nServizi; i++)
            {
                servizi[i] = (char*)malloc(sizeof(char) * (MAX_NOME_SERVIZIO + 1));
                fscanf(fp, "%s ", servizi[i]);
            }
        }
        res = fscanf(fp, "\n");
        insert_albergo(head, nome, stelle, nServizi, servizi);
        nServizi = 0;
    } while (res != EOF);

    fclose(fp);
    return 1;
}

int save_to_file(ListaAlberghi head, char* filename)
{
    FILE *fp;
    int res;

    fp = fopen(filename, "w");
    if(!fp) return 0;

    while(head)
    {
        fprintf(fp, "%20s (", head->nome);
        for(unsigned i = 0; i < head->stelle; i++)
            fprintf(fp,"*");
        fprintf(fp, "), %u ", head->nServizi);
        for(unsigned i = 0; i < head->nServizi; i++)
        {
            fprintf(fp, "%s ", head->servizi[i]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    return 1;   
}

void destroy_alberghi(ListaAlberghi head)
{
    ListaAlberghi temp;
    while(head)
    {
        temp = head;
        head = head->next;
        for(unsigned i = 0; i < temp->nServizi; i++)
        {
            free(temp->servizi[i]);
        }
        free(temp->servizi);
        free(temp);
    }
}

// Controllo dei dati della lista
void insert_albergo(ListaAlberghi *head, char *nome, unsigned short stelle, 
    unsigned short nServizi, char **servizi)
{
    if(!head || !strlen(nome) || !stelle)
    {
        fprintf(stderr, "Parametri invalidi passati a insert_albergo.\n");
        return;
    }
    ListaAlberghi temp;
    temp = (ListaAlberghi)malloc(sizeof(Albergo));
    temp->next = *head;
    *head = temp;
    temp->stelle = stelle;
    temp->nServizi = nServizi;
    temp->servizi = servizi;
    strncpy(temp->nome, nome, MAX_NOME_ALBERGO);
}

void query_alberghi(ListaAlberghi head, unsigned short stelle, char *servizio)
{
    
}