#include "hsl.h"
#include <stdio.h>

void test_terminal_width(int n) {
  for (int i = 0; i < n; i++) {
    printf("-");
  }
  printf("\nnb printed : %d\n", n);
}

void test_terminal_heigth(int n) {
  for (int i = 0; i < n; i++) {
    printf("-\n");
  }
  printf("\nnb printed : %d\n", n);
}

void print_n_space(int n) {
  for (int i = 0; i < n; i++) {
    printf(" ");
  }
}

void print_ith_lign(int i) {
  print_n_space(12 - i - 1);
  printf("-");
  print_n_space(2 * i);
  printf("-");
  print_n_space(12 - i - 1);
  printf("\n");
}

void print_empty_chromatic_circle(void) {
  for (int i = 0; i < 12; i++) {
    print_ith_lign(i);
  }
  for (int i = 11; i >= 0; i--) {
    print_ith_lign(i);
  }
}

void fprint_chromatic_circle(FILE *tex_file, _hsl **hsl_array, int len) {
  fprintf(
      tex_file,
      "\\documentclass{article}\n\\usepackage{tikz}\n\\usepackage{amssymb}\n "
      "\\usepackage{amsmath}\n\\usepackage{mathrsfs}\n\\usepackage{esint}\n"
      "\\usepackage{geometry}\n\\geometry{lmargin=1cm,rmargin=1cm}\n"
      "\\begin{document}\n\n\\begin{tikzpicture}\n");
  double radius = 7.;
  double outer_radius = radius + 2.;
  double mid_radius = (radius + outer_radius) / 2.;
  fprintf(tex_file,
          "  \\draw (0,0) circle (%lfcm);\n  \\draw (0,0) circle (%lfcm);\n  "
          "\\node at (0,0) {$+$};\n",
          radius, outer_radius);

  for (int i = 0; i < 12; i++) {
    double theta = ((double)i) * M_PI / 6. - M_PI / 12.;
    double x = radius * cos(theta);
    double y = radius * sin(theta);
    double xp = outer_radius * cos(theta);
    double yp = outer_radius * sin(theta);
    double xcolor = mid_radius * cos(theta + M_PI / 12.);
    double ycolor = mid_radius * sin(theta + M_PI / 12.);
    fprintf(tex_file,
            "  \\draw (%lf,%lf) -- (%lf,%lf);\n  \\node at (%lf,%lf) {", x, y,
            xp, yp, xcolor, ycolor);
    switch (i) {
    case 0:
      fprintf(tex_file, "red");
      break;
    case 1:
      fprintf(tex_file, "orange");
      break;
    case 2:
      fprintf(tex_file, "yellow");
      break;
    case 3:
      fprintf(tex_file, "yellow-green");
      break;
    case 4:
      fprintf(tex_file, "green");
      break;
    case 5:
      fprintf(tex_file, "green-cyan");
      break;
    case 6:
      fprintf(tex_file, "cyan");
      break;
    case 7:
      fprintf(tex_file, "cyan-blue");
      break;
    case 8:
      fprintf(tex_file, "dark blue");
      break;
    case 9:
      fprintf(tex_file, "blue-magenta");
      break;
    case 10:
      fprintf(tex_file, "magenta");
      break;
    case 11:
      fprintf(tex_file, "magenta-red");
      break;
    default:
      printf("Index i should not take that value");
      exit(1);
    }
    fprintf(tex_file, "};\n");
  }

  for (int i = 0; i < len; i++) {
    double hue_in_radians = (((double)hsl_array[i]->hue) * M_PI) / 180.;
    double sat_radius = (((double)hsl_array[i]->sat) / 100) * radius;
    double x = sat_radius * cos(hue_in_radians);
    double y = sat_radius * sin(hue_in_radians);
    fprintf(tex_file, "  \\node at (%lf,%lf) {$\\bullet$};\n", x, y);
  }
  fprintf(tex_file, "\\end{tikzpicture}\n\\end{document}");
}
