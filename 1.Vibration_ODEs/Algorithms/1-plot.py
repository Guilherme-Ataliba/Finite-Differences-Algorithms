import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import argparse

data = pd.read_csv("1-output.csv", names=["t", "u", "erro"], sep=",")

def real(I: float, w: float, t: float):
    return I * np.cos(w * t)

parser = argparse.ArgumentParser()
parser.add_argument("--I", type=float, default=1.0)
parser.add_argument("--w", type=float, default=2*np.pi)


a = parser.parse_args()
I = a.I
w = a.w

# plt.plot(data.t, data.u, label="predicted", alpha=0.5)
plt.plot(data.t, real(I, w, data.t), label="real", alpha=0.5)
# plt.plot(data.t, data.erro)
plt.legend()
plt.show()
