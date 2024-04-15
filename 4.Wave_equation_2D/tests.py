import matplotlib.pyplot as plt
from matplotlib.cm import coolwarm
from matplotlib import animation
from matplotlib.animation import PillowWriter
import numpy as np
import pandas as pd
import os

dt = np.dtype([])
with open("output/test.bin", "rb") as f:
    # Nx = np.fromfile(f, dtype=np.int32, count=1)[0]
    # Ny = np.fromfile(f, dtype=np.int32, count=1)[0]
    Nx = 1000
    Ny = 1000
    data = np.fromfile(f).reshape(Ny, Nx)

# print(data.max())
a=b=10

x = np.linspace(0, a, Nx)
y = np.linspace(0, b, Ny)
xv, yv = np.meshgrid(x, y)

plt.rcParams["figure.autolayout"] = True

fig, ax = plt.subplots(1, 1, subplot_kw={"projection": "3d"})

plot = [ax.plot_surface(xv, yv, data, cmap="coolwarm", vmin=-0.02, vmax=0.02)]
ax.set_zlim(-Nx/1000, Nx/1000)

plt.show()
