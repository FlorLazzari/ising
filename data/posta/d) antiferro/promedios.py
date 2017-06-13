# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt

samples_B01 = np.loadtxt("sample_n32_100_100temp_J-1_B01.csv", delimiter = ',', skiprows=1)
samples_B1 = np.loadtxt("sample_n32_1k_100temp_J-1_B1.csv", delimiter = ',', skiprows=1)

n_iter_01 = 100    # cantidad de datos sampleados para cada temperatura
n_iter_1 = 1000
range_temp = 100 #cantidad de temperaturas
temp_max = 5
temperatura = np.linspace(temp_max/range_temp, temp_max, range_temp)

#%% Obtener mag y en

magnet_01 = np.zeros((n_iter_01, range_temp))
energy_01 = np.zeros((n_iter_01, range_temp))

magnet_1 = np.zeros((n_iter_1, range_temp))
energy_1 = np.zeros((n_iter_1, range_temp))

for i in range(range_temp):
    magnet_01[:,i] = samples_B01[i*n_iter_01 : (i+1)*n_iter_01,1]
    energy_01[:,i] = samples_B01[i*n_iter_01 : (i+1)*n_iter_01,2]
    
    magnet_1[:,i] = samples_B1[i*n_iter_1 : (i+1)*n_iter_1,1]
    energy_1[:,i] = samples_B1[i*n_iter_1 : (i+1)*n_iter_1,2]

mag_avg_01 = np.abs(np.mean(magnet_01,0))
en_avg_01 = np.mean(energy_01,0)

mag_avg_1 = np.abs(np.mean(magnet_1,0))
en_avg_1 = np.mean(energy_1,0)

#%% Graficar

plt.figure()
plt.suptitle('Magnetización y energía para antiferromagnético', fontsize = 15)
plt.subplot(2,2,1)
plt.plot(temperatura, mag_avg_01, '*')
plt.grid(True)
plt.xlabel('Temperatura')
plt.ylabel('magnetizacion')
plt.title('Magnetización con $B=0.1$')
#plt.legend()

plt.subplot(2,2,2)
plt.plot(temperatura, mag_avg_1, '*')
plt.grid(True)
plt.xlabel('Temperatura')
plt.ylabel('magnetizacion')
#plt.legend()
plt.title('Magnetización con $B=1$')

plt.subplot(2,2,3)
plt.plot(temperatura, en_avg_01, '*')
plt.grid(True)
plt.xlabel('Temperatura')
plt.ylabel('energia')
plt.title('Energía con $B=0.1$')
#plt.legend()

plt.subplot(2,2,4)
plt.plot(temperatura, en_avg_1, '*')
plt.grid(True)
plt.xlabel('Temperatura')
plt.ylabel('energía')
plt.title('Energía con $B=0.1$')
#plt.legend()

#plt.tight_layout()
plt.show()
