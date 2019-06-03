#ifndef OPERATIONS_H
#define OPERATIONS_H

unsigned parse_file(const char *filename, short **vec);
unsigned long int sum (short* vec, unsigned len);
short max(short* vec, unsigned len);
short min(short* vec, unsigned len);
double average(short* vec, unsigned len);
double geom_average(short* vec, unsigned len);
unsigned long int prod (short* vec, unsigned len);
void print_histo(short* vec, unsigned len, const char* pstr);

#endif