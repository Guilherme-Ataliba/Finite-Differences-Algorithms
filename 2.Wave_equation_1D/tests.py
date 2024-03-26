import matplotlib.pyplot as plt
from matplotlib import animation
from matplotlib.animation import PillowWriter
import pandas as pd
import numpy as np


def I(x, A, L):
    return A*np.sin(np.pi/L*x)

Nx = 100
L = 10
A = 2
c = 0.5
x = np.linspace(0, 10, Nx)
t = np.linspace(0, 10, Nx)

u = np.empty(Nx)
u_n = np.empty(Nx)
u_nm1 = np.empty(Nx)

dx = x[1] - x[0]
dt = t[1] - t[0]
C = c*dt/dx
Nt = len(t) - 1
C2 = C**2


data = []

for i in range(0, Nx):
    u_n[i] = I(x[i], A, L)

for i in range(1, Nx-1):
    u[i] = u_n[i] - 0.5*C**2*(u_n[i+1] - 2*u_n[i] + u_n[i-1])
u[0] = 0
u[Nx-1] = 0

data.append(u)

u_nm1[:], u_n[:] = u_n, u

for n in range(1, Nt):
    for i in range(1, Nx-1):
        u[i] = 2*u_n[i] - u_nm1[i] - C**2*(u_n[i+1] - 2*u_n[i] + u_n[i-1])
    u[0] = 0
    u[Nx-1] = 0

    data.append(u)

    u_nm1[:], u_n[:] = u_n, u

fig, ax = plt.subplots(1, 1)
ln, = plt.plot([], [])

ax.set_xlim(0, 10)
ax.set_ylim(-10, 10)

def animate(i):
    ln.set_data(x, data[i])
    # ln.set_data(x, exact(x, i, A, L, c))

ani = animation.FuncAnimation(fig, animate, frames=Nx-1, interval=Nx-1)
ani.save("images/ani1.gif", writer="pillow", fps=Nx-1, dpi=100)