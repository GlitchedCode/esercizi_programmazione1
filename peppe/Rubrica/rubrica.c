#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "rubrica.h"

void rubrica_init(Rubrica *r)
{
    r->count = 0;
}

int read_from_file(Rubrica *r, const char *filename)
{
    FILE *handle;
    int c;
    if(!r) return 0;

    handle = fopen(filename, "r");
    if(!handle) return 0;

    while((c = fscanf(handle, "%" MACROSTR(MAX_NAMELEN) "s %" MACROSTR(MAX_NUMLEN) "s\n", 
        r->contatti[r->count].nome, r->contatti[r->count].numero)) != EOF)
    {
        if(c > 0) {r->count++; }
        if(r->count >= MAX_CONTATTI) break;
    }

    fclose(handle);
    return 1;
}

int save_to_file(Rubrica *r, const char *filename)
{
    FILE *handle;
    unsigned count = 0;
    if(!r) return 0;
    
    handle = fopen(filename, "w");
    if(!handle) return 0;

    for(count = 0; count < r->count; count++)
    {
        fprintf(handle, "%" MACROSTR(MAX_NAMELEN) "s %" MACROSTR(MAX_NUMLEN) "s\n", 
            r->contatti[count].nome, r->contatti[count].numero);
    }
    fclose(handle);     
    return 1;
}

int insert(Rubrica *r, const char *nome, const char* numero)
{
    unsigned c;
    if(r->count >= MAX_CONTATTI) 
    {
        fprintf(stderr, "Rubrica piena.\n");
        return 0;
    }
    for (c = 0; c < r->count; c++)
        if(!strncmp(nome, r->contatti[c].nome, MAX_NAMELEN))
        {
            fprintf(stderr, "Nome già presente nella rubrica.\n");
            return 0;
        }
    strncpy(r->contatti[r->count].nome, nome, MAX_NAMELEN);
    strncpy(r->contatti[r->count].numero, numero, MAX_NUMLEN);
    r->count++;
    return 1;
}

void print(Rubrica *r)
{
    unsigned count;
    for(count = 0; count < r->count; count++)
    {
        printf("%" MACROSTR(MAX_NAMELEN) "s %" MACROSTR(MAX_NUMLEN) "s\n", 
            r->contatti[count].nome, r->contatti[count].numero);
    }
}

void search(Rubrica *r, const char *query, int exact)
{
    unsigned c;
    if(!r|| !query) return;
    if(exact)
    {
        for(c = 0; c < r->count; c++)
            if(strstr(r->contatti[c].nome, query) != 0)
                printf("%" MACROSTR(MAX_NAMELEN) "s %" MACROSTR(MAX_NUMLEN) "s\n", 
                    r->contatti[c].nome, r->contatti[c].numero);
    }
    else
    {
        for(c = 0; c < r->count; c++)
            if(!strncmp(r->contatti[c].nome, query, MAX_NAMELEN))
                printf("%" MACROSTR(MAX_NAMELEN) "s %" MACROSTR(MAX_NUMLEN) "s\n", 
                    r->contatti[c].nome, r->contatti[c].numero);
    }
    
}