#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include "operations.h"
#include <stdlib.h>

#define DEFAULT_PSTR "*"

void usage();

int main(int argc, char** argv)
{
    int opt;
    char* filename = "vec.txt";
    char* pstr = DEFAULT_PSTR;
    short *vec = NULL;
    unsigned len;

    opterr = 0;
    while ((opt = getopt(argc, argv, "hf:p:")) != -1)
    {
        switch (opt)
        {
        case 'f':
            filename = optarg;
            break;
        case 'p':
            pstr = optarg;
            break;
        case 'h':
            usage();
            return 0;
            break;
        case '?':
            usage();
            return 1;
            break;
        default:
            break;
        }
    }
    
    len = parse_file(filename, &vec);
    printf("Numeri letti: %d\n", len);

    if(!len)
    {
        printf("Vettore vuoto.");
        return 0;
    }

    print_histo(vec,len,pstr);

    printf("%s: %ld\n%s: %lf\n%s: %lf\n%s: %2d\n%s: %2d",
        "Somma", sum(vec,len),
        "Media aritmetica", average(vec, len),
        "Media geometrica", geom_average(vec,len),
        "Minimo", min(vec,len),
        "Massimo", max(vec,len));


    free(vec);
    return 0;
}

void usage()
{
    printf("histo [-f FILENAME] [-p POINT_STRING]\n-h option prints this message");
}