import matplotlib.pyplot as plt
from matplotlib.cm import coolwarm
from matplotlib import animation
from matplotlib.animation import PillowWriter
import numpy as np
import pandas as pd
import os

dt = np.dtype([])
with open("output/test_matrix.bin", "rb") as f:
    Nx = np.fromfile(f, dtype=np.int32, count=1)[0]
    Ny = np.fromfile(f, dtype=np.int32, count=1)[0]
    Nt = np.fromfile(f, dtype=np.int32, count=1)[0]
    data = np.fromfile(f).reshape(Nt, Ny, Nx)

a=b=10

x = np.linspace(0, a, Nx)
y = np.linspace(0, b, Ny)
xv, yv = np.meshgrid(x, y)

plt.rcParams["figure.autolayout"] = True

fig, ax = plt.subplots(1, 1, subplot_kw={"projection": "3d"})

plot = [ax.plot_surface(xv, yv, data[0], cmap="coolwarm", vmin=-0.02, vmax=0.02)]
ax.set_zlim(-0.1, 0.1)

def animate(i, Z_time, plot):
    plot[0].remove()
    plot[0] = ax.plot_surface(xv, yv, data[i], cmap="coolwarm", vmin=-0.02, vmax=0.02)


ani = animation.FuncAnimation(fig, animate, frames=Nt, fargs=(data, plot), interval=30, repeat=True)
ani.save("images/ani_test.gif", writer="pillow", fps=Nx, dpi=100)
