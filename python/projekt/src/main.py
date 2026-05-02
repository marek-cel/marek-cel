#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt

if __name__ == "__main__":
    print("Hello, World!")

    x_values = np.linspace(0, 10, 100)
    y_values = np.sin(x_values)

    plt.plot(x_values, y_values)
    plt.title("Sine Wave")
    plt.xlabel("x")
    plt.ylabel("sin(x)")
    plt.grid()
    plt.show()
