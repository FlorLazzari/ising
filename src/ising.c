#include "stdlib.h"
#include <time.h>
#include <stdio.h>
#include "metropolis.h"
#include "lattice.h"

int main(int argc, char **argv) {
  int n = 3;
  int *lattice = malloc(n * n * sizeof(int));
  float prob = 0.5;
  float T = 2.0;
  int niter = 2000;
  srand(time(NULL));
  fill_lattice(lattice, n, prob);

  // metropolis(lattice, n, T);
  int idx = 0; // ALERTA!!! (ESTO ES TURBIO)
  int site = pick_site(lattice, n, idx);
  // flip(lattice, int n, float T);
  int DE = delta_E (lattice, n, site);
  int E = energy(lattice, n);


  // for (int i = 0; i < niter; i++) {
  //   metropolis(lattice, n, T);
  // }
  print_lattice(lattice, n);
  printf("\n el sitio elegido es %i, la delta E es %i, la energia es %i\n",site, DE, E);

  return 0;
}
