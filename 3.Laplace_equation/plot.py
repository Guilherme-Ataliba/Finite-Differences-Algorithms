import matplotlib.pyplot as plt
from matplotlib import animation
from matplotlib.animation import PillowWriter
import pandas as pd
import numpy as np

def real(x, y, a, b, V0, n=157):
    soma = 0
    for i in range(1, n, 2):
        soma += 1/i*(np.cosh(i*np.pi*x/a)/np.cosh(i*np.pi*b/a))*np.sin(i*np.pi*y/a)
    soma = 4*V0/np.pi*soma  
    return soma

Nx = 24
Ny = 48
iterations = 1e3
xf = 1
yf = 1
V0 = -5
x = np.linspace(-xf, xf, Nx)
y = np.linspace(0, yf, Ny)
xv, yv = np.meshgrid(x, y)

data = pd.read_csv("output.csv", sep=",", names=[i for i in range(Nx)])
Z = data.values
real = real(xv, yv, xf, yf, V0)

fig, ax = plt.subplots(subplot_kw={"projection": "3d"})

plt.title(f"Predicted - {iterations} iterations")
ax.plot_surface(xv, yv, Z, cmap="jet")

plt.savefig("Figures/predicted.jpg")


fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
plt.title(f"Real - {iterations} iterations")
ax.plot_surface(xv, yv, real, cmap="jet")

# plt.figure()
# plt.title(f"Real - {iterations} iterations")
# plt.pcolormesh(xv, yv, real, cmap="jet")
# plt.savefig("Figures/real.jpg")
plt.show()

