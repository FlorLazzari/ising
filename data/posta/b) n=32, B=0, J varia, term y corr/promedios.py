# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
import scipy.special as sp

samples = np.loadtxt("sample_n32_100_100temp_J1.csv", delimiter = ',', skiprows=1)

n = 32
n_iter = 100    # cantidad de datos sampleados para cada temperatura
range_temp = 100 #cantidad de temperaturas
temp_max = 5
temperatura = np.linspace(temp_max/range_temp, temp_max, range_temp)

#%% Obtener mag y en

tiempo = np.arange(n_iter)
magnet = np.zeros((n_iter, range_temp))
energy = np.zeros((n_iter, range_temp))

for i in range(range_temp):
    magnet[:,i] = samples[i*n_iter : (i+1)*n_iter,1]
    energy[:,i] = samples[i*n_iter : (i+1)*n_iter,2]/(n*n)

mag_avg = np.abs(np.mean(magnet,0))
en_avg = np.mean(energy,0)
mag_teo = np.nan_to_num((1-(np.sinh(2/temperatura))**(-4))**(1/8))

K_grande = 1/temperatura
kappa = 2*np.sinh(2*K_grande)/(np.cosh(2*K_grande))**2
kappa_prim = 2*(np.tanh(2*K_grande))**2 - 1

en_teo = -(1/(np.tanh(2*K_grande)))*(1 + (2*kappa_prim)/np.pi * sp.ellipk(kappa) )

#%% Graficar

plt.figure()
plt.subplot(2,1,1)
plt.plot(temperatura, mag_avg, '*', label = 'simulaciones')
plt.plot(temperatura, mag_teo, 'r', label = 'teorico')
plt.grid(True)
plt.xlabel('Temperatura')
plt.ylabel('Magnetizacion por sitio')
plt.title('Magnetizacion en funcion de la temperatura para n = %i' % n, fontsize = 15)
plt.legend()

plt.subplot(2,1,2)
plt.plot(temperatura, en_avg, '*', label = 'simulaciones')
plt.plot(temperatura, en_teo, 'r', label = 'teorico')
plt.grid(True)
plt.xlabel('Temperatura')
plt.ylabel('Energia por sitio')
plt.legend()
plt.title('Energia en funcion de la temperatura para n = %i' % n, fontsize = 15)

plt.tight_layout()
plt.show()
