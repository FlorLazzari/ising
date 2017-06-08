#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Jun  7 20:56:20 2017

@author: martin
"""
import numpy as np
import matplotlib.pyplot as plt

datos_term = np.loadtxt("termalizacion_n32_1k_B1.csv", delimiter = ',', skiprows=1)
samples = np.loadtxt("sampleo_n32_1k_B1.csv", delimiter = ',', skiprows=1)

n_iter = 100 * 1000 # cantidad de iteraciones para cada temperatura (de ising.c)
n_iter_sample = 100
tiempo_term = 50 * 1000 #estimado del tiempo de termalizacion (a ojo)
range_temp = 10 #cantidad de temperaturas
range_temp_sample = 100
temp_max = 2.6
temperatura_corto = np.linspace(temp_max/range_temp, temp_max, range_temp)
temperatura_sample = np.linspace(temp_max/range_temp_sample, temp_max, range_temp_sample)


#%% Graficar magnetizacion y energia (sin cortar termalizacion)

# [i*n_iter : (i+1)*n_iter,0]
plt.figure()

for i in range(range_temp):
    plt.subplot(1,2,1)
    plt.plot(datos_term[0 : n_iter, 0], datos_term[i*n_iter : (i+1)*n_iter,1], label = 'T = {:.2f}'.format(temperatura_corto[i]))

    plt.subplot(1,2,2)
    plt.plot(datos_term[0 : n_iter, 0], datos_term[i*n_iter : (i+1)*n_iter,2], label = 'T = {:.2f}'.format(temperatura_corto[i]))

plt.subplot(1,2,1)
plt.grid(True)
plt.xlabel('Tiempo')
plt.ylabel('magnetizacion')
plt.title('Magnetizacion en el tiempo')
plt.legend()

plt.subplot(1,2,2)
plt.grid(True)
plt.xlabel('Tiempo')
plt.ylabel('energia')
plt.legend()
plt.title('Energia en el tiempo')

plt.show()


#%% Obtener valores medios

B = 1
param = B/temperatura_sample
#
## cada array tiene los valores en el tiempo (filas) para cada temperatura (columna)
magnet = np.zeros((n_iter_sample, range_temp_sample))
energy = np.zeros((n_iter_sample, range_temp_sample))

# separa los datos en columnas segun la temperatura
for i in range(range_temp):
    magnet[:,i] = samples[i*n_iter_sample : (i+1)*n_iter_sample,1]
    energy[:,i] = samples[i*n_iter_sample : (i+1)*n_iter_sample,2]

mag_avg = np.mean(magnet,0)
en_avg = np.mean(energy,0)


#%% Graficar


plt.figure()

plt.subplot(1,2,1)
plt.plot(param, mag_avg)
plt.grid(True)
plt.xlabel('B/T')
plt.ylabel('magnetizacion')
plt.title('magnetizacion en function de la temperatura')

plt.legend()

plt.subplot(1,2,2)
plt.plot(param, en_avg)
plt.grid(True)
plt.xlabel('Tiempo')
plt.ylabel('energia')
plt.legend()
plt.title('Fluctuaciones de energia en el tiempo')

plt.show()
