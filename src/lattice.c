#include "lattice.h"
int fill_lattice(int *lattice, int n, float p) {

  int i;
	float r;

  // recorre el lattice
	for (i=0; i<n*n; i++){
		r = rand()%100; // genera el random
		r = r/100;

    // con probabilidad p, llena con 1 o -1
		if (r <= p){
			lattice[i] = 1;
				}
		else{
			lattice[i] = -1;
			  }
	}
  return 0;
}

int print_lattice(int *lattice, int n) {

  int i;
	printf("\n");

	for (i = 0 ; i < n*n ; i++){
		if ((i)%n == 0){
			printf("\n %3i", lattice[i]);
		}
		else{
			printf("%3i",lattice[i]);
			}
		}
	printf("\n");
	printf("\n");

  return 0;
}
