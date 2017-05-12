#ifndef METROPOLIS_H
#define METROPOLIS_H
int metropolis(int *lattice, int n, float T);
int pick_site(int *lattice, int n, int idx);
int flip(int *lattice, int n, float T);
int delta_E (int *lattice, int n, int site);
int energy(int *lattice, int n);
int sum_E (int *lattice, int selected, int right, int down);
#endif
