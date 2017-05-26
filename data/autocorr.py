# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt

datos = np.loadtxt("datos_magnet_energy.csv", delimiter = ',', skiprows=1)

n_iter = 20000 # cantidad de iteraciones para cada temperatura (de ising.c)
tiempo_term = 10000 #estimado del tiempo de termalizacion (a ojo)
range_temp = 10 #cantidad de temperaturas
temperatura = np.arange(0.4,4.4,0.4)

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
    # estos dos son para la autocorrelacion (resto el offset)
    m[:,i] = magnet[:,i] - np.mean(magnet[:,i])
    e[:,i] = energy[:,i] - np.mean(energy[:,i])

#%% Graficar m y e

plt.figure()

for i in range(10):
    plt.subplot(1,2,1)
    plt.plot(datos[i*n_iter : (i+1)*n_iter, 0], datos[i*n_iter : (i+1)*n_iter,1], label = 'T = {:.2f}'.format(temperatura[i]))

    plt.subplot(1,2,2)
    plt.plot(datos[i*n_iter : (i+1)*n_iter,0], datos[i*n_iter : (i+1)*n_iter,2], label = 'T = {:.2f}'.format(temperatura[i]))

plt.subplot(1,2,1)
plt.grid(True)
plt.xlabel('Tiempo')
plt.ylabel('magnetizacion')
plt.legend()

plt.subplot(1,2,2)
plt.grid(True)
plt.xlabel('Tiempo')
plt.ylabel('energia')
plt.legend()
plt.title('Magnetizacion y energia en el tiempo')
plt.show()

#%% Graficar Fluctuaciones

for temp in range(10):
    plt.subplot(1,2,1)
    plt.plot(t[:,temp], m[:,temp], label = 'T = {:.2f}'.format(temperatura[temp]))

    plt.subplot(1,2,2)
    plt.plot(t[:,temp], e[:,temp], label = 'T = {:.2f}'.format(temperatura[temp]))

plt.subplot(1,2,1)
plt.grid(True)
plt.xlabel('Tiempo')
plt.ylabel('magnetizacion')
plt.legend()

plt.subplot(1,2,2)
plt.grid(True)
plt.xlabel('Tiempo')
plt.ylabel('energia')
plt.legend()
plt.title('Fluctuaciones de magnetizacion y energia en el tiempo')
plt.show()

#%% Autocorrelacion

N = 1000
tiempo_auto = int(n_iter - tiempo_term - 2*N) # asegurarme de que sea par?
t_rho = np.arange(tiempo_auto)
rho = np.zeros((tiempo_auto, range_temp))

#
# def autocorr(x):
#     result = np.correlate(x, x, mode='full')
#     return result[result.size/2:]


#por ahora para Magnetizacion
for i in range(range_temp):
    for k in range(1,tiempo_auto):
        # el indice falopa es para evitar cosas como m[:0]
        rho[k-1,i] = np.mean(m[:N,i]*m[k:N+k,i])/np.mean(m[:N+k,i]**2) # ***revisar biennnnn!!!!

#%% Graficar autocorr

plt.figure()
for temp in range(10):
    plt.plot(t_rho, rho[:,temp], label = 'T = {:.2f}'.format(temperatura[temp]))
plt.legend()
plt.title('Autocorrelacion en funcion del tiempo')
plt.grid(True)
plt.xlabel('Tiempo')
plt.ylabel('Autocorrelacion (mag)')
plt.show()


# tiempo_descorr = 15000 # ver de donde sale
# mag_posta = magnet[tiempo_descorr - tiempo_term :,:]
# en_posta = energy[tiempo_descorr - tiempo_term :,:]
# mag_avg = np.mean(mag_posta,0)
# en_avg = np.mean(en_posta,0)
