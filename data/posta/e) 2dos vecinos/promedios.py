# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt

samples = np.loadtxt("sample_n32_1k_100temp_J1_2ds.csv", delimiter = ',', skiprows=1)

n_iter = 1000    # cantidad de datos sampleados para cada temperatura
range_temp = 100 #cantidad de temperaturas
temp_max = 5
temperatura = np.linspace(temp_max/range_temp, temp_max, range_temp)

#%% Obtener mag y en

tiempo = np.arange(n_iter)
magnet = np.zeros((n_iter, range_temp))
energy = np.zeros((n_iter, range_temp))

for i in range(range_temp):
    magnet[:,i] = samples[i*n_iter : (i+1)*n_iter,1]
    energy[:,i] = samples[i*n_iter : (i+1)*n_iter,2]

mag_avg = np.abs(np.mean(magnet,0))
en_avg = np.mean(energy,0)

#%% Graficar

plt.figure()
plt.subplot(2,1,1)
plt.plot(temperatura, mag_avg, 'r*')
plt.grid(True)
plt.xlabel('Temperatura')
plt.ylabel('magnetizacion')
plt.title('Magnetizacion en funcion de la temperatura para interacción con 2dos vecinos', fontsize = 15)
#plt.legend()

plt.subplot(2,1,2)
plt.plot(temperatura, en_avg, 'r*')
plt.grid(True)
plt.xlabel('Temperatura')
plt.ylabel('energia')
#plt.legend()
plt.title('Energia en funcion de la temperatura para interacción con 2dos vecinos', fontsize = 15)

#plt.tight_layout()
plt.show()
