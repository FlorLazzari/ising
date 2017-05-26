#include "stdlib.h"
#include <time.h>
#include <stdio.h>
#include "metropolis.h"
#include "lattice.h"

// Programa para estimar el tiempo de termalizacion a varios B y T

int main(int argc, char **argv) {
  FILE *fdat;
  fdat = fopen("datos_magnet_energy_termalizacion.csv", "w");
  fprintf(fdat, "i    M    E    B    T\n");
  int n = 20;
  int *lattice = malloc(n * n * sizeof(int));
  double *list = malloc(5* sizeof(double));
  float prob = 0.5;
  float T = 0, J = 0, B = 0;
  int niter = 10000;
  srand(time(NULL));
  fill_lattice(lattice, n, prob);

  for (int k = 0; k < 5; k++){

    T = (float)k;

    for (int j = 0; j < 5; j++) {

      B = (float)j;
      list_exp(list, T, J, B);

      float E = energy(lattice, n, J, B);
      float M = magnet(lattice, n);
      float* p_e = &E;
      float* p_m = &M;
      float* energy_array = malloc(niter * sizeof(float)); // aca voy a guardar los valores de energia
      float* magnet_array = malloc(niter * sizeof(float)); // aca voy a guardar los valores de magnetizacon

      for (int i = 0; i < niter; i++) {
        metropolis(lattice, n, T, J, B, p_e, p_m, list);
        // print_lattice(lattice, n);
        energy_array[i] = *p_e;
        magnet_array[i] = *p_m;
        // printf("ARRAY MAG = %f\n", magnet_array[i]);
        // printf("ARRAY ENERGIA = %f\n", energy_array[i]);
        fprintf(fdat, "%i,%3.6g,%3.3g,%.1g,%.1g \n",i, magnet_array[i], energy_array[i], B, T);
      }

    }

  }


  return 0;
}
