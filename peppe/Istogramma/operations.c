#include "operations.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

unsigned parse_file(const char *filename, short **vec)
{
    unsigned ret = 1;
    int c;
    FILE *handle = fopen(filename, "r");

    if(!handle)
    {
        fprintf(stderr, "Impossibile aprire il %s in lettura.", filename);
        exit(1);
    }

    while ((c = fgetc(handle)) != EOF)
        if(c == '\n') ret++; // conto le righe

    printf("Righe: %d\n", ret);

    fseek(handle, 0, SEEK_SET);
    *vec = (short*)malloc(sizeof(short)*ret);
    
    ret = -1; // qui vado intenzionalmente fuori dai limiti del
              // tipo unsigned perche' nel loop ci rientro di certo
    do { // questo loop itera [numero di righe] + 1 volte
        ++ret;
        c = fscanf(handle, "%d\n", *vec + ret);
    }while (c != 0 && c != EOF);
    fclose(handle);
    return ret;
}

unsigned long int sum (short* vec, unsigned len)
{
    unsigned long int ret = 0;  
    for (unsigned i = 0; i < len; i++)
    {
        ret += vec[i];
    }
    return ret;
}

short max(short* vec, unsigned len)
{
    short ret = vec[0];
    for (unsigned i = 1; i < len; i++)
    {
        ret = ret < vec[i] ? vec[i] : ret;
    }
    return ret;
}

short min(short* vec, unsigned len)
{
    short ret = vec[0];
    for (unsigned i = 1; i < len; i++)
    {
        ret = ret > vec[i] ? vec[i] : ret;
    }
    return ret;
}

double average(short* vec, unsigned len)
{
    double ret = 0;
    for (unsigned i = 0; i < len; i++)
    {
        ret += (double)vec[i];
    }
    return ret / len;
}

double geom_average(short* vec, unsigned len)
{
    return pow(prod(vec,len), 1.l/len);
}

unsigned long int prod (short* vec, unsigned len)
{
    double ret = 1.l;
    for (unsigned i = 0; i < len; i++)
    {
        ret *= (double)vec[i];
    }
    return ret;
}

void print_histo(short* vec, unsigned len, const char *pstr)
{
    for (unsigned i = 0; i < len; i++)
    {
        printf("%d| ", i + 1);
        for (short j = 0; j < vec[i]; j++)
        {
            printf("%s", pstr);
        }
        printf("\n");
    }
}
