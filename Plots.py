import numpy as np
import math
import matplotlib.pyplot as plt

r, v = np.loadtxt('RadialVelocities.dat', skiprows = 1, unpack=True)
b, d, h = np.loadtxt('PlotData.dat', unpack=True)

def Model(r):
    v = np.zeros(len(r))
    
    for i in range(len(r)):
        v[i] = ((math.sqrt(b)*r[i])/((r[i]**2 + 0.2497**2)**(3.0/4.0))) + ((math.sqrt(d)*r[i])/((r[i]**2 + (5.16 + 0.3105)**2)**(3.0/4.0))) + ((math.sqrt(h))/((r[i]**2 + 64.3**2)**(1.0/4.0)))
        
    return v

rm = np.arange(0.3, 299, 0.01)
vm = Model(rm)

plt.plot(r, v, 'bo', label='Datos dados')
plt.plot(rm, vm, 'k', label='Modelo encontrado')
plt.xlabel('Radio (kpc)')
plt.ylabel('Volumen (kpcˆ3)')
plt.legend()
plt.savefig('graph.png')
plt.close