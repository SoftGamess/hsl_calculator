#ifndef CHROMATIC_CIRC
#define CHROMATIC_CIRC

#include "hsl.h"

void test_terminal_width(int n);

void test_terminal_heigth(int n);

void print_n_space(int n);

void print_ith_lign(int i);

void print_empty_chromatic_circle(void);

void fprint_chromatic_circle(FILE *tex_file, _hsl **hsl_array, int len);

#endif
