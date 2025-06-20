#include "chromatic_circ.h"
#include <stdio.h>


int main(int argc, char **argv) {

  if (argc <= 1){
    return 0;
  }
  const char *mode = argv[1];
  if (strcmp(mode,"to_rgb") == 0){
    if (argc < 5){
      printf("When converting HSL to RGB, you must provide at least 3 values for a valid HSL code !\n");
      exit(1);
    } else if (argc > 5){
      printf("When converting HSL to RGB, you must provide only 3 values for a valid HSL code !\n");
      exit(1);
    } else {
      _hsl *h = (_hsl*) malloc(sizeof(_hsl));
      h->hue = int_of_string(argv[2]);
      h->sat = int_of_string(argv[3]);
      h->light = int_of_string(argv[4]);
      print_rgb(rgb_of_hsl(h));
      return 0;
    }
  } else if (strcmp(mode,"to_hex") == 0){
    if (argc < 5){
      printf("When converting HSL to HEX, you must provide at least 3 values for a valid HSL code !\n");
      exit(1);
    } else if (argc > 5){
      printf("When converting HSL to HEX, you must provide only 3 values for a valid HSL code !\n");
      exit(1);
    } else {
      _hsl *h = (_hsl*) malloc(sizeof(_hsl));
      h->hue = int_of_string(argv[2]);
      h->sat = int_of_string(argv[3]);
      h->light = int_of_string(argv[4]);
      print_hex(hex_of_hsl(h));
      return 0;
    }
  } else if (strcmp(mode,"circ") == 0){
    if (argc % 3 != 0){
      printf("Invalid number of argument for a print of chromatic circle !\n");
      exit(1);
    }
    int color_nb = argc / 3 - 1;
    char conf[2];
    printf("Are you sure you want to potentially overwrite the file \"%s\" ? (y/n)\n",argv[2]);
    fgets(conf,2,stdin);
    if (strcmp(conf,"y") != 0){
      printf("Exiting program.\n");
      return 0;
    }
    FILE *stream = fopen(argv[2],"w+");
    _hsl **hsl_array = (_hsl**)malloc(sizeof(_hsl)*color_nb);
    for (int i = 0; i < color_nb; i++){
      hsl_array[i] = (_hsl*) malloc(sizeof(_hsl));
      hsl_array[i]->hue = int_of_string(argv[3*(i+1)]);
      hsl_array[i]->sat = int_of_string(argv[3*(i+1)+1]);
      hsl_array[i]->light = int_of_string(argv[3*(i+1)+2]);
    }
    fprint_chromatic_circle(stream,hsl_array,color_nb);
    return 0;
  } else {
    printf("Unknown mode !\n");
    exit(1);
  }

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

  return 0;
}
