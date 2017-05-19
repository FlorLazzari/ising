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
  i = (site - j)/n;

  int up, right, down, left;
  up = site - n;
  right = site + 1;
  down = site + n;
  left = site -1;

  // primer fila
  if (i == 0){
    up = (n-1)*n + j;
  }
  // ultima fila
  if (i == (n-1)){
    down = j;
  }
  // primer columna
  if (j == 0){
    left = i*n + (n-1);
  }
  // ultima columna
  if (j == (n-1)){
    right = i*n;
  }

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

// hacer este cambio evitaria tantos "if andentro de for"
up = lattice[((i-1+n)%n)*n+j];
down = lattice[j+((i+1+n)%n)*n];
right = lattice[((j+1+n)%n)*n+i*n];
left = lattice[((j-1+n)%n)*n+i*n];
sum = up + down + right + left;

}

// esto habria que cambiarlo, no es eficiente hacer "if adentro de for":

// calcula energia del lattice
// int energy(int *lattice, int n) {
//   int i, j;
//   int down;
//   int right;
//   int selected;
//   int E = 0;
//
// 	for (i=0; i<n; i++){ // recorre filas
// 		for (j=0; j<n; j++){ // recorre columnas
// 			selected = i*n+j;
// 			down = selected+n;
// 			right = selected+1;
//
//       //ultimo elemento
//       if (i == n && j == n){
//         E += sum_E(lattice, selected, selected-n+1, n-1);
//       }
//       // ultima fila
//       else if (i == n){
//         E += sum_E(lattice, selected, right, j);
//       }
//       // ultima columna
//       else if (j == n){
//         E += sum_E(lattice, selected, selected-n+1, down);
//       }
//       // bulk
//       else {
//         E += sum_E(lattice, selected, right, down);
//       }
//     }
//   }
//   return E;
// }

int pick_site(int *lattice, int n, int idx) {
  // este metodo segun gille "no es uniforme"
  // int r = rand()%(n*n);
  // habria que hacer algo asi:
  int r = int(((float)rand()/RAND_MAX) * (n*n));
  return r;
}

int flip(int *lattice, int n, float T) {
  int site = pick_site(lattice, n, 0);
  int DE = delta_E(lattice, n, site);
  return 0;
}
