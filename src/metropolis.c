#include "metropolis.h"

int metropolis(int *lattice, int n, float T) {
  ********
  return 0;
}

int sum_E (int *lattice, int selected, int right, int down) {
  // caso: todos iguales
  if (lattice[selected] == lattice[right] && lattice[selected] == lattice[down]){
    sum = 2;
  }
  // caso: uno distinto
  else if ( (lattice[selected] == lattice[right] && lattice[selected] != lattice[down]) || (lattice[selected] != lattice[right] && lattice[selected] == lattice[down])){
    sum = 0;
  }
  // caso: todos distintos
  // (esto en principio podria ser un else en lugar de un else if porque cubrimos todos los casos)
  else if (lattice[selected] != lattice[right] && lattice[selected] != lattice[down]){
    sum = -2;
  }
  return sum;
}


// calcula energia del lattice
int energy(int *lattice, int n) {
  int i, j;
  int down;
  int right;
  int selected;
  int E = 0;

	for (i=0; i<n; i++){ // recorre filas
		for (j=0; j<n; j++){ // recorre columnas
			selected = i*n+j;
			down = selected+n;
			right = selected+1;

      //ultimo elemento
      if (i == n && j ==n){
        E += sum_E(lattice, selected, selected-n+1, n-1);
      }
      // ultima fila
      else if (i == n){
      ********
      }
      // ultima columna
      else if (j == n){
      ********
      }
    }
  }
}


int pick_site(int *lattice, int n, int idx) {
  int r = rand()%n;
  return r;
}






int flip(int *lattice, int n, float T) {
  int sitio = pick_site(lattice, n);
  return 0;
}
