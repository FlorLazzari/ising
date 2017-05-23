#ifndef METROPOLIS_H
#define METROPOLIS_H
int metropolis(int *lattice, int n, float T, float J, float B);
int pick_site(int *lattice, int n, int idx);
int flip(int *lattice, int n, float T, float J, float B);
float delta_E (int *lattice, int n, int site, float J, float B);
float energy(int *lattice, int n, float J, float B);
int sum_E (int *lattice, int selected, int right, int down);
int sum_E_version2 (int *lattice, int n, int idx);
#endif
