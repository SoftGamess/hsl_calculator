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
  h->hue = ((coef1*h1->hue + coef2*h2->hue) / div) % 361;
  h->sat = (coef1*h1->sat + coef2*h2->sat) / div % 101;
  h->light = (coef1*h1->light + coef2*h2->light) / div % 101;
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

int main(int argc, char **argv) {
  if (argc != 10) {
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

  print_hsl(h);

  return 0;
}
