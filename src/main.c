#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double min(double x, double y) {
  if (x <= y) {
    return x;
  } else {
    return y;
  }
}

double max(double x, double y) {
  if (x >= y) {
    return x;
  } else {
    return y;
  }
}

double double_mod(double x,int mod){
  int mod_x = (int) x % mod;
  return ((double) mod_x) + (x - (double) (int) x);
}

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

double double_abs(double x) {
  if (x >= 0) {
    return x;
  } else {
    return -x;
  }
}

int double_approx(double x) {
  double decimals = x - ((double)(int)x);
  if (0 <= decimals && decimals < 0.5) {
    return (int)x;
  } else if (0.5 <= decimals && decimals < 1) {
    return ((int)x) + 1;
  } else if (-1 < decimals && decimals <= -0.5) {
    return ((int)x) - 1;
  } else if (-0.5 < decimals && decimals < 0) {
    return (int)x;
  } else {
    printf("The value of x's decimals is greater than 1 !\n");
    exit(1);
  }
}

_rgb *rgb(int r, int g, int b) {
  _rgb *s = (_rgb *)malloc(sizeof(_rgb));
  s->r = r % 256;
  s->g = g % 256;
  s->b = b % 256;
  return s;
}

_hex *hex(const char r[3], const char g[3], const char b[3]) {
  _hex *h = (_hex *)malloc(sizeof(_hex));
  strcpy(h->r, r);
  strcpy(h->g, g);
  strcpy(h->b, b);
  return h;
}

char hex_of_single_int(int n) {
  if (!(0 <= n && n <= 15)) {
    printf("Your integer is not comprised between 0 and 15 included !\n");
    exit(1);
  }
  switch (n) {
  case 0:
    return '0';
    break;
  case 1:
    return '1';
    break;
  case 2:
    return '2';
    break;
  case 3:
    return '3';
    break;
  case 4:
    return '4';
    break;
  case 5:
    return '5';
    break;
  case 6:
    return '6';
    break;
  case 7:
    return '7';
    break;
  case 8:
    return '8';
    break;
  case 9:
    return '9';
    break;
  case 10:
    return 'A';
    break;
  case 11:
    return 'B';
    break;
  case 12:
    return 'C';
    break;
  case 13:
    return 'D';
    break;
  case 14:
    return 'E';
    break;
  case 15:
    return 'F';
    break;
  default:
    printf("This case should not trigger !");
    exit(1);
  }
}

char *hex_of_int(int n, char hex_n[3]) {
  if (!(0 <= n && n <= 255)) {
    printf("Your integer is not comprised between 0 and 255 included !\n");
    exit(1);
  }
  hex_n[2] = '\0';
  int remainder1 = n % 16;
  int remainder2 = (n / 16) % 16;
  hex_n[0] = hex_of_single_int(remainder2);
  hex_n[1] = hex_of_single_int(remainder1);
  return hex_n;
}

_hex *hex_of_rgb(const _rgb *s) {
  _hex *h = (_hex *)malloc(sizeof(_hex));
  hex_of_int(s->r, h->r);
  hex_of_int(s->g, h->g);
  hex_of_int(s->b, h->b);
  return h;
}

double magical_hsl_fun(double light,double hue, int n, double a) {
  double k = double_mod((double) n + (hue/30),12);
  return light-a*max(-1,min(k-3.,min(9.-k,1.)));
}

_rgb *rgb_of_hsl(const _hsl *h){
  double light = ((double) h->light)/100;
  double hue = (double) h->hue;
  double sl = ((double) h->sat)/100;
  double a = sl*min(light,1.-light);
  
  _rgb *res = (_rgb*) malloc(sizeof(_rgb));
  res->r = double_approx(256.*magical_hsl_fun(light, hue,0,a)-1);
  res->g = double_approx(256.*magical_hsl_fun(light, hue,8,a)-1);
  res->b = double_approx(256.*magical_hsl_fun(light, hue,4,a)-1);
  return res;
}

_hex *hex_of_hsl(const _hsl *h){
  return hex_of_rgb(rgb_of_hsl(h));
}


_hsl *hsl(int hue, int sat, int light) {
  assert(hue >= 0 && sat >= 0 && light >= 0);
  _hsl *h = (_hsl *)malloc(sizeof(_hsl));
  h->hue = hue % 361;
  h->sat = sat % 101;
  h->light = light % 101;
  return h;
}

_hsl *amean(const _hsl *h1, const _hsl *h2, int coef1, int coef2) {
  int div = coef1 + coef2;
  _hsl *h = (_hsl *)malloc(sizeof(_hsl));
  h->hue = ((coef1 * h1->hue + coef2 * h2->hue) / div) % 361;
  h->sat = (coef1 * h1->sat + coef2 * h2->sat) / div % 101;
  h->light = (coef1 * h1->light + coef2 * h2->light) / div % 101;
  return h;
}

_hsl *gmean(const _hsl *h1, const _hsl *h2) {
  _hsl *h = (_hsl *)malloc(sizeof(_hsl));
  h->hue = (int)sqrt((double)h1->hue * (double)h2->hue) % 361;
  h->sat = (int)sqrt((double)h1->sat * (double)h2->sat) % 101;
  h->light = (int)sqrt((double)h1->light * (double)h2->light) % 101;
  return h;
}

int fast_exp(int x, int n) {
  if (n == 0) {
    return 1;
  } else if (n % 2 == 0) {
    return fast_exp(x * x, n / 2);
  } else {
    return x * fast_exp(x * x, n / 2);
  }
}

int int_of_string(char *str) {
  int len = strlen(str);
  int result = 0;
  int factor = 1;
  if (len >= 5) {
    printf("Your number is more than 5 digit long which does not make sense "
           "(but is correct) for HSL values !\n");
    exit(1);
  }
  for (int i = len - 1; i >= 0; i--) {
    int ascii_code = (int)str[i];
    if (!(48 <= ascii_code && ascii_code <= 57)) {
      printf("Your number has non-digit character in it !\n");
      exit(1);
    }
    result += (ascii_code - 48) * factor;
    factor *= 10;
  }
  return result;
}

void print_hsl(const _hsl *h) {
  printf("hsl(%d,%d,%d)", h->hue, h->sat, h->light);
}

void print_rgb(const _rgb *s) { printf("rgb(%d,%d,%d)", s->r, s->g, s->b); }

void print_hex(const _hex *h){
  printf("#%s%s%s",h->r,h->g,h->b);
}

int main(int argc, char **argv) {
  /*if (argc != 10) {
    printf("Number of arguments is supposed to be 10 !");
    exit(1);
  }
  char mode;
  if (strcmp("a", argv[1]) == 0) {
    mode = 'a';
  } else if (strcmp("g", argv[1]) == 0) {
    mode = 'g';
  } else {
    printf("Second argument is supposed to be 'a' or 'g' for arithmetic mean "
           "or geometric mean respectively !\n");
    exit(1);
  }

  _hsl *h1 = malloc(sizeof(_hsl));
  _hsl *h2 = malloc(sizeof(_hsl));

  h1->hue = int_of_string(argv[2]) % 361;
  h1->sat = int_of_string(argv[3]) % 101;
  h1->light = int_of_string(argv[4]) % 101;
  h2->hue = int_of_string(argv[5]) % 361;
  h2->sat = int_of_string(argv[6]) % 101;
  h2->light = int_of_string(argv[7]) % 101;


  _hsl *h = NULL;

  if (mode == 'a') {
    h = amean(h1,h2,int_of_string(argv[8]),int_of_string(argv[9]));
  }
  else {
    h = gmean(h1,h2);
  }

  print_hsl(h);*/

  _hsl *h = (_hsl *)malloc(sizeof(_hsl));
  h->hue = 60;
  h->sat = 50;
  h->light = 50;

  _hex *hp = hex_of_hsl(h);

  print_hex(hp);

  return 0;
}
