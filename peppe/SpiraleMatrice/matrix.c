#include "matrix.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>

static const int inc_vectors[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};

void print_matrix_spiral(Matrix in, unsigned order)
{
    unsigned row = 0, col = 0;
    unsigned turns = 0;
    unsigned max_turns = (order * 2) - 1;
    short current_inc;
    long row_top_limit = -1, col_left_limit = -1;
    long row_bottom_limit = order, col_right_limit = order;
    while(1)
    {
        if(!((row > row_top_limit) && (row < row_bottom_limit 
)) ||
            !((col > col_left_limit) && (col < col_right_limit)))
        {
            row -= inc_vectors[current_inc][0];
            col -= inc_vectors[current_inc][1];
            
            if(inc_vectors[current_inc][1] > 0)
                row_top_limit++;
            else if(inc_vectors[current_inc][1] < 0)
                row_bottom_limit--;
            else if(inc_vectors[current_inc][0] > 0)
                col_right_limit--;
            else if(inc_vectors[current_inc][0] < 0)
                col_left_limit++;

            turns++;
            current_inc = turns % 4;
            row += inc_vectors[current_inc][0];
            col += inc_vectors[current_inc][1];
        }

        if(turns >= max_turns) break;

        printf("%lf %d %d\n", in[row][col], row, col);
        row += inc_vectors[current_inc][0];
        col += inc_vectors[current_inc][1];
    }
    printf("\n");
}

Matrix create_matrix(unsigned order)
{
    Matrix ret = (Matrix)malloc(sizeof(double*)*order);
    if (ret)
        for (int i = 0; i < order; i++)
        {
            ret[i] = (double*)malloc(sizeof(double)*order);
            if(!ret[i])
            {
                fprintf(stderr, "Errore durante la creazione della matrice\n");
                exit(1);
            }
        }
    return ret;
}

void destroy_matrix(Matrix *m, unsigned order)
{
    for(unsigned i = 0; i < order; i++)
        free((*m)[i]);
    free(*m);
    *m = NULL;
}

void fill_hilbert(Matrix in, unsigned order)
{
    for(int r = 0; r < order; r++)
    {
        for(int c = 0; c < order; c++)
        {
            in[r][c] = 1.f / (r + c + 1);
        }
    }
}

void fill_vandermonde_ab(Matrix in, unsigned order, double a, double b)
{
    double step;
    unsigned row, col, i;

    for (row = 0; row < order; row++)
        in[row][0]=1.l;

    if (order < 2)
        return;

    step = (b - a) / order;

    for(row = 0; row < order; row++)
    {
        for(col = 1; col < order; col++)
        {
            in[row][col] = 1.l;
            for(i=0;i<col;i++)
                in[row][col] *= a + (step * row);
        }
    }
}

void print_matrix(Matrix in, unsigned order)
{
    unsigned row, col;
    for(row = 0; row < order; row++)
    {
        for(col = 0; col < order; col++)
            printf("%lf ", in[row][col]);
        printf("\n");

    }
    printf("\n");
}
