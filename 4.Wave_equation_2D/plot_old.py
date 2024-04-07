import matplotlib.pyplot as plt
from matplotlib.cm import coolwarm
from matplotlib import animation
from matplotlib.animation import PillowWriter
import numpy as np
import pandas as pd
import os

plt.rcParams["figure.autolayout"] = True

Ny = 99
Nx = 99
a = 10
b = 10
l = len(os.listdir("output"))

x = np.linspace(0, a, Nx)
y = np.linspace(0, b, Ny)
xv, yv = np.meshgrid(x, y)

fig, ax = plt.subplots(1, 1, subplot_kw={"projection": "3d"})

Z_time = []
for i in range(0, l):
    data = pd.read_csv(f"output/{i}.csv")
    Z_time.append(data.values)    

plot = [ax.plot_surface(xv, yv, Z_time[0], cmap=coolwarm, vmin=-0.02, vmax=0.02)]
ax.set_zlim(-0.1, 0.1)

def animate(i, Z_time, plot):
    plot[0].remove()
    plot[0] = ax.plot_surface(xv, yv, Z_time[i], cmap=coolwarm, vmin=-0.02, vmax=0.02)


ani = animation.FuncAnimation(fig, animate, frames=l, fargs=(Z_time, plot), interval=30, repeat=True)
ani.save("images/ani_test.gif", writer="pillow", fps=Nx, dpi=100)