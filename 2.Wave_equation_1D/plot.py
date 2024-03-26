import matplotlib.pyplot as plt
from matplotlib import animation
from matplotlib.animation import PillowWriter
import pandas as pd
import numpy as np

def exact(x, t, A, L, c):
    return A*np.sin(np.pi/L*x)*np.cos(np.pi/L*c*t)

Nx = 10
Nt = 100
xf = 5.0
L = 10
A = 2
c = 0.5
x = np.linspace(0, xf, Nx)
data = pd.read_csv("output_test.csv", sep=",", names=[i for i in range(Nx)])

fig, ax = plt.subplots(1, 1)
ln, = plt.plot([], [])

ax.set_xlim(0, xf)
ax.set_ylim(-10, 10)

def animate(i):
    ln.set_data(x, data.iloc[i])
    # ln.set_data(x, exact(x, i, A, L, c))

ani = animation.FuncAnimation(fig, animate, frames=Nt, interval=30)
ani.save("images/ani_test.gif", writer="pillow", fps=Nx, dpi=100)