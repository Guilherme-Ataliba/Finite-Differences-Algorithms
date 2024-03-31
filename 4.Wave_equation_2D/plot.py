import matplotlib.pyplot as plt
from matplotlib.cm import coolwarm
import numpy as np
import pandas as pd

Ny = 100
Nx = 100
a = 10
b = 10

x = np.linspace(0, a, Nx)
y = np.linspace(0, b, Ny)
xv, yv = np.meshgrid(x, y)

data = pd.read_csv("final_time.csv", sep=",", names=[i for i in range(0, Ny)])
Z = data.values

fig, ax = plt.subplots(subplot_kw={"projection": "3d"})

surf = ax.plot_surface(xv, yv, Z, cmap=coolwarm)
fig.colorbar(surf)

plt.show()