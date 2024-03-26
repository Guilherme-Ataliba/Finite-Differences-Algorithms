import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

forward_data = pd.read_csv("forward.csv", names=["X", "f", "dfdx", "error"])
central_data = pd.read_csv("central.csv", names=["X", "f", "dfdx", "error"])
second_central_data = pd.read_csv("second_central.csv", names=["X", "f", "dfdx", "error"])

# plt.plot(data.X, data.dfdx, label="Nummerical")
# plt.plot(data.X, np.cos(data.X), label="Cossine")
plt.plot(forward_data.X, forward_data.error, label="forward")
plt.plot(central_data.X, central_data.error, label="central")
plt.plot(second_central_data.X, second_central_data.error, label="second_central")
plt.legend()
plt.show()
