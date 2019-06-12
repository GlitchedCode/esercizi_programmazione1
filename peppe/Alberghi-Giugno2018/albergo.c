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
    int stelle = 0, nServizi;
    int res; char c;

    fp = fopen(filename, "r");
    if(!fp) return 0;

    do
    {
        res = fscanf(fp, "%20s (", nome);
        while (fscanf(fp,"%1c", &c) > 0)
        {
            if(c == ')') break;
            stelle = stelle + 1;
        }

        res = fscanf(fp, ", %d", &nServizi);
        if(res < 1) break; 
        if(nServizi)
        {
            fscanf(fp, " ");
            servizi = (char**)malloc(sizeof(char*)*nServizi);
            for(unsigned i = 0; i < nServizi; i++)
            {
                servizi[i] = (char*)malloc(sizeof(char) * (MAX_NOME_SERVIZIO + 1));
                fscanf(fp, "%50s", servizi[i]);
            }
        }
        res = fscanf(fp, "%c", &c);
        if(res < 1 || c != '\n') break;
        insert_albergo(head, nome, stelle, nServizi, servizi);
        nServizi = 0;
        stelle = 0;
        servizi = NULL;
    } while (1);

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
        res = fprintf(fp, "%s (", head->nome);
        for(unsigned i = 0; i < head->stelle; i++)
            fprintf(fp,"*");
        res = fprintf(fp, "), %u", head->nServizi);
        for(unsigned i = 0; i < head->nServizi; i++)
        {
            fprintf(fp, " %s", head->servizi[i]);
        }
        fprintf(fp, "\n");

        head = head->next;
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

void print_all(ListaAlberghi head)
{
    while(head)
    {
        printf("%20s (", head->nome);
        for(unsigned i = 0; i < head->stelle; i++)
            printf("*");
        printf("), %u ", head->nServizi);
        for(unsigned i = 0; i < head->nServizi; i++)
        {
            printf("%s ", head->servizi[i]);
        }
        printf("\n");
        head = head->next;
    }
}

// Controllo dei dati della lista
void insert_albergo(ListaAlberghi *head, char *nome, unsigned short stelle, 
    unsigned short nServizi, char **servizi)
{
    if(!head || !strlen(nome) || !stelle)
    {
        fprintf(stderr, "Parametri invalidi passati a insert_albergo.\n");
        fprintf(stderr, "%d %s %d\n", (long int)head, nome, stelle);
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
    char found = 0;
    while(head)
    {
        if(head->stelle >= stelle)
        {
            for(unsigned i = 0; i < head->nServizi; i++)
                if(!strncmp(head->servizi[i], servizio, MAX_NOME_SERVIZIO))
                {
                    found = 1;
                    break;
                }
            
            if(found)
            {
                printf("%20s (", head->nome);
                for(unsigned i = 0; i < head->stelle; i++)
                    printf("*");
                printf("), %u ", head->nServizi);
                for(unsigned i = 0; i < head->nServizi; i++)
                {
                    printf("%s ", head->servizi[i]);
                }
                printf("\n");
            }

            found = 0;
        }

        head = head->next;
    }
}