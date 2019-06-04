#ifndef MATRIX_H
#define MATRIX_H

typedef double **Matrix;

Matrix create_matrix(unsigned order);
void destroy_matrix(Matrix *m, unsigned order);
void fill_hilbert(Matrix in, unsigned order);
void fill_vandermonde_ab(Matrix in, unsigned order, double a, double b);
void print_matrix(Matrix in, unsigned order);
void print_matrix_spiral(Matrix in, unsigned order);
#endif