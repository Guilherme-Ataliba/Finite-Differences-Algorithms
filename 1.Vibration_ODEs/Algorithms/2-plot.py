import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import argparse

data = pd.read_csv("2-output.csv", names=["t", "u"], sep=",")

def real(w, b, m, F0, t):
    w02 = k/m
    return ((F0/m)/((w02 - w**2)**2 + (b/m)**2 *w**2)) * np.cos(w*t - ((b/m)*w)/(w02 - w**2))

    # I = 1.0;
w = 2.0
    # V = 3;
m = 1.0
b = 2.0
k = 1.0
F0 = 2.0

plt.plot(data.t, data.u, label="predicted", alpha=0.5)
# plt.plot(data.t, real(w, b, m, F0, data.u), label="real")
plt.legend()
plt.show()
