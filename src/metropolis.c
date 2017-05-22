#include "metropolis.h"
#include <time.h>
#include <stdlib.h>

int metropolis(int *lattice, int n, float T) {
  int E_lattice;
  E_lattice = energy(lattice, n);
  int site = flip(lattice, n, T);
  return 0;
}

int delta_E (int *lattice, int n, int site){
  int DE = 0;
  int sum_neigh = 0;
  int i, j;
  j = site%n;
  i = (site - j)/n; // ****funciona usar site/n ?

  int up, right, down, left;
  up = ((i-1+n)%n)*n+j;
  down = j+((i+1+n)%n)*n;
  right = ((j+1+n)%n)+i*n;
  left = ((j-1+n)%n)+i*n;

  sum_neigh = lattice[right] + lattice[down] + lattice[left] + lattice[up];
  DE = -2*lattice[site]*sum_neigh;
  return DE;
}

int sum_E (int *lattice, int selected, int right, int down) {
  int sum = 0;
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


int sum_E_version2 (int *lattice, int n, int idx){
  // filas
  int i = idx/n;
  //columnas
  int j = idx%n;

  int up, down, right, left, sum;

  // hacer este cambio evitaria tantos "if andentro de for"
  up = lattice[((i-1+n)%n)*n+j];
  down = lattice[j+((i+1+n)%n)*n];
  right = lattice[((j+1+n)%n)+i*n];
  left = lattice[((j-1+n)%n)+i*n];
  sum = up + down + right + left;

}

// en principio anda bien...

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
			down = j+((i+1+n)%n)*n; // para ultima fila, es [(2n)%n *n + j] = j
			right = ((j+1+n)%n)+i*n; // para ultima columna es [(2n)%n + i*n] = i*n

      // ver si se puede mejorar el sum_E, abajo otra solucion
      //E += sum_E(lattice, selected, right, down);
      E += lattice[selected]*(lattice[right]+lattice[down]);
    }
  }
  return E;
}

int pick_site(int *lattice, int n, int idx) {
  // este metodo segun gille "no es uniforme"
  // int r = rand()%(n*n);
  // habria que hacer algo asi:
  int r;
  r = (int)(((float)rand()/RAND_MAX) * (n*n));
  return r;
}

int flip(int *lattice, int n, float T) {
  int site = pick_site(lattice, n, 0);
  int DE = delta_E(lattice, n, site);
  return 0;
}
