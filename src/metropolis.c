#include "metropolis.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>

int metropolis(int *lattice, int n, float T, float J, float B, float* p_e , float* p_m, double* list) { // esto esta bien?
  int site = pick_site(lattice, n);
  // printf("el sitio elegido es %i\n", site);
  double r;
  float DE = delta_E(lattice, n, site, J, B);
  // printf("el DE de metropolis es %f\n",DE); // me da cero asi que acá falla
  float DM = delta_magnet(lattice, site, n);
  if (DE <= 0) { // tomo el cambio
    flip(lattice, n, site);
    //printf("la energia antes de cambiar es %f\n",*p_e);
    *p_e += DE;
    *p_m += DM;
    //printf("la energia despues del cambio es %f\n",*p_e);
  }
  else {
    r = (((double)rand())/RAND_MAX);
    // printf("el random de metropolis es %lf \n", r);
    // double prob_exp = probability(lattice[site], DE, J, B, T, list);
    double prob_exp = exp(-DE/T);
    if (r < prob_exp){
      flip(lattice, n, site);
      //printf("la energia antes de cambiar es %f\n",*p_e);
      *p_e += DE;
      *p_m += DM;
      //printf("la energia despues del cambio es %f\n",*p_e);
    }
    else {
    }
  }
  return 0;
}

// para el punto e)
int metropolis_2(int *lattice, int n, float T, float J, float B, float* p_e , float* p_m, double* list) { // esto esta bien?
  int site = pick_site(lattice, n);
  // printf("el sitio elegido es %i\n", site);
  double r;
  float DE = delta_E_2(lattice, n, site, J, B);
  // printf("el DE de metropolis es %f\n",DE); // me da cero asi que acá falla
  float DM = delta_magnet(lattice, site, n);
  if (DE <= 0) { // tomo el cambio
    flip(lattice, n, site);
    //printf("la energia antes de cambiar es %f\n",*p_e);
    *p_e += DE;
    *p_m += DM;
    //printf("la energia despues del cambio es %f\n",*p_e);
  }
  else {
    r = (((double)rand())/RAND_MAX);
    // printf("el random de metropolis es %lf \n", r);
    // double prob_exp = probability(lattice[site], DE, J, B, T, list);
    double prob_exp = exp(-DE/T);
    if (r < prob_exp){
      flip(lattice, n, site);
      //printf("la energia antes de cambiar es %f\n",*p_e);
      *p_e += DE;
      *p_m += DM;
      //printf("la energia despues del cambio es %f\n",*p_e);
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
  float DE = 0; //ACA HABIA UN INTTTTTTTT *emoji de kurt cobain*
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
  //printf("el delta del B es %f\n",2*B*lattice[site] );
  //printf("la delta de energia desde la funcion es %f\n",DE );
  return DE;
}

float delta_E_2 (int *lattice, int n, int site, float J, float B){ //para el punto e)
  float DE = 0; //ACA HABIA UN INTTTTTTTT *emoji de kurt cobain*
  int sum_neigh_1 = 0;
  int sum_neigh_2 = 0;
  int i, j;
  j = site%n;
  i = site/n; // ****funciona usar site/n ?

  int up, right, down, left;
  up = ((i-1+n)%n)*n+j;
  down = j+((i+1+n)%n)*n;
  right = ((j+1+n)%n)+i*n;
  left = ((j-1+n)%n)+i*n;

  // calcula la antiferro para 2dos vecinos
  int up_right, down_right, up_left, down_left;
  up_right = (j+1+n)%n + n*((i-1+n)%n);
  down_right = (j+1+n)%n + n*((i+1+n)%n);
  up_left = (j-1+n)%n + n*((i-1+n)%n);
  down_left = (j-1+n)%n + n*((i+1+n)%n);

  sum_neigh_1 = lattice[right] + lattice[down] + lattice[left] + lattice[up];
  sum_neigh_2 = lattice[up_right] + lattice[up_left] + lattice[down_right] + lattice[down_left];
  DE = J*2*lattice[site]*sum_neigh_1 + 2*B*lattice[site] - J*2*lattice[site]*sum_neigh_2;
  //printf("el delta del B es %f\n",2*B*lattice[site] );
  //printf("la delta de energia desde la funcion es %f\n",DE );
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
      //printf("el sitio i,j = %i %i contribuye con E = %f \n", i, j, - B*(float)lattice[selected] );
    }
  }
  return E;
}

float energy_2(int *lattice, int n, float J, float B) { //para el punto e)
  int i, j;
  int down;
  int right;
  int selected;
  int up_right;
  int down_right;
  float E = 0;

	for (i=0; i<n; i++){ // recorre filas
		for (j=0; j<n; j++){ // recorre columnas
			selected = i*n+j;
			down = j+((i+1+n)%n)*n; // para ultima fila, es [(2n)%n *n + j] = j
			right = ((j+1+n)%n)+i*n; // para ultima columna es [(2n)%n + i*n] = i*n
      up_right = (j+1+n)%n + n*((i-1+n)%n); //agrega segundos vecinos diagonales
      down_right = (j+1+n)%n + n*((i+1+n)%n);
      // ver si se puede mejorar el sum_E, abajo otra solucion
      //E += sum_E(lattice, selected, right, down);
      E += ( (-J)*lattice[selected]*(lattice[right]+lattice[down]) - B*(float)lattice[selected] + J*lattice[selected]*(lattice[up_right]+lattice[down_right]) ); // termino de segundos vecinos
      //printf("el sitio i,j = %i %i contribuye con E = %f \n", i, j, - B*(float)lattice[selected] );
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
    // printf("list exp -- con DE = %lf tengo exp = %lf\n", DE, list[i]);
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
  // printf("probability -- con DE = %f, el index es %i con prob = %lf\n", DE, index, p);
  return p;
}

int flip(int *lattice, int n, int site) {
  lattice[site] = -lattice[site];
}
