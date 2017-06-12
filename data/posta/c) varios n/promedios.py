# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
import scipy.special as sp

samples_16 = np.loadtxt("sample_n16_100_100temp_J1.csv", delimiter = ',', skiprows=1)
samples_32 = np.loadtxt("sample_n32_100_100temp_J1.csv", delimiter = ',', skiprows=1)
samples_64 = np.loadtxt("sample_n64_100_100temp_J1.csv", delimiter = ',', skiprows=1)
samples_128 = np.loadtxt("sample_n128_100_100temp_J1.csv", delimiter = ',', skiprows=1)
n = [16, 32, 64, 128]

n_iter = 100    # cantidad de datos sampleados para cada temperatura
range_temp = 100 #cantidad de temperaturas
temp_max = 5
temperatura = np.linspace(temp_max/range_temp, temp_max, range_temp)

#%% Obtener mag y en

tiempo = np.arange(n_iter)
magnet = np.zeros((n_iter, range_temp, len(n)))
energy = np.zeros((n_iter, range_temp, len(n)))


for i in range(range_temp):
    magnet[:,i,0] = samples_16[i*n_iter : (i+1)*n_iter,1]
    energy[:,i,0] = samples_16[i*n_iter : (i+1)*n_iter,2]/(16*16)

for i in range(range_temp):
    magnet[:,i,1] = samples_32[i*n_iter : (i+1)*n_iter,1]
    energy[:,i,1] = samples_32[i*n_iter : (i+1)*n_iter,2]/(32*32)

for i in range(range_temp):
    magnet[:,i,2] = samples_64[i*n_iter : (i+1)*n_iter,1]
    energy[:,i,2] = samples_64[i*n_iter : (i+1)*n_iter,2]/(64*64)

for i in range(range_temp):
    magnet[:,i,3] = samples_128[i*n_iter : (i+1)*n_iter,1]
    energy[:,i,3] = samples_128[i*n_iter : (i+1)*n_iter,2]/(128*128)
    
    
mag_avg = np.abs(np.mean(magnet,0))
en_avg = np.mean(energy,0)
mag_teo = np.nan_to_num((1-(np.sinh(2/temperatura))**(-4))**(1/8))

K_grande = 1/temperatura
kappa = 2*np.sinh(2*K_grande)/(np.cosh(2*K_grande))**2
kappa_prim = 2*(np.tanh(2*K_grande))**2 - 1

en_teo = -(1/(np.tanh(2*K_grande)))*(1 + (2*kappa_prim)/np.pi * sp.ellipk(kappa) )

#%% Graficar

plt.figure()
plt.suptitle('Magnetizacion en funcion de la temperatura', fontsize = 15, y = 0.9999)
for i in range(len(n)):
    plt.subplot(2,2,i+1)
    plt.plot(temperatura, mag_avg[:,i], '*', label = 'simulaciones')
    plt.plot(temperatura, mag_teo, 'r', label = 'teorico')
    plt.grid(True)
    plt.xlabel('Temperatura')
    plt.ylabel('Magnetizacion por sitio')
    plt.title('n = %i' % n[i])
    plt.legend()
plt.tight_layout()

plt.figure()
plt.suptitle('Energia en funcion de la temperatura', fontsize = 15, y = 0.9999)
for i in range(len(n)):
    plt.subplot(2,2,i+1)
    plt.plot(temperatura, en_avg[:,i], '*', label = 'simulaciones')
    plt.plot(temperatura, en_teo, 'r', label = 'teorico')
    plt.grid(True)
    plt.xlabel('Temperatura')
    plt.ylabel('Energia por sitio')
    plt.legend()
    plt.title('n = %i' % n[i])

plt.tight_layout()
plt.show()
