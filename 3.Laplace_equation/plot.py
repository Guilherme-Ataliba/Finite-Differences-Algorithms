import matplotlib.pyplot as plt
from matplotlib import animation
from matplotlib.animation import PillowWriter
import pandas as pd
import numpy as np

def real(x, y, w, a, b):
    return (np.sin(w*x)/np.sin(w*a)) * (np.sinh(w*y)/np.sinh(w*b))

Nx = 1000
Ny = 500
iterations = 1e5
xf = 3*np.pi
yf = np.pi
w = 1
x = np.linspace(0, xf, Nx)
y = np.linspace(0, yf, Ny)

xv, yv = np.meshgrid(x, y)

data = pd.read_csv("output.csv", sep=",", names=[i for i in range(Nx)])
Z = data.values
real = real(xv, yv, w, xf, yf)

fig, ax = plt.subplots(subplot_kw={"projection": "3d"})

plt.title(f"Predicted - {iterations} iterations")
ax.plot_surface(xv, yv, Z, cmap="jet")
# plt.pcolormesh(xv, yv, Z, cmap="jet")
# plt.savefig("Figures/predicted.jpg")


fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
plt.title(f"Real - {iterations} iterations")
ax.plot_surface(xv, yv, real, cmap="jet")

# plt.figure()
# plt.title(f"Real - {iterations} iterations")
# plt.pcolormesh(xv, yv, real, cmap="jet")
# plt.savefig("Figures/real.jpg")
plt.show()

