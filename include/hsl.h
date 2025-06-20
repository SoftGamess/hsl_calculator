#ifndef HSL
#define HSl

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hsl {
  int hue;
  int sat;
  int light;
};
typedef struct hsl _hsl;

struct rgb {
  int r;
  int g;
  int b;
};
typedef struct rgb _rgb;

struct hex {
  char r[3];
  char g[3];
  char b[3];
};
typedef struct hex _hex;

double min(double x, double y) ;

double max(double x, double y) ;

double double_mod(double x,int mod);

double double_abs(double x) ;

int double_approx(double x) ;

_rgb *rgb(int r, int g, int b) ;

_hex *hex(const char r[3], const char g[3], const char b[3]) ;

char hex_of_single_int(int n) ;

char *hex_of_int(int n, char hex_n[3]) ;

_hex *hex_of_rgb(const _rgb *s) ;

double magical_hsl_fun(double light,double hue, int n, double a) ;

_rgb *rgb_of_hsl(const _hsl *h);

_hex *hex_of_hsl(const _hsl *h);

_hsl *hsl(int hue, int sat, int light) ;

_hsl *amean(const _hsl *h1, const _hsl *h2, int coef1, int coef2) ;

_hsl *gmean(const _hsl *h1, const _hsl *h2) ;

int fast_exp(int x, int n) ;

int int_of_string(char *str) ;

void print_hsl(const _hsl *h) ;

void print_rgb(const _rgb *s) ;

void print_hex(const _hex *h);


#endif
