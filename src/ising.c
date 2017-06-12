#include "stdlib.h"
#include <time.h>
#include <stdio.h>
#include "metropolis.h"
#include "lattice.h"


int main(int argc, char **argv) {
  FILE *fdat;
  fdat = fopen("sample_prueba_n32_100_100temps.csv", "w");
  fprintf(fdat, "i    M    E    T\n");
  int n = 32;
  int *lattice = malloc(n * n * sizeof(int));
  double *list = malloc(5* sizeof(double));
  float prob = 0.5;
  float T = 2, J = 1, B = 0;
  int range_temp = 100;
  int n_term = 300000;
  int n_corr = 30000;
  int n_iter = 100*n_corr;
  float T_max = 5;
  srand(time(NULL));

  fill_lattice(lattice, n, prob); // lo hago una unica vez para reciclar el termalizado para la proxima T
  // for (int j=0; j < range_temp; j++){
  //
  //   //T = 0.4 + (4.0/10)*j; como andaba antes
  //   T = (T_max/range_temp)*(j+1);
  //   //B = 0.0;
  //   //fill_lattice(lattice, n, prob);
  //   list_exp(list, T, J, B);
  //
  //   float E = energy(lattice, n, J, B);
  //   float M = magnet(lattice, n);
  //   float* p_e = &E;
  //   float* p_m = &M;
  //   float* energy_array = malloc(n_iter * sizeof(float)); // aca voy a guardar los valores de energia
  //   float* magnet_array = malloc(n_iter * sizeof(float)); // aca voy a guardar los valores de magnetizacon
  //
  //   // ciclo de termalizacion
  //   for (int i = 0; i < n_term; i++) {
  //     // printf("antes de cambiar\n");
  //     // print_lattice(lattice, n);
  //     // printf("cambiado\n");
  //     metropolis(lattice, n, T, J, B, p_e, p_m, list);
  //     // print_lattice(lattice, n);
  //     energy_array[i] = *p_e;
  //     magnet_array[i] = *p_m;
  //     // printf("ARRAY MAG = %f\n", magnet_array[i]);
  //     //printf("ARRAY ENERGIA = %f\n", energy_array[i]);
  // 	  fprintf(fdat, "%i,%3.6g,%3.3g,%3.3g \n",i, magnet_array[i], energy_array[i],T);
  //     printf("dato tomado para T = %.2f, i = %i de %i\n", T, i, n_term);
  //   }
    //
    // // ciclo de sampleo, toma datos solo cada tiempo de descorrelacion
    // for (int i = 0; i < n_iter; i++) {
    //   metropolis(lattice, n, T, J, B, p_e, p_m, list);
    //   // print_lattice(lattice, n);
    //   energy_array[i] = *p_e;
    //   magnet_array[i] = *p_m;
    //   // printf("ARRAY MAG = %f\n", magnet_array[i]);
    //   //printf("ARRAY ENERGIA = %f\n", energy_array[i]);
    //   if (i%n_corr == 0){
    //     fprintf(fdat, "%i,%3.6g,%3.3g,%3.3g \n",i, magnet_array[i], energy_array[i],T);
    //     printf("dato tomado para T = %.3f, i = %i de %i\n", T, i/n_corr, n_iter/n_corr);
    //   }
    // }
    // //free(lattice);
  //   free(energy_array);
  //   free(magnet_array);
  // }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~LO DE ABAJO SOLO PARA EL PUNTO E ~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  for (int j=0; j < range_temp; j++){

    //T = 0.4 + (4.0/10)*j; como andaba antes
    T = (T_max/range_temp)*(j+1);
    //B = 0.0;
    //fill_lattice(lattice, n, prob);
    list_exp(list, T, J, B);

    float E = energy_2(lattice, n, J, B);
    float M = magnet(lattice, n);
    float* p_e = &E;
    float* p_m = &M;
    float* energy_array = malloc(n_iter * sizeof(float)); // aca voy a guardar los valores de energia
    float* magnet_array = malloc(n_iter * sizeof(float)); // aca voy a guardar los valores de magnetizacon

    // ciclo de termalizacion
    for (int i = 0; i < n_term; i++) {
      // printf("antes de cambiar\n");
      // print_lattice(lattice, n);
      // printf("cambiado\n");
      metropolis_2(lattice, n, T, J, B, p_e, p_m, list);
      // print_lattice(lattice, n);
      energy_array[i] = *p_e;
      magnet_array[i] = *p_m;
      // printf("ARRAY MAG = %f\n", magnet_array[i]);
      //printf("ARRAY ENERGIA = %f\n", energy_array[i]);
  	  // fprintf(fdat, "%i,%3.6g,%3.3g,%3.3g \n",i, magnet_array[i], energy_array[i],T);
      // printf("dato tomado para T = %.2f, i = %i de %i\n", T, i, n_term);
    }
    //
    // // ciclo de sampleo, toma datos solo cada tiempo de descorrelacion
    for (int i = 0; i < n_iter; i++) {
      metropolis_2(lattice, n, T, J, B, p_e, p_m, list);
      // print_lattice(lattice, n);
      energy_array[i] = *p_e;
      magnet_array[i] = *p_m;
      // printf("ARRAY MAG = %f\n", magnet_array[i]);
      //printf("ARRAY ENERGIA = %f\n", energy_array[i]);
      if (i%n_corr == 0){
        fprintf(fdat, "%i,%3.6g,%3.3g,%3.3g \n",i, magnet_array[i], energy_array[i],T);
        printf("dato tomado para T = %.3f, i = %i de %i\n", T, i/n_corr, n_iter/n_corr);
      }
    }
    // //free(lattice);
    free(energy_array);
    free(magnet_array);
  }

  return 0;
}
