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
    frames = np.fromfile(f, dtype=np.int32, count=1)[0]
    data = np.fromfile(f).reshape(frames, Ny, Nx)

a=b=10

x = np.linspace(0, a, Nx)
y = np.linspace(0, b, Ny)
xv, yv = np.meshgrid(x, y)

plt.rcParams["figure.autolayout"] = True

fig, ax = plt.subplots(1, 1, subplot_kw={"projection": "3d"})

z_lim = [-Nx/5000, Nx/5000]

plot = [ax.plot_surface(xv, yv, data[0], cmap="coolwarm", vmin=2*z_lim[0]/10, vmax=2*z_lim[1]/10)]
ax.set_zlim(-Nx/5000, Nx/5000)

def animate(i, Z_time, plot, z_lim):
    plot[0].remove()
    plot[0] = ax.plot_surface(xv, yv, data[i], cmap="coolwarm", vmin=2*z_lim[0]/10, vmax=2*z_lim[1]/10)


ani = animation.FuncAnimation(fig, animate, frames=frames, fargs=(data, plot, z_lim), interval=30, repeat=True)
ani.save("images/ani_test.gif", writer="pillow", fps=60, dpi=100)
