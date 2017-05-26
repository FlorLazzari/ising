# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt

datos = np.loadtxt("datos_magnet_energy.csv", delimiter = ',', skiprows=1)

n_iter = 20000 # cantidad de iteraciones para cada temperatura (de ising.c)
tiempo_term = 10000 #estimado del tiempo de termalizacion
range_temp = 10 #cantidad de temperaturas

#%% Organizar datos

# cada array tiene los valores en el tiempo (filas) para cada temperatura (columna)
t = np.zeros((n_iter - tiempo_term, range_temp))
magnet = np.zeros((n_iter - tiempo_term, range_temp))
energy = np.zeros((n_iter - tiempo_term, range_temp))
m = np.zeros((n_iter - tiempo_term, range_temp))
e = np.zeros((n_iter - tiempo_term, range_temp))

# separa los datos en columnas segun la temperatura
for i in range(range_temp):
    t[:,i] = datos[tiempo_term + i*n_iter : (i+1)*n_iter, 0]
    magnet[:,i] = datos[tiempo_term + i*n_iter : (i+1)*n_iter,1]
    energy[:,i] = datos[tiempo_term + i*n_iter : (i+1)*n_iter,2]
    # estos dos son para la autocorrelacion
    m[:,i] = magnet[:,i] - np.mean(magnet[:,i])
    e[:,i] = energy[:,i] - np.mean(energy[:,i])

#%% Graficar

temp = 6 # el indice corresponde a la temp T = 0.4*(i+1) (entre 0.4 y 4)

plt.figure()
plt.title('Magnetizacion post-termalizar (sin promedio)')
plt.subplot(1,2,1)
plt.plot(t[:,temp], m[:,temp], label = 'magnetizacion')
plt.grid(True)
plt.xlabel('Tiempo')
plt.ylabel('magnetizacion')

plt.subplot(1,2,2)
plt.title('Energia post-termalizar (sin promedio)')
plt.plot(t[:,temp], e[:,temp], label = 'energia')
plt.grid(True)
plt.xlabel('Tiempo')
plt.ylabel('energia')

plt.show()

#%% Autocorrelacion
tiempo_auto = int((n_iter-tiempo_term)/2) # asegurarme de que sea par?
k = np.arange(tiempo_auto)
rho = np.zeros((tiempo_auto, range_temp))

#por ahora para Magnetizacion
for i in range(range_temp):
    for k in range(tiempo_auto):
        rho[k,i] = np.mean(m[:k,i]*m[k:,i])/np.mean(m[:,i]**2)

plt.figure()
plt.plot()
