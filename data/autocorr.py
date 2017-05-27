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
plt.title('Magnetizacion en el tiempo')
plt.legend()

plt.subplot(1,2,2)
plt.grid(True)
plt.xlabel('Tiempo')
plt.ylabel('energia')
plt.legend()
plt.title('Energia en el tiempo')

plt.tight_layout()
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
plt.title('Fluctuaciones de magnetizacion en el tiempo')

plt.legend()

plt.subplot(1,2,2)
plt.grid(True)
plt.xlabel('Tiempo')
plt.ylabel('energia')
plt.legend()
plt.title('Fluctuaciones de energia en el tiempo')

plt.tight_layout()
plt.show()

#%% Autocorrelacion

N = n_iter - tiempo_term
t_rho = np.arange(N)
rho_m = np.zeros((N, range_temp))
rho_e = np.zeros((N, range_temp))

for i in range(range_temp):
    for k in range(1,N):
        # el indice falopa es para evitar cosas como m[:0]
        rho_m[k-1,i] = np.sum(m[:N-k,i]*m[k:,i])/np.sum(m[:,i]**2)
        rho_e[k-1,i] = np.sum(e[:N-k,i]*e[k:,i])/np.sum(e[:,i]**2)
         # esta es la que va, el tema era el mean en lugar del sum, porque los
         # arrays no tenian la misma longitud

#%% Autocorrelacion por intervalos y su promedio

# intento ahora partir el intervalo de tiempo en particiones, y calcular rho
# en cada uno, para después promediarlos.

particiones = 5
n_part = int(N/particiones)
t_rho_prom = np.arange(n_part)
rho_part_m = np.zeros((n_part, particiones, range_temp))
rho_part_e = np.zeros((n_part, particiones, range_temp))

# para cada temperatura, y para cada particion calculo la rho como antes.
# el tema es ajustar los bordes de cada particion con el indice j
# el N sería acá n_prom, y 
for i in range(range_temp):
    for j in range(particiones):
        for k in range(1,n_part):
            
            rho_part_m[k-1,j,i] = np.sum(m[j*n_part : (j+1)*n_part-k ,i] * 
                      m[j*n_part + k : (j+1)*n_part ,i]) / np.sum(m[j*n_part : (j+1)*n_part ,i]**2)

            rho_part_e[k-1,j,i] = np.sum(e[j*n_part : (j+1)*n_part-k ,i] * 
                      e[j*n_part + k : (j+1)*n_part ,i]) / np.sum(e[j*n_part : (j+1)*n_part ,i]**2)
            
rho_prom_m = np.mean(rho_part_m,1)            
rho_prom_e = np.mean(rho_part_e,1) 

#%% Graficar autocorr

plt.figure()
for temp in range(10):
    plt.subplot(1,2,1)
    plt.plot(t_rho, rho_m[:,temp], label = 'T = {:.2f}'.format(temperatura[temp]))
    
    plt.subplot(1,2,2)
    plt.plot(t_rho, rho_e[:,temp], label = 'T = {:.2f}'.format(temperatura[temp]))

plt.subplot(1,2,1)    
plt.legend()
plt.title('Autocorrelacion de magnetizacion en funcion del tiempo')
plt.grid(True)
plt.xlabel('Tiempo')
plt.ylabel('Autocorrelacion (mag)')

plt.subplot(1,2,2)    
plt.legend()
plt.title('Autocorrelacion de energia en funcion del tiempo')
plt.grid(True)
plt.xlabel('Tiempo')
plt.ylabel('Autocorrelacion (en)')

plt.show()


#%% Graficar autocorr promediada

# los graficos decaen bien pero (para cualquier cantidad de particiones?)
# decaen a cero posta al final del intervalo, corte que medio turbiooo

plt.figure()
for temp in range(10):
    plt.subplot(1,2,1)
    plt.plot(t_rho_prom, rho_prom_m[:,temp], label = 'T = {:.2f}'.format(temperatura[temp]))
    
    plt.subplot(1,2,2)
    plt.plot(t_rho_prom, rho_prom_e[:,temp], label = 'T = {:.2f}'.format(temperatura[temp]))

plt.subplot(1,2,1)    
plt.legend()
plt.title('Autocorrelacion de magnetizacion en funcion del tiempo (promediada)')
plt.grid(True)
plt.xlabel('Tiempo')
plt.ylabel('Autocorrelacion (mag)')

plt.subplot(1,2,2)    
plt.legend()
plt.title('Autocorrelacion de energia en funcion del tiempo (promediada)')
plt.grid(True)
plt.xlabel('Tiempo')
plt.ylabel('Autocorrelacion (en)')

plt.show()

#%% Promedios de mag y en post-correlacion

tiempo_descorr = 1000 # ver de donde sale (se cuenta desde tiempo_term, del grafico de rho)
mag_posta = magnet[tiempo_descorr:, :]
en_posta = energy[tiempo_descorr:, :]
mag_avg = np.mean(mag_posta,0)
en_avg = np.mean(en_posta,0)

#%% Graficar E y M en temperatura

plt.figure()
plt.subplot(2,1,1)
plt.plot(temperatura, mag_avg)
plt.grid(True)
plt.xlabel('Temperatura')
plt.ylabel('magnetizacion')
plt.title('Magnetizacion en funcion de la temperatura')
#plt.legend()

plt.subplot(2,1,2)
plt.plot(temperatura, en_avg)
plt.grid(True)
plt.xlabel('Temperatura')
plt.ylabel('energia')
#plt.legend()
plt.title('Energia en funcion de la temperatura')

plt.tight_layout()
plt.show()