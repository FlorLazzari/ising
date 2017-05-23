#include "stdlib.h"
#include <time.h>
#include <stdio.h>
#include "metropolis.h"
#include "lattice.h"

int main(int argc, char **argv) {
  int n = 3;
  int *lattice = malloc(n * n * sizeof(int));
  double *list = malloc(5* sizeof(double));
  float prob = 0.5;
  float T = 2.0;
  int niter = 2000;
  srand(time(NULL));
  fill_lattice(lattice, n, prob);
  float J = 1, B = 0;
  list_exp(list, T, J, B);
  // metropolis(lattice, n, T);
  int idx = 0; // ALERTA!!! (ESTO ES TURBIO)
  int site = pick_site(lattice, n, idx);
  // flip(lattice, int n, float T);
  float DE = delta_E (lattice, n, site, J, B);
  float E = energy(lattice, n, J, B);
  double prob_exp = probability(lattice[site], DE, J, B, T, list);

  // for (int i = 0; i < niter; i++) {
  //   metropolis(lattice, n, T);
  print_lattice(lattice, n);
  // }
  printf("\n el sitio elegido es %i, la delta E es %.2f, la energia es %.2f, la prob es %.3lf\n",site, DE, E, prob_exp);

  return 0;
}
