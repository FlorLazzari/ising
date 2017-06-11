#ifndef METROPOLIS_H
#define METROPOLIS_H
int metropolis(int *lattice, int n, float T, float J, float B, float* p_e, float* p_m, double* list);
int metropolis_2(int *lattice, int n, float T, float J, float B, float* p_e, float* p_m, double* list);
int pick_site(int *lattice, int n);
int flip(int *lattice, int n, int site);
float delta_E (int *lattice, int n, int site, float J, float B);
float delta_E_2 (int *lattice, int n, int site, float J, float B);
float energy(int *lattice, int n, float J, float B);
float energy_2(int *lattice, int n, float J, float B);
int sum_E (int *lattice, int selected, int right, int down);
int sum_E_version2 (int *lattice, int n, int idx);
int list_exp(double *list, float T, float J, float B);
double probability(int spin, float DE, float J, float B, float T, double *list);
float magnet(int *lattice, int n);
float delta_magnet(int *lattice, int site, int n);
#endif
