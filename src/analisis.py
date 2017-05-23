import numpy as np
import matplotlib.pyplot as plt

datos = np.loadtxt("datos_magnet_energy.csv", delimiter = ',', skiprows=1)
t = datos[:,0]
magnet = datos[:,1]
energy = datos[:,2]

plt.figure()
plt.subplot(1,2,1)
plt.plot(t, magnet, label = 'magnetizacion')
plt.grid(True)
plt.xlabel('Tiempo')
plt.ylabel('magnetizacion')

plt.subplot(1,2,2)
plt.plot(t, energy, label = 'energia')
plt.grid(True)
plt.xlabel('Tiempo')
plt.ylabel('energia')

plt.show()
