#include "metropolis.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>

int metropolis(int *lattice, int n, float T, float J, float B, float* p_e , float* p_m, double* list) { // esto esta bien?
  int site = pick_site(lattice, n);
  double r;
  float DE = delta_E (lattice, n, site, J, B);
  float DM = delta_magnet(lattice, site, n);
  if (DE <= 0) { // tomo el cambio
    flip(lattice, n, site);
    *p_e += DE;
    *p_m += DM;
  }
  else {
    r = (((double)rand())/RAND_MAX);
    double prob_exp = probability(lattice[site], DE, J, B, T, list);
    if (r < prob_exp){
      flip(lattice, n, site);
      *p_e += DE;
      *p_m += DM;
    }
    else {
    }
  }
  return 0;
}

float magnet(int *lattice, int n){
  int i;
  float M = 0;
  for (i = 0; i < n*n; i++) {
    M += lattice[i];
  }
  return M/(n*n);
}

float delta_magnet(int *lattice, int site, int n){
  float DM;
  DM = (-2*(float)lattice[site])/(n*n);
  // printf("DM = %f\n", DM);
  return DM;
}

float delta_E (int *lattice, int n, int site, float J, float B){
  int DE = 0;
  int sum_neigh = 0;
  int i, j;
  j = site%n;
  i = site/n; // ****funciona usar site/n ?

  int up, right, down, left;
  up = ((i-1+n)%n)*n+j;
  down = j+((i+1+n)%n)*n;
  right = ((j+1+n)%n)+i*n;
  left = ((j-1+n)%n)+i*n;

  sum_neigh = lattice[right] + lattice[down] + lattice[left] + lattice[up];
  DE = J*2*lattice[site]*sum_neigh + 2*B*lattice[site];
  printf("el delta del B es %f\n",2*B*lattice[site] );
  return DE;
}

// calcula energia del lattice
float energy(int *lattice, int n, float J, float B) {
  int i, j;
  int down;
  int right;
  int selected;
  float E = 0;

	for (i=0; i<n; i++){ // recorre filas
		for (j=0; j<n; j++){ // recorre columnas
			selected = i*n+j;
			down = j+((i+1+n)%n)*n; // para ultima fila, es [(2n)%n *n + j] = j
			right = ((j+1+n)%n)+i*n; // para ultima columna es [(2n)%n + i*n] = i*n

      // ver si se puede mejorar el sum_E, abajo otra solucion
      //E += sum_E(lattice, selected, right, down);
      E += ( (-J)*lattice[selected]*(lattice[right]+lattice[down]) - B*(float)lattice[selected] );
      printf("el sitio i,j = %i %i contribuye con E = %f \n", i, j, - B*(float)lattice[selected] );
    }
  }
  return E;
}

int pick_site(int *lattice, int n) {
  int r;
  r = (int)(((float)rand()/RAND_MAX) * (n*n));
  return r;
}

int list_exp(double *list, float T, float J, float B){
  int i;
  double DE;
  for (i = 0; i < 5; i++) {
    DE = (double)(2*(J*(i*2-4)+B));
    list[i] = exp(-(DE/T)); //el exp de verdad
  }
  return 0;
}

double probability(int spin, float DE, float J, float B, float T, double *list){
  int index;
  // ***no hay posibilidad de que se pisen para distintos J y B??
  if (J == 0){
    index = 0; // **esto esta bien??
  }
  else{
    index = ((int)((DE/(2)-B)/J) + 4)/2; // ** le sacamos el spin??
  }
  double p = (list[index]); // *** SI NO FUNICONA MIRAR ACA Y EN LOS DOUBLE
  return p;
}

int flip(int *lattice, int n, int site) {
  lattice[site] = -lattice[site];
}
