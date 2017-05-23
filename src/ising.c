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
  float T = 2.0, J = 1, B = 0;;
  int niter = 4;
  srand(time(NULL));
  fill_lattice(lattice, n, prob);
  list_exp(list, T, J, B);

  float E = energy(lattice, n, J, B);
  int M = magnet(lattice, n);
  float* p_e = &E;
  int* p_m = &M;
  float* energy_array = malloc(niter * sizeof(float)); // aca voy a guardar los valores de energia
  int* magnet_array = malloc(niter * sizeof(int)); // aca voy a guardar los valores de magnetizacon

  for (int i = 0; i < niter; i++) {
    metropolis(lattice, n, T, J, B, p_e, p_m, list);
    print_lattice(lattice, n);
    energy_array[i] = *p_e;
    magnet_array[i] = *p_m;
    printf("ARRAY ENERGIA = %f\n", energy_array[i]);
  }

  return 0;
}
